#!/usr/bin/env python
"""
Generate an ECDSA keypair and Bitcoin-compatible payment address.
Requires Brian Warner's excellent python-ecdsa library.


http://github.com/aristus/bitcoin-printer
"""
from ecdsa.ecdsa import Public_key, int_to_string
from ecdsa.ellipticcurve import CurveFp, Point
import binascii
import hashlib
ripehash = hashlib.new('ripemd160')


# ***WARNING*** This is possibly insecure! ***WARNING***
from random import SystemRandom
randrange = SystemRandom().randrange


## Bitcoin has an adorable encoding scheme that includes numbers and letters
## but excludes letters which look like numbers, eg "l" and "O"
__b58chars = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
__b58base = len(__b58chars)
def b58encode(v):
    long_value = 0L
    for (i, c) in enumerate(v[::-1]):
        long_value += (256 ** i) * ord(c)
    result = ''
    while long_value >= __b58base:
        div, mod = divmod(long_value, __b58base)
        result = __b58chars[mod] + result
        long_value = div
    result = __b58chars[long_value] + result
    nPad = 0
    for c in v:
        if c == '\0':
            nPad += 1
        else:
            break
    return (__b58chars[0] * nPad) + result

def generate_btc_address():
    # secp256k1, not included in stock ecdsa
    _p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2FL
    _r = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141L
    _b = 0x0000000000000000000000000000000000000000000000000000000000000007L
    _a = 0x0000000000000000000000000000000000000000000000000000000000000000L
    _Gx = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798L
    _Gy = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8L
    curve_256 = CurveFp(_p, _a, _b)
    generator = Point(curve_256, _Gx, _Gy, _r)

    secret = randrange(1, generator.order())
    pubkey = Public_key(generator, generator * secret)
    step1 = '\x04' + int_to_string(pubkey.point.x()) + int_to_string(pubkey.point.y())
    step2 = hashlib.sha256(step1).digest()
    ripehash.update(step2)
    step4 = '\x3f' + ripehash.digest()
    step5 = hashlib.sha256(step4).digest()
    step6 = hashlib.sha256(step5).digest()
    chksum = step6[:4]
    addr = step4 + chksum
    addr_58 = b58encode(addr)
    return (
        hex(secret)[2:-1],
        binascii.hexlify(step1),
        binascii.hexlify(addr),
        addr_58
    )

def generate_pub_address_from_secret(secret):
    # secp256k1, not included in stock ecdsa
    _p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2FL
    _r = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141L
    _b = 0x0000000000000000000000000000000000000000000000000000000000000007L
    _a = 0x0000000000000000000000000000000000000000000000000000000000000000L
    _Gx = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798L
    _Gy = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8L
    curve_256 = CurveFp(_p, _a, _b)
    generator = Point(curve_256, _Gx, _Gy, _r)

    # secret = randrange(1, generator.order())
    pubkey = Public_key(generator, generator * secret)
    step1 = '\x04' + int_to_string(pubkey.point.x()) + int_to_string(pubkey.point.y())
    step2 = hashlib.sha256(step1).digest()
    ripehash.update(step2)
    step4 = '\x3f' + ripehash.digest()
    step5 = hashlib.sha256(step4).digest()
    step6 = hashlib.sha256(step5).digest()
    chksum = step6[:4]
    addr = step4 + chksum
    addr_58 = b58encode(addr)
    return (
        secret,
        hex(secret)[2:-1],
        binascii.hexlify(step1),
        binascii.hexlify(addr),
        addr_58
    )

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
    # secret, pubkey, addr, addr_58 = generate_btc_address()
    # print('secret: {}'.format(secret))
    # print('pubkey: {}'.format(pubkey))
    # print('address: {}'.format(addr))
    # print('addr_58: {}'.format(addr_58))
    # print("wif {}".format(numtowif(0x57541e727b3b48e4a1de9dd187b96096c9a72238137c52cdbffa3083f7af3ec1)))

    # print("secret-from-wifpriv {}".format(wiftonum("7QZrfF5NwiwhESwXgAEWWV1MPapDfTprnp3ZudfWY2ZmaAyWS4Q")))
    # print("wif {}".format(numtowif(17122472186888036075620406240825730964885834492327783793333612583577007149717)))
    # print("hexlified secret key {}".format(hex(17122472186888036075620406240825730964885834492327783793333612583577007149717)))


    # print("wallet public address {}".format(pubtoaddr(0x042025df079e340dc6cef3fa71638a8d018bb81780ab5e76e7316520709519fb7b5bd0803791e9dee434b30a9c4bb93cca3225150e1a8d1713c7a9a07f05285881)))

    # secret, pubkey, addr, addr_58 = generate_pub_address_from_secret(17122472186888036075620406240825730964885834492327783793333612583577007149717)
    # print('secret: {}'.format(secret))
    # print('pubkey: {}'.format(pubkey))
    # print('address: {}'.format(addr))
    # print('addr_58: {}'.format(addr_58))
    # print("wif {}".format(numtowif(0x25daf9cf817bb8406d28dc1f3eb636f02eaebf4c5dc0dae28ad618d6a873d295)))

    # secret, privkey, pubkey, addr, addr_58 = generate_pub_address_from_secret(
    #     wiftonum("7QZrfF5NwiwhESwXgAEWWV1MPapDfTprnp3ZudfWY2ZmaAyWS4Q"))
    secret, privkey, pubkey, addr, addr_58 = generate_pub_address_from_secret(
        wiftonum("7S7sAzb4vAgbC5ShYL4re7NtTKtpSt37Br5dogJkX3Efju5vzDX"))
    print('secret: {}'.format(secret))
    print('privkey: {}'.format(privkey))
    print('pubkey: {}'.format(pubkey))
    print('address: {}'.format(addr))
    print('addr_58: {}'.format(addr_58))
    print("wif {}".format(numtowif(secret)))
