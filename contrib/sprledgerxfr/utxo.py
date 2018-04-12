#! /usr/bin/env python3
import unittest
import os
from datetime import datetime, timedelta, tzinfo
import json
import re
# import sqlite3
import psycopg2
import requests
import time

ecoin = dict(
    name="Spreadcoin",
    symbol="SPR",
    url="http://spreadcoin.info",
    ispos=True,
    scheme=["proof-of-work", "proof-of-stake"],
    nethashcmd="getnetworkhps",
    rpchost="127.0.0.1",
    rpcuser="spreadcoinuser",
    rpcpassword="letmein",
    nbpp=20,
    endpoint="http://localhost:0000",
    dataset="sprchain",
    mainburnaddress="",
    testburnaddress="",
    donationaddresses = ["address-1-here"],
    port=41677,
    rpcport=41678,
    testnetrpcuser="spreadcoinuser",
    testnetrpcpassword="letmein",
    testnetdataset="sprtchain",
    testnetport=51677,
    testnetrpcport=51678,
    strftimeformat="%%H:%%M:%%S %%d-%%m-%%Y",
    blockdateformat="formatted",
    txdateformat="%%Y-%%m-%%d %%H:%%M:%%S UTC"
)

global blockhash
debug = False
test = False

MAX_BLOCK_HEIGHT = 1657200 # The block number marking the end of the public ledger, -1 for “latest block”
# MAX_BLOCK_HEIGHT = 1000


class RPCHost(object):
    def __init__(self, url):
        self._session = requests.Session()
        self._url = url
        self._headers = {'content-type': 'application/json'}

    def call(self, rpcMethod, *params):
        payload = json.dumps({"method": rpcMethod, "params": list(params), "jsonrpc": "2.0"})
        tries = 10
        hadConnectionFailures = False
        while True:
            # print("{url} {headers} {data}".format(url=self._url, headers=self._headers, data=payload))
            try:
                response = self._session.get(self._url, headers=self._headers, data=payload)
            except requests.exceptions.ConnectionError:
                tries -= 1
                if tries == 0:
                    raise Exception('Failed to connect for remote procedure call.')
                hadConnectionFailures = True
                print("Couldn't connect for remote procedure call, will sleep for ten seconds and then try again ({} more tries)".format(tries))
                time.sleep(10)
            else:
                if hadConnectionFailures:
                    print('Connected for remote procedure call after retry.')
                break
        if response.status_code not in (200, 500):
            raise Exception('RPC connection failure: ' + str(response.status_code) + ' ' + response.reason)
        responseJSON = response.json()
        if 'error' in responseJSON and responseJSON['error'] is not None:
            raise Exception('Error in RPC call: ' + str(responseJSON['error']))
        return responseJSON['result']


class TestCatchUp(unittest.TestCase):

    def setUp(self):
        self.ecoin = ecoin
        self.serverurl = 'http://{}:{}@localhost:{}/'.format(
            self.ecoin.get('rpcuser'), self.ecoin.get('rpcpassword'), self.ecoin.get('rpcport'))
        self.amerpc = RPCHost(self.serverurl)



        # self.conn = sqlite3.connect('utxo.db')
        # self.cursor = self.conn.cursor()

        # Connect to an existing database
        self.conn = psycopg2.connect("dbname=sprutxo user=gjh password=9h1991n5")

        # Open a cursor to perform database operations
        self.cursor = self.conn.cursor()


        # Create table
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS outputs (
            bnum integer, spent boolean default false,
            tx text, bhsh text,
            txhsh text, seq integer,
            addr text, bal numeric)''')
        self.cursor.execute('''CREATE INDEX IF NOT EXISTS txhsh_index ON outputs USING HASH (txhsh);''')
        self.conn.commit()

    def tearDown(self):
        # self.cursor.execute('''DROP TABLE IF EXISTS outputs;''')
        self.conn.commit()
        self.conn.close()

    # @unittest.skip("Passed, skipping")
    def test_doreadblock(self):
        binfo = self.amerpc.call('getinfo')
        self.cursor.execute('''select max(bnum) from outputs''')
        last_block_in_db = self.cursor.fetchone()[0] or 0
        blocknum = binfo['blocks'] if MAX_BLOCK_HEIGHT is None else MAX_BLOCK_HEIGHT
        if last_block_in_db < blocknum:
            print("Catching up from {} to {}".format(last_block_in_db, blocknum))
        for i in range(last_block_in_db + 1, blocknum  + 1):
            block = self.amerpc.call('getblock', self.amerpc.call('getblockhash', i))
            # FOR EACH TX
            for txid in block.get('tx'):
                tx = self.amerpc.call('decoderawtransaction', self.amerpc.call('getrawtransaction', txid))
                # SPENT TXS, REMOVE FROM UTXO SET
                for txin in tx.get('vin'):
                    if "coinbase" not in txin.keys():
                        query = """update outputs set spent = true where txhsh='{}' and seq={};""".format(
                                txin["txid"], txin["vout"])
                        self.cursor.execute(query)
                # UNSPENT TXS, ADD TO UTXO SET
                for txout in tx.get('vout'):
                    scripttype = txout["scriptPubKey"]["type"]
                    if scripttype in ["pubkeyhash", "pubkey", "scripthash"]:
                        query = "insert into outputs (bnum, tx, bhsh, txhsh, seq, addr, bal) " + \
                                "values ({}, '{}', '{}', '{}', {}, '{}', {});".format(
                                    i, scripttype, block["hash"], txid, txout["n"],
                                    txout["scriptPubKey"]["addresses"][0],
                                    txout["value"])
                        self.cursor.execute(query)
                    elif scripttype in ["nonstandard", "multisig"]:
                        query = "insert into outputs (bnum, tx, bhsh, txhsh, seq, addr, bal) " + \
                                "values ({}, '{}', '{}', '{}', {}, '** {} **', {});".format(
                                    i, scripttype, block["hash"], txid, txout["n"],
                                    scripttype, txout["value"])
                        self.cursor.execute(query)
                    else:
                        raise Exception(
                            "Don't know how to handle {} scripts in transaction {}".format(
                                scripttype, txid))
            if i % 10000 == 0:
                print(i)
                self.conn.commit()

if __name__ == "__main__":
    unittest.main()
