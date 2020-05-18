#!/usr/bin/env python3
# Copyright (c) 2015-2017 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test BIP65 (CHECKLOCKTIMEVERIFY).

Test that the CHECKLOCKTIMEVERIFY soft-fork activates at (regtest) block height
1351.
"""

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *
from test_framework.mininode import *
from test_framework.blocktools import create_coinbase, create_block
from test_framework.script import CScript, OP_1NEGATE, OP_CHECKLOCKTIMEVERIFY, OP_DROP, CScriptNum, OP_CHECKSIG
#from io import BytesIO
from fake_stake.base_test import sQuorum_FakeStakeTest
from test_framework.key import CECKey
from struct import pack

CLTV_HEIGHT = 1050

# Reject codes that we might receive in this test
REJECT_INVALID = 16
REJECT_OBSOLETE = 17
REJECT_NONSTANDARD = 64

def cltv_invalidate(tx):
    '''Modify the signature in vin 0 of the tx to fail CLTV

    Prepends -1 CLTV DROP in the scriptSig itself.

    TODO: test more ways that transactions using CLTV could be invalid (eg
    locktime requirements fail, sequence time requirements fail, etc).
    '''
    tx.vin[0].scriptSig = CScript([OP_1NEGATE, OP_CHECKLOCKTIMEVERIFY, OP_DROP] +
                                  list(CScript(tx.vin[0].scriptSig)))

def cltv_validate(node, tx, height):
    '''Modify the signature in vin 0 of the tx to pass CLTV
    Prepends <height> CLTV DROP in the scriptSig, and sets
    the locktime to height'''
    tx.vin[0].nSequence = 0
    tx.nLockTime = height

    # Need to re-sign, since nSequence and nLockTime changed
    signed_result = node.signrawtransaction(ToHex(tx))
    new_tx = CTransaction()
    new_tx.deserialize(BytesIO(hex_str_to_bytes(signed_result['hex'])))

    new_tx.vin[0].scriptSig = CScript([CScriptNum(height), OP_CHECKLOCKTIMEVERIFY, OP_DROP] +
                                  list(CScript(new_tx.vin[0].scriptSig)))
    return new_tx

def create_transaction(node, coinbase, to_address, amount):
    inputs = [{ "txid" : coinbase['txid'], "vout" : coinbase['vout']}]
    outputs = { to_address : amount }
    rawtx = node.createrawtransaction(inputs, outputs)
    signresult = node.signrawtransaction(rawtx)
    tx = CTransaction()
    tx.deserialize(BytesIO(hex_str_to_bytes(signresult['hex'])))
    return tx

def create_pos_block(self, hashPrevBlock, stakingPrevOuts, height):
    ''' creates a block to spam the network with
    :param   hashPrevBlock:      (hex string) hash of previous block
             stakingPrevOuts:    ({COutPoint --> (int, int, int, str)} dictionary)
                                  map outpoints (to be used as staking inputs) to amount, block_time, nStakeModifier, hashStake
             height:             (int) block height
    :return  block:              (CBlock) generated block
    '''

    # Get current time
    current_time = int(time.time())
    nTime = current_time & 0xfffffff0

    # Create coinbase TX
    # Even if PoS blocks have empty coinbase vout, the height is required for the vin script
    coinbase = create_coinbase(height)
    coinbase.vout[0].nValue = 0
    coinbase.vout[0].scriptPubKey = b""
    coinbase.nTime = nTime
    coinbase.rehash()

    # Create Block with coinbase
    block = create_block(int(hashPrevBlock, 16), coinbase, nTime)

    # Find valid kernel hash - Create a new private key used for block signing.
    if not block.solve_stake(stakingPrevOuts):
        raise Exception("Not able to solve for any prev_outpoint")

    # Sign coinstake TX and add it to the block
    self.block_sig_key = CECKey()

    # Create a new private key and get the corresponding public key
    self.block_sig_key.set_secretbytes(hash256(pack('<I', 0xffff)))
    pubkey = self.block_sig_key.get_pubkey()
    # Create the raw stake TX (unsigned)
    scriptPubKey = CScript([pubkey, OP_CHECKSIG])
    outNValue = int(stakingPrevOuts[block.prevoutStake][0] + 2*COIN)
    stake_tx_unsigned = CTransaction()
    stake_tx_unsigned.nTime = block.nTime
    stake_tx_unsigned.vin.append(CTxIn(block.prevoutStake))
    stake_tx_unsigned.vin[0].nSequence = 0xffffffff
    stake_tx_unsigned.vout.append(CTxOut())
    stake_tx_unsigned.vout.append(CTxOut(outNValue, scriptPubKey))
    # Sign the stake TX
    stake_tx_signed_raw_hex = self.node.signrawtransaction(bytes_to_hex_str(stake_tx_unsigned.serialize()))['hex']

    # Deserialize the signed raw tx into a CTransaction object and return it
    stake_tx_signed = CTransaction()
    stake_tx_signed.deserialize(BytesIO(hex_str_to_bytes(stake_tx_signed_raw_hex)))

    signed_stake_tx = stake_tx_signed
    block.vtx.append(signed_stake_tx)

    # Get correct MerkleRoot and rehash block
    block.hashMerkleRoot = block.calc_merkle_root()
    block.rehash()

    # Sign block with coinstake key and return it
    block.sign_block(self.block_sig_key)
    return block


class BIP65Test(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 1
        self.extra_args = [['-promiscuousmempoolflags=1', '-whitelist=127.0.0.1']]
        self.setup_clean_chain = True

    def run_test(self):
        self.nodes[0].add_p2p_connection(P2PInterface())
        self.node=self.nodes[0]
        network_thread_start()

        # wait_for_verack ensures that the P2P connection is fully up.
        self.nodes[0].p2p.wait_for_verack()

        self.log.info("Mining %d blocks", CLTV_HEIGHT - 2)
        self.coinbase_blocks = self.nodes[0].generate(500)
        self.coinbase_blocks += self.nodes[0].generate(CLTV_HEIGHT - 502)
        self.nodeaddress = self.nodes[0].getnewaddress()
        self.log.info("Test that an invalid-according-to-CLTV transaction can still appear in a block")

        listunsp=self.nodes[0].listunspent()
        for tx in listunsp:
            if (tx['vout'] == 0):
                self.cointx = tx
        spendtx = create_transaction(self.nodes[0], self.cointx,
                self.nodeaddress, 1.0)
        cltv_invalidate(spendtx)
        spendtx.rehash()

        block_count = self.nodes[0].getblockcount()
        current_block_n = block_count + 1
        pastBlockHash = self.nodes[0].getblockhash(block_count)
        stakingPrevOuts = sQuorum_FakeStakeTest.get_prevouts(self, listunsp, block_count)
        block = create_pos_block(self, pastBlockHash, stakingPrevOuts, current_block_n)

        block.nVersion = 4
        block.vtx.append(spendtx)
        block.hashMerkleRoot = block.calc_merkle_root()
        block.rehash()
        block.sign_block(self.block_sig_key)

        self.nodes[0].p2p.send_and_ping(msg_block(block))
        assert_equal(self.nodes[0].getbestblockhash(), block.hash)

        self.nodes[0].generate(205)
        listunsp=self.nodes[0].listunspent()
        for tx in listunsp:
            if (tx['vout'] == 0):
                self.cointx = tx
        spendtx = create_transaction(self.nodes[0], self.cointx,
                self.nodeaddress, 1.0)
        self.log.info("Test that blocks must now be at least version 5")
        block_count = self.nodes[0].getblockcount()
        current_block_n = block_count + 1
        pastBlockHash = self.nodes[0].getblockhash(block_count)
        stakingPrevOuts = sQuorum_FakeStakeTest.get_prevouts(self, listunsp, block_count)
        block = create_pos_block(self, pastBlockHash, stakingPrevOuts, current_block_n)

        block.nVersion = 4
        block.rehash()
        block.sign_block(self.block_sig_key)

        self.nodes[0].p2p.send_and_ping(msg_block(block))

        wait_until(lambda: "reject" in self.nodes[0].p2p.last_message.keys(), lock=mininode_lock)
        with mininode_lock:
            assert_equal(self.nodes[0].p2p.last_message["reject"].code, REJECT_OBSOLETE)
            assert_equal(self.nodes[0].p2p.last_message["reject"].reason, b'bad-version')
            assert_equal(self.nodes[0].p2p.last_message["reject"].data, block.sha256)
            del self.nodes[0].p2p.last_message["reject"]

        self.log.info("Test that invalid-according-to-cltv transactions cannot appear in a block")
        block.nVersion = 5

        cltv_invalidate(spendtx)
        spendtx.rehash()

        # Verify that a block with this transaction is invalid.
        block.vtx.append(spendtx)
        block.hashMerkleRoot = block.calc_merkle_root()
        block.rehash()
        block.sign_block(self.block_sig_key)

        self.nodes[0].p2p.send_and_ping(msg_block(block))

        wait_until(lambda: "reject" in self.nodes[0].p2p.last_message.keys(), lock=mininode_lock)
        with mininode_lock:
            assert self.nodes[0].p2p.last_message["reject"].code in [REJECT_INVALID, REJECT_NONSTANDARD]
            assert_equal(self.nodes[0].p2p.last_message["reject"].data, block.sha256)
            if self.nodes[0].p2p.last_message["reject"].code == REJECT_INVALID:
                # Generic rejection when a block is invalid
                assert_equal(self.nodes[0].p2p.last_message["reject"].reason, b'block-validation-failed')
            else:
                assert b'Negative locktime' in self.nodes[0].p2p.last_message["reject"].reason

        self.log.info("Test that a version 5 block with a valid-according-to-CLTV transaction is accepted")
        spendtx = cltv_validate(self.nodes[0], spendtx, CLTV_HEIGHT - 1)
        spendtx.rehash()

        block.vtx.pop()
        block.vtx.append(spendtx)
        block.hashMerkleRoot = block.calc_merkle_root()
        block.rehash()
        block.sign_block(self.block_sig_key)

        self.nodes[0].p2p.send_and_ping(msg_block(block))
        assert_equal(int(self.nodes[0].getbestblockhash(), 16), block.sha256)


if __name__ == '__main__':
    BIP65Test().main()