# secret: dcace436d957ace3e71ed4ac45d3271a11d8e2f4b4fc9a854b642d26ed263141
# pubkey: 04268ea362af051f3edba3813babe7c557a59659e443f11c3ec908426159e620b0a7ea64d75a56303db5b4474138385d1c5ca8283c615b6d5cfbd718567203a66d
# address: 3fbb25b3b4ad4bb71bd9638d249ccf022812fb8d95a4f374d1
# addr_58: SeMYZHxwEVo1tEunePcASGmfiBtiJdyoTN

# wifprv: 17122472186888036075620406240825730964885834492327783793333612583577007149717
# wifpvh: 25daf9cf817bb8406d28dc1f3eb636f02eaebf4c5dc0dae28ad618d6a873d295

# secret: 50a84840cae71fa36ac093e373ba6698bd2ad6e0efa63912ff247034219791bb
# pubkey: 0446aacf480f7337fc9a102247453716175b0ffd5c7946ef003e5bf3ffb7b256d9a6173fb92dcc6f0c9fb023c8d12d98b6b1c227917031a6a1d973e4d25990ce54
# address: 3fc9bd84ddb656862298aec75668529218643d0b1289e91131
# addr_58: SfghtQomK4vUSNtxXVGviQn1qtsncg7Zvp


"""
SPRxfrBsDnDuoPv11oWW6iUk7vnEcDPF2N - 7QZrfF5NwiwhESwXgAEWWV1MPapDfTprnp3ZudfWY2ZmaAyWS4Q

Prefix difficulty:            264104224 SPRxfr
Difficulty: 264104224
Using 4 worker thread(s)
Pattern: SPRxfr                                                                
Pubkey (hex): 04deb1fc5fd86d3e50e3b1740000f036ed9582c8a2a64208e5a9a7b1f5cbbd079be139e4649482060729b79155fea310ffb8b9c78e227375d7877bdbe575389212
Privkey (hex): F23B4149FEC06F28DA2C3E7979FE4567F822E71456C0D7CACB0EA05A2ABBBAAB
Privkey (ASN1): 308201130201010420f23b4149fec06f28da2c3e7979fe4567f822e71456c0d7cacb0ea05a2abbbaaba081a53081a2020101302c06072a8648ce3d0101022100fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f300604010004010704410479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8022100fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141020101a14403420004deb1fc5fd86d3e50e3b1740000f036ed9582c8a2a64208e5a9a7b1f5cbbd079be139e4649482060729b79155fea310ffb8b9c78e227375d7877bdbe575389212
Address: SPRxfrPYH1m7FNRR8QLvnJj7Hrv6Gdd9oy
Privkey: 7S7sAzb4vAgbC5ShYL4re7NtTKtpSt37Br5dogJkX3Efju5vzDX
"""
# importspreadprivkey 7QZrfF5NwiwhESwXgAEWWV1MPapDfTprnp3ZudfWY2ZmaAyWS4Q

# importprivkey VH22Bo8KrY8QaMVgPqkdF8cYzgFQtmQEmCeLFJpyMwudjC9zt3ci

# importspreadprivkey 7QZrfF5NwiwhESwXgAEWWV1MPapDfTprnp3ZudfWY2ZmaAyWS4Q

"""

~/minkiz/collected/utils/vanitygen.old $ ./vanitygen -v -S -t 4 SPRxfr
Prefix difficulty:            264104224 SPRxfr
Difficulty: 264104224
Using 4 worker thread(s)
Pattern: SPRxfr                                                                
Pubkey (hex): 0446aecbcb8409187402f0b216499dbd8350b3b75f8c0e121c1055a0f1cb217c07b533be58233c918c73f70b98ec2494dd34ad22420026b44ade724c2bc5a4203f
Privkey (hex): 1C6B4A1723CE3A448363D7A945F43C3FAD95C85C2BE1967D857C5236740CF463
Privkey (ASN1): 3082011302010104201c6b4a1723ce3a448363d7a945f43c3fad95c85c2be1967d857c5236740cf463a081a53081a2020101302c06072a8648ce3d0101022100fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f300604010004010704410479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8022100fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141020101a1440342000446aecbcb8409187402f0b216499dbd8350b3b75f8c0e121c1055a0f1cb217c07b533be58233c918c73f70b98ec2494dd34ad22420026b44ade724c2bc5a4203f
Address: SPRxfrZUffg6JK2wYXKVEUSxgtCDayyihW
Privkey: 7QVhd6fzTUdr1vzc4xWTqGpgVT9k13wuqZ6kDsjFCby5aV2kRsc

"""