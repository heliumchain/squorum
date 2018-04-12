#!/usr/bin/env python
"""
Generate an ECDSA keypair and Bitcoin-compatible payment address.
Requires Brian Warner's excellent python-ecdsa library.


http://github.com/aristus/bitcoin-printer
"""
import hashlib, binascii

t = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'

def numtowif(numpriv):
    # for bitcoin (80=128)
    # for testcoin (EF==239 == testnet)
    # step1 = '80'+hex(numpriv)[2:].strip('L').zfill(64)
    step1 = 'BF'+hex(numpriv)[2:].strip('L').zfill(64)
    step2 = hashlib.sha256(binascii.unhexlify(step1)).hexdigest()
    step3 = hashlib.sha256(binascii.unhexlify(step2)).hexdigest()
    step4 = int(step1 + step3[:8] , 16)
    return ''.join([t[step4 / (58 ** l) % 58] for l in range(100)])[::-1].lstrip('1')

def wiftonum(wifpriv):
    return sum([t.index(wifpriv[::-1][l]) * (58 ** l) for l in range(len(wifpriv))]) / (2 ** 32) % (2 ** 256)

def validwif(wifpriv):
    return numtowif(wiftonum(wifpriv)) == wifpriv

def pubtoaddr(numpub):
    pubkey1 = hex(numpub)[2:].strip('L').zfill(130)
    # print(pubkey1)
    pubkey2 = hashlib.sha256(binascii.unhexlify(pubkey1)).hexdigest()
    # print(pubkey2)
    pubkey3 = hashlib.new('ripemd160',binascii.unhexlify(pubkey2)).hexdigest()
    # print(pubkey3)
    # for bitcoin (0)
    # pubkey3b = '00' + pubkey3
    # for testcoin (111)
    # pubkey3b = '6f' + pubkey3
    # for spreadcoin (63)
    pubkey3b = '3f' + pubkey3
    # print(pubkey3b)
    pubkey4 = hashlib.sha256(binascii.unhexlify(pubkey3b)).hexdigest()
    #pubkey4=hashlib.sha256(binascii.unhexlify(pubkey3b)).hexdigest()
    # print(pubkey4)
    pubkey5 = hashlib.sha256(binascii.unhexlify(pubkey4)).hexdigest()
    # print(pubkey5)
    pubkey5a = pubkey5[:8]
    # print(pubkey5a)
    pubkey6 = pubkey3b + pubkey5a
    # print(pubkey6)
    # print(pubkey6[:2])
    pubnum = int(pubkey6, 16)
    pubnumlist = []
    while pubnum !=0:
        pubnumlist.append(pubnum%58)
        pubnum /= 58
    address = ''
    for l in ['123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'[x] for x in pubnumlist]:
        address = l + address

    if pubkey6[:2] == '00':
        address = '1' + address

    return address

if __name__ == '__main__':
    # print("wallet import format {}".format(numtowif(0x5e4a8229e81a434b0646dcdbeb4b03083e2bd05af26fcf2e4e4aa37eacb2913b)))
    # print("wallet public address {}".format(pubtoaddr(0x04580e17442b4465fbf1eb8a039855343739f69f83222c3c6590c219dcd2d883bff96ebf6198ddb9a75baffffbc1be62f05261d7dfec58d8a06cf3809c6cefe620)))
    print("wallet import format {}".format(numtowif(0x57541e727b3b48e4a1de9dd187b96096c9a72238137c52cdbffa3083f7af3ec1)))
    print("wallet public address {}".format(pubtoaddr(0x042025df079e340dc6cef3fa71638a8d018bb81780ab5e76e7316520709519fb7b5bd0803791e9dee434b30a9c4bb93cca3225150e1a8d1713c7a9a07f05285881)))


# secret: 57541e727b3b48e4a1de9dd187b96096c9a72238137c52cdbffa3083f7af3ec1
# pubkey: 042025df079e340dc6cef3fa71638a8d018bb81780ab5e76e7316520709519fb7b5bd0803791e9dee434b30a9c4bb93cca3225150e1a8d1713c7a9a07f05285881
# address: 3f7ef08598f9dfcf71f39f7d2fe82851ce74d9258beec9b350
# addr_58: SYsCJmJXbD7cLenh3yf8LpeGVLZyAMQJR5

