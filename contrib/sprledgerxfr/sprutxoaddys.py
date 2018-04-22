#! /usr/bin/env python3
import unittest

import bittrex_addys
import spr_addys

class TestCatchUp(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    @unittest.skip("Passed, skipping")
    def test_check_bittrex(self):
    for i in bittrex_addys.bittrex_addys:
        if i[0] in spr_addys.spr_addys:
            print("{}: {}".format(i[0], spr_addys.spr_addys[i[0]]))

    # @unittest.skip("Passed, skipping")
    def test_create_tx(sekf):
        with open('./genesistx.txt', 'w') as fp:
            for i, j in list(spr_addys.spr_addys.items()):
                # fp.write("""        txNew.vout[0].nValue = {};\n        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("{}"))) << OP_EQUALVERIFY << OP_CHECKSIG;\n        genesis.vtx.push_back(txNew);\n""".format(int(j * 100000000), i))
                fp.write('''    std::makepair("{}", {}),\n'''.format(i, int(j * 100000000)))
            fp.close()

if __name__ == "__main__":
    unittest.main()
