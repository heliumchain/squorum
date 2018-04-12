import bittrex_addys
import spr_addys

def check():
    for i in bittrex_addys.bittrex_addys:
        if i[0] in spr_addys.spr_addys:
            print("{}: {}".format(i[0], spr_addys.spr_addys[i[0]]))

if __name__ == '__main__':
    check()
