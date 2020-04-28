./src/squorum-tx \
    -datadir=`pwd`/datadir \
    -create in=4d49a71ec9da436f71ec4ee231d04f292a29cd316f598bb7068feccabdc59485:0 \
    set=prevtxs:"[{\"txid\":\"4d49a71ec9da436f71ec4ee231d04f292a29cd316f598bb7068feccabdc59485\",\"vout\":0,\"scriptPubKey\":\"4d49a71ec9da436f71ec4ee231d04f292a29cd316f598bb7068feccabdc59485\"}]" \
    set=privatekeys:"[\"VKAxuBuE8NY573JkEJp9od8igik6bSqYRLMkofzQ917ynVcVA3Qj\"]" \
    sign=ALL \
    outaddr=0.001:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P
