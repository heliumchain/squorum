
from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
from itertools import islice
import time
# Using filtered version of address dictionary excluding Bittrex address and < 10 HLM balances
from spr_addys_filtered import spr_addys

# Breaks up dictionary into chunks
def chunks(data, SIZE=10000):
    it = iter(data)
    for i in range(0, len(data), SIZE):
        yield {k:data[k] for k in islice(it, SIZE)}

# replace rpcuser and rpcpassword values for your local node to match helium.conf
rpc_connection = AuthServiceProxy("http://%s:%s@%s:%s" % ('rpcuser', 'rpcpassword', '127.0.0.1', '9019'))
print(rpc_connection.getbalance())

# How many transactions in sendmany
batch_size = 1000

# Chunking was not necessary since there were less than 800 transactions,
# but would be for very large disbursals that may exceed maximum transaction size.
# Premine funds were sent in advance manually to an address with Premine as the label.
# If this had not been done, the default account of "" would have worked.
for chunk in chunks(spr_addys, batch_size):
    sendcoins = rpc_connection.sendmany("Premine", chunk)
    time.sleep(5)
