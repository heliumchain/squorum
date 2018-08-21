// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018 The Helium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "amount.h"
#include "base58.h"
#include "random.h"
#include "util.h"
#include "uint256.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000d0b57455f1d5574e80d377561d4ca1b258a80b4f87b2389695c0bb0de59"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1520801782, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x00000f4e3a8c8c8bbf2dad765ec396a3d5c13b6bdf1a0151c71e6e1811f06bc3"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1520851782,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x3466bad752fbab0a6f04c084e0593b4d138de9a03bff704e2c9ce65b1edba961"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1520851782,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    {
        txNew.vout[0].nValue = 369280970638330;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQTstaCXN3vNjSCjJbVA9Z7ecrsYcTjYKn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 45058669255132;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeMQjNgjaHzw4eebBCwzP5FBZNma8sGrEz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        // Alleged Bittrex wallet address, to be credited to a Treasury multisig address
        // txNew.vout[0].nValue = 43287087949961;
        // txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdbyXf2f1xCy5zPQVgELigaZgMusvmJNuE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 28844516711691;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sgmo2Q7CNCL8FyizoJ8wyCJkumDKNqsxtZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 27256779006446;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQ1NHaacKvSwdRqkr8YwR7hWGAoSj1FAV6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 17763816139307;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVAhrCi5axA6HLX5oJGVFMg4iRkrjaM7sN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13648686713232;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SegEX88QcgP7DK4qUFLnMrKMqteNv4yqS3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13444192372678;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STAMATYyXDQfUDRfLYrUpYUz4MXzFZrw44"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12550514178817;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPREADERvKc1xxmghRjDgTiU1Vdd8Pjx1m"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11299920000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdmKaRDcRp6aVuoeqYfZzKc8pAcX5DH9Bm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11257926353687;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SamMB1mvFbV9359kz5R8Xe4MmfLiY5XvGe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10294700000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXKrxAEDu7Q5za6qnwPD33yPQVrqDyX3Mw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10044500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSD53KPJwSeazrV2YPY6EXzn4TD4WJdUr4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10043200000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SW4GKsUZK2h8C1fGHPqoVFGW56AYMfwzE8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10037200000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf8P2fgsGVu123V7e8KfjeywB1dYHzkRF3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10033100000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMwV5cM8p98NdWrv2KnjE6SsBPhb7in7jT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10031400000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdQG5bLthc7DM5dNSXnhE3245G4ydPM4bC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10025000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYQQVVEBRvX1mG6HmRtPBQG2wnBwGXcbYE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10014000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScGmwBtysERr21Jd6VJxuhG2ZSAiEepFdz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10013400000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScZYpvBQYBU4nd8ui3G7g3fybxcWgtTCeu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9072477275858;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STwc9SWYkKi7p3mnh5j8eawevSJF47ZCY9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6777823688082;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMLbivkkQCi6ExH9o7ZEwhuUiAjdRQMrmC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6487345347510;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY7t4wyuKHV8wf5rpNDMCUde4kUVexBSeY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6406075347198;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShGoCH7WbgtiXXkh6uk8aRSpeRMNAaFpBy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6283895745936;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSRb2Y3RvRtypuezwiBv3ENPm3VVwR4KBw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5701735820743;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWTzmtsoJ9kYGz8GFHnvyfRo8NNGxSvJGc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5088666344541;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShWnLy37dqA2oxTUGYvojdLvLhmWCZKsT8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5000000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STGY7dkHN237yeDZoyfJ6oXbjkFxkcRQsU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4552403947347;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc2hEDo3Fkj14RmJJg4oYfxC6VvPvYjcRK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000448000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQrgnkJmgxM3yTyghhcHMaCHL2DM5J6FT8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3980000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVsUNu13XTh5eHpoLFgFjSkEbzd9UVcLrD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3955835220665;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SacKKpiHx56zRWyoEQb6VrsR82g67896dN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3802331698410;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sa6TCTCHwfxknWy7CKAtdhJ3Psc5K6VE3U"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3499979000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh4HGiEgLCeP1SbDe9T1FPMz7rUYEMV9Rd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3002631248581;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQETXPY8pZBN43jjsNFCdmVKmDmfYapckd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2914840701947;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STJg1icEY5EtH6iMmfG4afojkhaqGmCzhA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2810219512665;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQ6bGKHqFAMAJYxxJGGH1UX2bE2uFJoZCV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2707589658546;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbWsX5uGS3XpiT4netCT3HsXsZaxPbReoy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2532944186839;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU3tAdvXWsX5fnZ2uCTdiQH37EcBScUwgh"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2499980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSs7P3qabxWZWLAJPqsP7X6grNP6CzdWx1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2399940000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPEdWyPnrnEcpW2PRKzuoJc9iUKqbNKFSp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2209340000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sds5Svz2v8aiAD2np7T7uM7FnHPi78cHWa"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2135090025417;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYAGnRK7fP6ibFHigTtM1tLaeVUAJy7RZf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2117775258268;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPpa4AT6ESKravJ9RdhrPT8rHJ8Xd61wqS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2002537818074;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg7SzyE3oHC2J3LGaWVZgknxXoiox3pNcU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1923133025681;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZnJXTubuyF6CrQQuaqiumAVvxqXhxGeT9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1800440000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sacj8jmJ7hQXX7pf3B62tYzmqNMsu3zsWG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1766352868816;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUEfYGkyvormnzv9DTQvS9apP8nP3yJtF6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1711500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdwzydPixDcn9y95LZusi44FFmQNZ4AwrD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1600171804738;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sfrodef4Xks5aLRbAReyEXB1XWkDdYSNNd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1600080000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPrdeF1KU5CreLH2TYdnhNmZMAmoBbEynY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1567880000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZAbnqgVcfyr2UQMj7gnpDBHtLXbKvMmva"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1532820784045;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMYEacZMDsAMNs1RKDNV3SpxFC5uNrgAkn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1499960000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeYrnpyh3L2NHyzz7XDcvepXPK763sHFwU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1474340000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNtgyE8YMQ7unPZdVBF6BTegzUTDmj3H3k"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1394327484681;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShwQq7J7vEEVEhUUdmSwuDsa966G2x6mTY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1368538787911;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdYZn96gyUUFWqZEewYTZYTYsd4YesWPRj"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1174100208039;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNn2TrcSMDr6wSNJZQfVBEfc1cWehkUQCt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1169909714871;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYajZHnPyg7AenPzVqN3BnB4UrnNTfWxZo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1142560386891;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXLD6325yLuehsmp3gXL466P88FZcfdqgs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1115048905854;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRgajXkftN3LGPmmu7xowcoaMefvwPhMrc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSn5evvraNQKV6VekBMBUD7cC4zzS2iLTj"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1068666906428;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWwH6QkaceRuTM6hcfx53PuqU9Qhkk3aKQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1061140564951;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMjM8ULvGDDyr45WJjr8gSpJFeER6xpasd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1031901681481;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdwSpVgKm4A7Nyg7JEWRmc4ga2GF2Y4N8z"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1024477817000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SX1hXM3HCofxofpujdfSM9pr3q5KJcTtU6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1022500414490;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMkbwmjr2zvtbcBLMZqdW6ajzn3xYsHq3n"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1019560000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPwYrW2R47pLpkWJXdeSoWG2vYTZ5atXxx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1012960000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRvKGYEWpxPVLzgfLNvA4K7GiVE1sCz2hB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1009350558972;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaCkzQZbEJe9fFy8AFQxPmAH9BaGyEvAD3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1007406135351;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMcayWTTaxMSgk85ZMoKZF8ECAvku3K3Gt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000979999999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXo18iJS7kU1T9Sjbwwcda7nfLB3SoUH7n"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000449346293;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeTVUH7hMcnvsvq5Ehx5YSRZsXUkTBjApK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 997265817445;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbLG98vroUYKprbu33m5Hvn8ZrMKpJNeLJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 936677023081;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYUngUvNSi2SJcNGVT1ynaxDyRMX5gf681"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 921000000001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sd3wyX4bkCpUEG21kQN2fVz2zQAqchHMLP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 916064819550;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXSNp3vQtANwwwdQcZ8CuBkM15dboDJQMa"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 901779999999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNzkKRtLXHkoWzEa8kkq6aYxSSpQRwshJc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 831229999999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Shyr98NDQ7moFDjyg7yCh7Cw5oDRdbEYhf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 800560000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRover7hXqKmdvxFRqFoM5o8R4yZ4TUHpt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 745554792782;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb6SSr9L6VLxmGfCrvvDd6ySewwP1vfwPZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 648808652346;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZGZNhyTd6GN89b5PFQ4fdQTypMehicrnn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 630011499333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScG4CKMpWRiEZN1Akqo95aPkka1uSMZiXy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 609985651156;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STdoocWjbm518RiYeveMeHY6YsaoTbJfcw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 606974578099;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STMXykU8T2qNhFSu3Nte7qCMF8iKdJ2TC7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 595168686668;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZaEGTuuxCKNz1Dde9ervUqh89ekuUf8Fc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 592193877335;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SagSEzSEHpR4hfhSg3ve6oQDSmNpv1EPvG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 553112183364;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sez2aCPiDMPX5hVLenb3USdrunU58MS4bD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 526582313745;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWHRB3TeewN7Be8V8DPmbN4XdPp3HKMbWm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 523331301385;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXqGxgrP9cmedEtWAUrMKfGiNvSJXbyJ46"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 503257063818;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf2ULBBpZgBFbmmdfKZAtX9nmNMhvHGMmT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 500980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSE1iKxtRtjqzUQQcPaCpq1W14qK3A2ZYB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 500060000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQtakqnKGKUZLK5UhRqETkWAZp6P4nZ7UG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 500060000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSCLTmynxDhixidmP7CiSRzMb9q2pG8QjJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 500054797167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShW1G8ibhr2jnhspQShyobVdepbHk4rXkJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 500000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWYn6XNPZ3tW1nr5ynYyaYymQdWR6kcgwu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 499000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbyqH8Re8RrtPc3kkkfYGHXumSt43jeHeo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 481795569025;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sd5ys634QiuCyjBZPYmwzbH71Pzd3W18Dd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 480874692760;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPyX5T3idxwEB29hDwJ1CDsr1KrPY18ec5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 468205385999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaPSsVumeP1a4FCrF9m63HJ1SNi1mc7jxb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 464264456676;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVDi85iCqoSiXBNMv289C1519WPJ1pBdJD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 453191365658;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaVMUZzBXMLEmQNsm2ts3J2PWcWzCECk4K"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 435100000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVF6k5dPmhVjtUh696Hs9y5Ge5dkuwzPfF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 434569308539;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfiD9BWkgfsfUYeYKzGpVCqdzmxYp9EsS1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 400124868402;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZAz7MbDud43epg4Ggdy11jk6YRu3PTFtg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 400000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjY8Zg1YHEEH9n5cNp92EXogMErBeZJv2m"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 386280000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sd9Rs4GjDcdEAwKaY2dTauDQYytZdzo2FN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 380297358694;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNnpRMuoJF8b6oEGhj1HL4aZoVXeUoAxNz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 366536421297;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWwB33beCahRmPLmsPSrXV2hhWK1JsrLPY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 366200000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZnFdYwjeoVy3aggs1sTZz7Aryw9vRMWzc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 363131346397;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMdunBqDm8Js8svTAYk6xaPSTjjYich8f6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 311743013862;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiGZbpP2s3whtH5B1iH3UTEg5hWWn1BWPQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 310370625448;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRbRHDemckVCuuoEZE4rDzHiLKwftv6Lpg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 307702345837;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY3V5G7s9RsWAcLYfAVED89CNCW8rQMLsG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 305281005253;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSdXG12HBfc3JuvV7GruUeW1agseyMFUVo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 301937555065;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPZmZHyBdtdWng536NjEoGB5pBLNEmrXU4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 301512075914;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Si3SyfKxMnsWHg7UsqBPfEB6SxQDVu7JbS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 300980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVDzaxvW2sZGEn1xk4kv5SB2i6cSmM6yQE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 300273935038;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiKyZkmf9sNhZav74NRGqChp6N5knzsRT3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 300124830247;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZjHMWg1pza1Cbx6jJFnaTEKm7aRnRPaS2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 300108783944;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVYAmue9mTXnxtFbLfnS7zcHK9uMqjb7sY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 299978829834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf4iFeN3tP281DxpA9wjUjdwrfskE5aozc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 298767653310;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgT3K6Y9xNrNgRoGba4ShDH9vuCQr6DtyE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 295567557017;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb4UuVYiHUBuynrE1EPuEzrR6rCwvFywrJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 279176164985;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbmSpg4jVPYVRsgM3eniBAvwsGvYZE2mCV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 261909910963;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZLNV3y2hTY89YJsmvcw8NTV5pQkwfq2T9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 254881527718;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiSrqUFBhUr5mM7yGd8eSatpBz769aa9Lr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 244722789499;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiV7LwsL6bg38esegaL5Xf9c9e7QddrJ6q"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 236024722758;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbTGkq2Bo1YMmg36LKMZP3wSFjg7rySttw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 227561738795;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Se1RVPubcHzeQFgNGTKKod4ZADxJJYzpGD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 222422311860;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShAbDdueCdVuG3huNG9U2m7XFUqY4Hz9sS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 214173686923;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUxMBVrDG27d2HX9L5hhougeSjEJ8XP25y"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 210550769806;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Scv2fFnwo39Zotmpfkwxx6YANL3n8oQ1hb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 207893901333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbBXzX1VQU89G68DV49Z1yiG4sZwoUSu23"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 202019107883;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkGEigwuZtjANL7UFvud3piUNfFwXMDjuJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 201580000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPU23JbsL5SrRhoJYZocw3QLP7DSTurmbY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200911028099;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STUe9Xp47YqpweoRchvT86YS9WkPpsXXU1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200593090099;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sk78GPMQn4gBavQv6iXn9dPRYao81rCtqF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200560000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVsFcDbR1tg2qLdiKpaga8TeRGYBeg1Tv1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200383430129;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SShVxxM6Fd3Fs9Fe5aABf3aEyW7NpC2h1o"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200270535346;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRP3ouSW1yaLXW3KYrKEGEzJLNC862jtPr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200260000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgF2NuWm5nZWNMc9sF9Pj57JkaagGwYqb4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200209592164;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbT4FwuaYskqoRYJ8WjFy18ai1B4bJmRfk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 200110665554;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgymAgxXuBi913tvz6wf5NV5qK5AhaUi4a"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 199980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScfdV6dTnY5ianhJEQwSyiCeZJWxboyYid"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 192822583161;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST5c9tyF8dV2RWRGRQQe5u1kqBnPicA9vF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 192716275510;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShryJ7NhsU9j7TQfLn6vmWqiUHLEZPameo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 189980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeBd1prDtx16ZpDzfbfvYPUN45fyECoiNC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 189980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXWJvxDoppLtm62MwBFohee2qnf5NEcaeM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 183396533340;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWDCYJwB7siUHcJyFuhsw5qKHKxDL4hGKq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 177269905346;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUpo3YGDKHJn2juTTV91Hq9AVHYa19eNBY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 165892778905;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMgcztf8bXEM4JCuUozt3PJV4b7kc3FQfd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 157000716081;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRTxueqsPSNYkSDwcMvRKMuUYAeR2gbanp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 154940000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZHSdhQfq4eMywVL4iyg58BCkYsRJnWtx1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 150124605004;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbfD25TQ7pbTvavd8vtdU8oP7F1fmdiWVW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 150005000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb8d9cBP8xsZKYLi8EZev7U13sU1cbmVFV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 150000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SannKMxrqgvCV1kbDQgLdju4nWEpEjD8pM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 150000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkHiSEzjKs9r3yBguRDSbeQNoTzTbFCmy8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 147210816600;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXCzNwuHfaVAriFebZ1M71mdJSMZTcSREv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 144311728888;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SibyBjnSTWouFaBggydFGdLmBC3MAWcwu4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 143455990612;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdiG6FnqonM4nVb7wYbzFPB8FV7tgukTnG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 143303129161;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf9bHEjJXYqoeLe4eDwQ4cL1UxZBw2jfPL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 137891133825;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc3NoYjKCVdTGBF4ntoeJs4hGKedCXB97w"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 137718472406;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRpuojjNftDDH52zijqt46Wvt1doQ86Fsf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 136836924533;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXDE3krPhygVVLQXVr3S2tFktXKuy6SbZA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 136484530460;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST7QK7D91L78Npni1TgxkuNB6vCZJagCSc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 135330177609;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShPR9RYqMeBawRJWHSFEumUwknx2EHVHUF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 128228098415;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdQsHCbxM32sTeZ99ykCRvXJ77S6bmbWQ4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 127702855223;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSmDS7MzWDCMqwqyMm6gGuXPhQ7Hv5fwaG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 123765970149;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbjhrMjydXLHN9mSG9DL6TZcYrkopzbEPE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 121219460669;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRLeZMTBXXaiyrhLWLNkWtkwuu8P6c4SoE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 119039842551;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgLMtXo59SgsPEnmx5CE5gcmzWs5ACA3Tw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 118091675478;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgyyYmpE5EhYVYypDbqqMB8MpBuMNwUmKc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 114009091093;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sj4TfWF8rewYSG2L5Rw1QrRQjaXoEESmMr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 113902555543;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjCqPC5xbPaXGHgSi1rxJxTZJa3AtSGE25"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 113489838388;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUgawYens7Qwwp3djyhFNyquLFFjMuuDdG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 110000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSHUvYeyGQcV6z1QvFiu2SppKDTbb2ZFC1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 109920000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Shq9me5UXcGMzfLaMbnG5rtbxgbrVXxVGs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 109512717273;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSC6TnmALpr4AXvsTcsLwHcLwaTVNd3bYe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 107266068260;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShQ2o3wYo25ATJpshnKYFJKNQFCo7ddPPq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 107154976697;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sdxd8kAQuvwkUUpKz7wCpjDPL2WVLwSYrZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 106664325564;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdLpRS8RwwMKhMUDJnmRWzpdvi31CVp2dP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 106352355504;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdEnngSLgj2hrHPpo54p4gJFMDatfLfB42"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 106072286716;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRp7Nbn3yUAQjWA9NLtX8AkjCAfzHk5Hiz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 105730615401;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sgye748RvwK7zRFWJcbtFLprb5XAfjajFt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 104980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST9w5E68pzDPp6vXgCvvwBRtXbkM6ceWSE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 104845224401;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVoe3qbdtRuLysXZAoo3L1nLYRFGT4sUc6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 104383639982;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNbrx9mZ1uH8ebSWQhAaRen9TCBoJNVv2j"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 103932756453;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVF7hmEJV1ZnxD6tAqEb7QJcPMjBcB9bJx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 103088656874;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgZefHwYNUZGNnopL6unZSxZxD5rsstUU5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 102539750000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQpXsZ3gGLx7JUF1KaJ9YKCQm3W6XLRLk3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 102339725789;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQRzTugdrB9Wp93egzZA1XuGw7N1uCW9CH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 102204322412;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg4ZCsRLexrZZN9hxRhVRPPJ9Ru7R8ntYM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 102025063847;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdSU8m98zBMKjjf6usjwMhXyRCY8j6PZaQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 101980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShXYLg7scmMiLEm5H2wCAENNJYKWzS1MjF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 101953670179;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SimFvZetowZj9m8Q1whSWmA39Uotq9coCZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 101775046580;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPitHDcu4mR7RV9wJsczGEzmBbBNUdrkRw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 101607567028;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXMmih8qZpm6DYLsTVacBq62UeQtz4fYyP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 101227376799;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeLvaMK4P2R3CMufht8ijkpzU4hbayHwQ1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100940000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWypKb432Vy9TmLNiWoimttUda4hKYLjTf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100900000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPvmqKsaaEXDwBGeqfuuDhmaGBTh6267vE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100580000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSKJ4r3eZZ4yy1F2TnLyQ4wPVyRy4XMFrA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100522365863;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRqGFZso2XeAzN4VdUibskQHch1P2QWgNv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100428305832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVVRhyBLnWMoAYuZcp62BDjiup96TxxPWm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100205659334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb3fBgvMhXreHgCtLwHT4s4Eb234U7msqG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100175730304;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfEkaN59BTrVwNJvA7hun1c5ariPpCSh4A"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100171137829;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SejbSHCG66yqyeRuJb7PKU2Ncw3hCv1aR8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100100000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVJuCXhZWVrn1SEs2U35PYxWqq3dW1ZmzW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100100000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SX8Ngo5gfPgaagvhjeqG9qrr5sNbVf7S2N"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100087521022;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU2xaQjhQUHAAzbcxzMJdnSFcAiNjJhYec"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100060000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh6Tztg2etwYH1mCJ87V9X9Vcnax9WK1Gn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100059000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYp3ndVDUA2qHQXMstEYJwUe7mZAamEW3p"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100019893034;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMXNQtFnWLu9LcUfe1YPYnRZHiRaKUMCKz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100018710000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Se6thoHtuTsAk8dsCzAH6thRHcbM5RZibT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100016419792;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQxCWiLkqr96QzBseURiMyyGQ7r4m5UYQp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100015777500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjtMAbUmoVGapB4u6TZrmDsKMdyHECXVmL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100009329825;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SejNtqRZSxKhegkmJp7ELBkciCLe99Zxkg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SczeJv2pKJd2ZdngiLfWHRuCUG4CovPzgU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SefqALLQnHTZc9ZxrLNLtpd1xmBe5eExnq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkFFFBXYE5PucaWxcxUf2kAqJCmyhE7F5p"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUzBbmTnzzpCrDbwzCdZPdbbhNF41Dm8J4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVAPgHom9sGNExxiJu1ghuu8zNJ7byucug"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 100000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWykn5ETRHnMd6RTYuTmwRZyhHFQHiEejk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 99900000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScL2WkPB61ZD6HKE4vqRmmdepXb2prUqpy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 99880000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdNfngo1csmiMEsg8Zh1TQG2u2pH39pSdA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 99698196176;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPtcqoKEuPXiGgRcV5AAun7tbaD9speXex"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 99388836500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQjKNTPCbJkNrxdnbM3ivqKhxkzYyyRBcr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 98025748737;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShxbEkYUCaJAqNLo7HojE3RYciwgJzsqtH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 95080000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUrt4ffP6qkp7r9ZtZFRNEz1WZRmsQU6QF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 94940000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc12hVa1hMxCaFd1kyyXpBPMbWBMV34koE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 92999600000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRHSEwUvNAawU4LtNioNGV12D6PJZgRBjX"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 91603228280;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjVhjABex7sh5bcaUrTcgKUrJZp6p8kjGf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 91172592885;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sac3VwY3Nsewo9xGFn5wiSNJGR4HbqsRKd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 89866415781;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXozTZB68JA6RfncH54qNC7Jd1fYGoxNzz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 88832059872;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STWUhopCbuhXjkNv2pALDJjGyE4VGnEU6u"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 87700000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sd3bPDEJBPDwXKJ7WMh44LeVjjgVE6xGLb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 85036209714;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjkRN4byTf9hWrm66T1YRX9F48BWRNjiSy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 84762478834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScETxCHTMe1qhvnizY9546H5RmZcUWnASf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 82355094504;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SazwsFkxGuGs9CQ39J9qxYpwpSfZXHG1Jg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 81764795826;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf4G4oRhooAJcDPRVgkNJL4uZXRkpVxMAk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 80383604302;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXqjRgLmvLVK4uHwn1CJWBxXuxDPmJQw7H"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 77292933466;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZxu7CPmw66kraLh1LY2eZUPyi2FPTxm91"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 77000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMdqSqXjFKmya2DUdjmTYpBJt5554jCFLq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 76846266492;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZ5M99PAZPm2X8EursjZ2F1DfkS7AZ8TBU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 76332707060;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh3aqkaTp75VoK23wFXgMKbKokn2otHvX2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 75660000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaNoKou1o36zJZEZrpk5tdrTwYcAcstZLu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 75385754138;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSVb8hvhMgk3fSYuzUoV861FHyg1irewLK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 66000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRZ1UPvEtSYJqZ15WbeEBiShY8NtGSB3Qd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 65396170998;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sbzv5Wb7HakYUeMQmFFNEyeNjdCGZQDeTE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 65285000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STdN5REUCViBKJ9pDhXqFzy8vJ43GMAqNy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 63411206666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYUknnmUKVY1ezCzgXnLRevqiv6sP3FKi7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 62525390335;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STMsd3zEYtgjRC6RMnNsBMkbFWByiNGjED"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 61623303000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkcYySpQTLAFtvddT7wuKz611xGwK9gwtC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 60000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkCnuPe3XpKLhNByKb6ssFP33o79SDYZDK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 59368786600;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SedixBSfzuo8KB1eN5gt6eWxovu93vbnaY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 58720174701;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPTWbZj6fvbRnjshwSPQB6z4zuNWRdiQkP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 56521708972;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZMkzRNayQy9fY2Aa9CuvFJWCS2rNz6dss"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 55552193166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPcQ7cpXfG6D9BdfqyrfWn4mibHQBcpaho"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 55253581190;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZHRUsuU6YBD2KeNmgqzDyWS2A6upE9A9U"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 52984699734;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbL8t8bDBKzazS5twPwrdd7THyQ8SQbCKc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 52161563005;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUe4RLALDbT8PSBKoYnZyoXUCAk9svwZrG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 51800706658;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQ8eXkmQh9Nf4iG5BVSJWFw8i5jsxGMVW9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 51484055986;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjqKBAc2scm6rwn7jyEF9gy2YV7LSrNXJW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 50157879829;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPyRZnc6CzmnMzJVPDxATKXtKHXN1dPbR2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 50080000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaoiZBHkPma5o8yeFwq6s4JbBa8wSA22FQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 50000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScRGgwcbkt8ez8TCQMfEr2GFKB6nXs3E3g"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgVToP4G9iC9rVRmfiVGPJ1aRfpuxPiXhp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SR5VFS6LznstFo3VAotMBYe6KoDrcHrTSw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSZemVv8uHWZBqvwFZNqXYP54UvQD4wtr1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXgBmyszieSLKTZYTnB9dVmtGDgkpZK528"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49979800000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWCQP4jRPHzV2DyE3WrVUJQ4rTupSfGUod"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49960000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVNfH1swFNewibGJ4gmXC7zNRtmfy8Yfup"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49389873600;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh7CuC1wmFYo3tMYW2pzKKeKz7RFWoAvyC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49377893790;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgVqL5nrxAkq7R3AroGoVAMCAKU3oYSG3C"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 49368874700;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXH5spD1Phj1g2QJDEtQL7Pbicdm93xckx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 48767689000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SW68n8ZQvyF8K7DWLiosSpVcSKkvqVN5Us"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 48423505522;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfTfBQhsX3ePyqpfV2XP28YAZP2pdxrxyM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 47174210185;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRpwRPCYqCXh7PqTPuP2rzaLkTU9RUXHxm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 46973770889;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUY97fb1Xk7NE5DPSxGVtrNMDavbpbMZmz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 46939047664;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjZHRyGRZZ4vQQb6x4RQBqyUa5XA28nRmK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 46254026343;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sk5jbGg2V6xp22xQgCXuqCfYP4aPnfs2zu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 45649624953;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVh3cLdyTZzHA3z2BiePNC2Us8PUCboLTs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 45267359700;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScEBMzpYfNUnQ7CQUqQdHGkGFFcRHvGwC3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 45238606840;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMraKqoh9Rk3SNPgboHYVhNRfcfSNRzZPz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 43762165908;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST7k6GEkyYdoxb93uv5Lq1r8RxCryLsuUW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 42787788700;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbEHWtMWUcEsQztJGAqTPKbGzuyxQRd3aH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 41003000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb8MNN5zTc3FDkP6qR8bJ99ruGPA7v71e2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 40538400000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZxTnagx4Wku5WFJ9z9khyGKv5iXEk2jhk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 40021500000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPiCunFXYxZudC3zgj98xtwumxdJor1DCy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 39388763500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPE1Cd3fXbzdhNgZwyqjfbig1Uhx3axWuA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 38641846005;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdQJKyM1f799kxw7FhbaXecngfjxdkyyYe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 37865178945;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXYteR9BR2ADA1YKZHSPy13SA3V6zGsbrp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 37292351832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRWWayRg6Krn6b1wLFkzoyt8ap7p5LDzTm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 37285208000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQMsxvg8FNrpdk5maBfSFbHjiGwUaLJXap"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 36053778833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZGiCxETYS2ov6doiLRE96LtTCTV2mRtTE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 33492951677;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SciwV31kTkbkh6Tcimbep2YvRaBW1o7K8h"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 32475150832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZw4kKxhWx4xcse9kHauzmSWZzhn9bhrc7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 32100000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWfxZEqRXE4n2dQ5Ut7KmH5VEM2xSYhBDo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 31479248894;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNFcKCmpvhfY9SdiHePHHUb7nMwhbaNqUu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 31239582499;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SR5UtgybNzqHusuS5kk6iZZ8P4BaRNLGRu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 30900000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXmFWUcJA6nNbLde6mmANa2AvoB4iiAjpT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 30646082164;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SatanDCUgGoBvbpqL6DPJq6avSetg6xQLp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 30397089962;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMvA3MGJS5GvBN3XE2FxX1cVCgfogoh1AL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 29772632999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjdzrC64jhbfbqoRQxbLjjoTPbUKsNcP55"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 29209649001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPQzr3nsaWSxCtrcY1M7iwwaUz44DoLNof"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 29154680252;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbrbBKochsSyvUUs8ih7EMGQWyYUkpfHDi"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 28250151332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVhTULydNDTnhCveDybZXxv2i9szW2HmyN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 28215652061;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScFRBL98SBE5riEBRUodoYhnT639arLTvB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 28170155828;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaZ8yZG5zrcozALmuh1zNvJD1HpSNQZkus"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 28000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZQdM7ibEajrCzDjH9bXapNrz6doqMaX9B"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 27371486778;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbLwZ7X7FVGt3yMXbTwsZoGuYFa8dDLk6q"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 26835769231;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SafNyqx3wGmDT3KZchMQBD93kqBhinuaZF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 26650028998;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQpvjJNHwEFtxuhxduvM72GusvpF41o2Hs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 25680000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRFMGWAfxsZFZjsY4QN7Uxq3mjGmi4JYST"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 25637030832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfNY9Mk6nNwzZuZWvHLxZUQDwsMXq8AVJL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 25127997669;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SR69KUjxZGV1t5aA6TLEnT3TKtYaSmQeFB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 24213391335;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYJQStapNbUfUa1qHkzh2VUMZAz1LNb494"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 24077239365;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STm57Hsdq34Z4YbeBGtGNSLgN8aD68DJF3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 23894862500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SidyBbYLuPhRFZ2djoogxwth3y8xNHLaYJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 23311555667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SX9QSGoDuTh9eWTrJQxFmr9qRd21gnnu1S"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 23174265667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sa5S8qTkLjesiQqTtJUaDMKwnowwXXT5oV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 23001001616;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdmJeZ9ZVBDs3MoKi4uMyFYLv3JnpxP2TR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 22987975835;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaasqiwBjj7Eo2YzE7uKucUcxHqf3MjhCF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 22393286834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYSbdSdtdek926SQ3oPrbBfhpdrKJM8F7P"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 22380000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SipxPo5WhWmbjZUgdKesoHgkJqfGAYRDfK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 22180000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Si2gCdzxirjHVzM8sZgtx2dpKu66J68mpg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 21980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRGmhQU1ju9D4y31mEqi6QrTAcqcbxHun7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 21184006625;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbD92UkdAGoxZC6UM3wXWqRfdWsJH2uieC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 20717741539;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPYegCJ7JgMXHtgFwpPCSpMPSBJRvEAeDY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 20552733168;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Seqe4X55o2JfdFeMBbhSsNVzf6Ub2m1pQC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 20269763498;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNvdraURkoYJnS2smZw1VMw3C3o8sxspAY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 20244717168;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSgcvxRxx27oQMg6xrEstWEo5CQtgLjz97"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 20000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZd9BLL3bmgps6SJ7ucDmq5JxoaBiZN4c3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 19980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQUTJnRu4X1fvHR2qBAhb96HtT6Qbsd6zH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 19980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SR9xYF7viecj8DHibTEP3VXSRZUrxGK2SL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 18771000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShUcFWGUFGtdkZAVAKU1A5YXDTYJMiQb1L"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 18600000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiSvQg4872YMyi1taTarLuRfhv6CcvT9WP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 17542362167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNXwW65eSW762wuCVNJmv7tcAbv4f5BMab"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 17080028829;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SV9gQKfw4oKv1W1WVrEUCHBLt92j1qcpQe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 16941112166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNzpEWYSjEw4nYTBwJCAQN5u1EvaF6dRcZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 16881000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWPmu6e6NuDzR5RtYDqGsT6uaLjPVnuuk1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 16860929289;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sif4GSZz7KotNRgAQsstRZYNmtimQer6AK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 16816985501;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjMN2cuwnga913uAdHqux6emDj8sbvvrRB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 15990000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZZ5bgCzsiGUmjF4Mi5fYRH6Lr9RQas3qR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 15756755834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNsKWC8P5HrMnSbCSZXKo78tTLiXWH861K"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 15561625501;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQCjTuLEnJe2dstrLSGkfhdBBkd9efwi5H"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 15069278666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg3rStd4TbiXnoPxxJVsUXYaDhuKf31kbM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbKZzL7ReGfGM5WvazqNHgGp7HwKKWSgSa"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14964399832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUQkezTRiiy6TbP1RrkUwdH1nebH1rrVdt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14868281167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPCiALEAzGPkGDjHMt5wUqKw7sghJkGj7u"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14815689040;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SR4xw9ugFRqe1U2HwYoCdjcPdUt5FYr73D"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14679936500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STmEbEPDz5379PKRdv1tWL8SbWUMRB3fHo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14336799951;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SP5N3SzDz7RRt3gHpjzuPefjGakRqSyjFN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 14319759835;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb16sRoHDvQoV2xpR82VdoELxa1mpdkgn8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13900721091;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sai1E8U2FH45jWmiojRSRD3N22wSUbPATH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13752532805;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STMwVvrGhe5YGq3vW4NA2NCorr9mn2ahb4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13452253834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXMwdwQXbhELG8Wh65kYL12DvKXPBZasxF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13077453832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeJQoofCsTSfrrnYtbPXrLcbbp78DNuWxS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13060000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdSxiUWncLf47KNkjEiG1wieb2hEKMxn9D"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 13055311167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SafL7WvyyXeXv2muJP3r7bbjemwtx1PHJF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12980005999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbDGiLncoWXXBQaUUSWDhYPyGAszKL1yUD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12650307001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY2GY67nKCrjeeNBakAdhRKQxe3WGUWJ9Y"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12244872669;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScXzdLHpBfyLYKcTntihntKJMhhZDd2HMA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12142697833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbspLHPVosdt1RcmS4nhvkeakgtVyfbCvB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 12098684500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMihxchkGCmwfe6wAuAwNEo82Tt2ufp1Gk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11512481834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRf49hvyjStiT2GGsPqcryCXHKgDNoWXbn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11135018834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SePGZyZURd92ptMAjsgDRZP1FpkN8krLTJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11098258334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbozAQCooDkczUrQCcoH9ZTbNVqphBvrLJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 11042002832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SesrZba4y7UtxnvGFsmPtJf7Saj1H5B3CU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10886047913;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPnZXGYB3ApsqDDgfAqZTCrAsAN4tCfTfg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10588127239;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPLjqRXscbQ7CoooexGQQurUXyzoVq4u1N"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10563358409;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXC4YcPQBeKc6SMcx49QtPv6r3HV7rbfxT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10492022501;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUxfWU4xFm5KUarc4zbxJJStw18JfRb5qc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10299089694;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SS1kSybbe9KhzG1eafoP44VeEhQTak2ef5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10219289499;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWRr9K7ondyQbSGaH7yBJUC9Wy32mDNCrL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10115622318;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STRdEizyPqHSE5DvsstULcLsBo84b3nG7d"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10040069323;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiGHXmnZcHobcP4E9tVUWY8THWojzKWzBM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000622318;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPGdGfrxnS3JYLWtuSGdQahWfZpBELy1er"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScwMkt4kuwHfr3CG5vrPpBXv3G2Z5rHmQb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SguGH5EH5UAGmLrWpq89UTSBU6hZS1yULg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkYshojvq7psMb2qqrDcB9vuFgE2CG4ByS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRgFCzSgidCwAe8i6MYz3oqMx2RBvwwU1h"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 10000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STyvqr2wJV25yascCNafQzsCRY3m9Xhymn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjAA2ZvXuuQgn4bFnJESuaKASczPBB57aE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SS7uvQtKBcqhF5fCo4jpjdF5uewoZgG3pk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSKPEEimLkf2EDCjYETWQq6J8qdj2xeBJb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWWPwv865aQV8sKdfyAmYTTZDee9UmscKw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXBwMHij4bmuuEqh7it5cXZbgTVqrSq9vK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9664755038;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUtL19tQAa65GLh3YJBghxUGMaZcU91uhY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9600000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaC1bFBQavM8k7MzVwJkBJQScfrtEws9jJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9500128963;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Se48EGTP7XptWu7h6PrGfPZXrDmtSJD3Ao"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9415795001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShjYLJGAFBMP3X8oMAzxFTAQCQ9p76gNzz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 9059235334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaQtbsd8vTMtxTTzVf4uPXNUzMQGQsDx8P"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8906399524;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXCrM8fifbFgmFLCETAwdrpJxYKehV6NVi"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8665856166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPnJx7HpurxR1Y7N8hq1dxYLBv9D69zYiq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8633844500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SevYmiwVdGNQoEo4QCeKmAmQZuyLNt6Vja"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8426035333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSF5uaEFJUVggWtvDookqV8H78QPq4y7rt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8351370502;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY8vXtafYSLvmqH8qQCuHAD61kh7sw3GQ3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8158110667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SW8MYMzU8ECS3mMcGD4WzFJFdbVNkvSbHH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 8000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Scmhgngf56XMEnh1q2KgM7k2SKeFfpvpAF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7833638318;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYx4wNnDq9Sh5JHMGtnCvqdfPcd5dZpByY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7823897166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh1LcfBbFKrmyFudAKZqgpLoR85JboeUfJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7800000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SahBWeMprA1vW3LWsVQxcCX9N3awWJ1hz3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7619423668;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfTBrACCVZZw7eW3UV6kEXCSH4LjBZxeXi"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7611221334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbWjeXmUfqXUpqrmKNyP4Hd21oXWdwUhvg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7605967250;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST5nSHvAyeyMNpQ8r8ERAnXhyNrgUVb4J8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7554451666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQQtAebpwSNkxhctK1hkkJtXXFnfRe3TJd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7535040578;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShePKBMMTzPscT3QBMEkWCDhYPRcDVrqjH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7120000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeRwBVgzyh5eRkgvtr7DuZCeP7vegETjjU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 7086809443;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STmVWPT5fg6i39GmtMbyBZKzgEocx4EA1u"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6922254167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SN33h37k7TV97QvLbj7iLbihN9SJrHfFWH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6861880001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRVzXG3hhLM6txdSKkdmmTG9DEgWKj7r8Z"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6741581166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STHueBBwbYMiYxNr6761MSA8tUrwFY5hh2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666536667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgumDYwzMk36iXh1x8nZuSWcBvXnJokMvD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666500000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STcc7ib5VzGtVVwTeD2kdSX6zho9RAzMXW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666491667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNuhnT1khC13W4N3iPGaYV33Gc6tQtXao3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666478333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SayVe3t7zFNE9VHzZsMmNWzVMG3PWxFT1Y"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666428333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUs5nWs1df2nyKMmj986L2orY7JSucU1Tt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666421667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZj5wrAMA3Gg5CadS2pMjm94au41ss5h6F"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666406667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSRnWXpwsmuxjAZoxjSuJ7hcDhWrMqyTJQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666378333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVcwffV8pHTFefNgW4oJ21NVg3smKgHCGu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666376667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SffSbjsKKnkHdJRguUcmqtRHh6fmRcptea"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666363333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdZTvWc4ZQrfMAQWZ6n6h3E3cr792w9pDT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666358332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjTuFVsydKs3nRiN362NYdhJ5BW9uKZjcV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666288333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkVavNbxHbHwDtfxTqUyq8QwV4GHyTzj7j"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666158333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb9rWgJKPfZeSK4jsat4SwQSnQ7eUz1Cs9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666153333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUnWNMmfs4VDVX2ZmRR1PxvLYQp3Vn6Jpx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666110000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkTr8WWuwd5GXhVWdHBdyBBxpbZYRSiYNj"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666096666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVkZkg8BuHMTudwTcAC8Rnj7gn4rpdJwaK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666095000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkavegxN1KdatMNjSZ8maRb9frdsMWZNmP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666093333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbfDputVM8QBVYH1eNiuLuXxjDQBH7rnaP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666050000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUDb3BEz943jbB4ea8KFHkS4wRCWmx4NA5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6666020000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbDT5yu8keKoVH6CCaodyC8URDjqNgDynR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6665956667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRRfDFC8P427tSnxoB6w4c5qsZedqTRWE6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6665918333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRY3c6ap1TZZVs6kJQ1MBVVgkLGSaQmCbp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6665888332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXuqzeU2jqm1CbyfppgERzNVj3WeD2Qy4d"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6665273333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQbFNPoizE9YukGLpXB1hM3NWEiuiVgJXK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6664390000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShsWkPqCXwH45y4R6Lye8dsewomhqF3EeY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6664048332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SepEBFiQv9So62rvmyiC8un8BmChSqAsht"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663885000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbkDTdG1weSX5EC5zz7BPRRXkPRwhaJmWL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663755000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXzjiF7Bu3SrYGvmJskvQHgLxMPg625ZHD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663495000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPfhAhJzVFGrpKGrzDrxyqzMwViPmX9gpA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663493333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Se2XDu59UwL1RQNVmrMXKYYJzy8fJYcacf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663450000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRakgcLHSjfGGT43DguP9Gd2nYmiV7Jaab"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663430000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYfrXUrfDWYYZrF8wSymmsWuiFKKfnsJJo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663416667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNcUrDrCv9QtNH29CKr4Bd3RokUbCzFbeg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663413333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYe863z1t5SiNYgj6SVpYLD7z5brgf8pjC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663405000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQEMNQyHXG3j5dSfXfKtQEEcdbe87TGKxF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663328333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU2Ez5v5vC1dFAmCy76Ly3SBmGtUgx9Yxj"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663325000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjijRgbwJ1RsqjjXL11TFmhBqX4NBxoach"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663320000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQeuT8FW8cgRALuLh9qrrj6mxUt1izxDLV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663310000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQtth581CRTGTi4fxmtiXbsNR9Uz87DZfL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663215000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sh1aJAWDrJyC3bA4vomRi9xeh5i4NKsAf2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663209999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Se1TXXXoHapT3Mbw5KtrLLCaioYBRyhkEY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6663103332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgPmQCZRa75zEhcGnwqpE4dcPrKcdZRusT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6600000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sb4Sc7CHG5tVa6tHUayHyhR1tuyMni5gah"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6592022000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SafAR7ZyZ7oe6QGFyFM4pYxJs8aeSATypZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6501743833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sdq1iA9UP6k2Hzsw6FX1r1yASoci2x5eb5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6324414745;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShXNrs1A5tT6GPuyDDHSGLkRNSMHeDuqB7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6265956333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPzJyEXHwwYBQqPVvH8hd5jupTL2dT8685"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6084296000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaK1xXknNWSCrVsXetoCFUfbafY1NA4FG8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 6000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSV7yzhbTbbNh5vfjPXviCGGb9vUj3ypo6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5971661167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScuHuvSvf22LyLkEG2h5Qr9JVkfzxTuvcZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5928000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMP8Xh5X7XrjLYt7QhqaW5usi8noCTG17S"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5907181832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjMihKhaYpWX9gpkMCKj94Sc4opdNcwACQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5890000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SToB4b3GQ4XKDvFyZHTYQJYi2aW1kZ2HMe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5885211000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbMWJV19JoEnHKd8NqYtJ5K1qkgG2jNZPH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5804401634;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STpMkwnzsw7J4BwHB1fv33zSuFHUJchYP2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5792218834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVPoEsE2UaiLLPiJz6ehQMdasbmaaVgT1i"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5791270832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWVkQZep53bBzygS5yoK1yYnme5vtPcAbW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5662448499;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWY1aTKBUX7FuephP7zZaSdDxwMTFpaLVY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5583349001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQD2m982qNyea5fCRYcJ77dgxLJQxuZg7W"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5131506999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjrEYMPXK7TpmtVEqpfa1ehXjqz8rZK4wJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5101514833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXx7AMAVaPyazRYiEc5824sHhXp2hsDdEw"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 5035412810;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScZgtMHZj3XBVqPk6QmwhdJMFDDsmRCGjN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgZR9edTx8L9JXq11dZX5Jx11axdLVx27r"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4968387081;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPqLzr3yvdSzyRMjqvsAemffbfUeAFj46M"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4959522501;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgXwyttYUSwg899Q6Yp3DdbGnyhRR9sZro"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4952145665;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjGZYcsT7sGyMDJS1WkBus3RKztfh1Ghcf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4830222826;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWSwdfAv7Z5Ln6PJPaeWywkVcnmaDCpELM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4767366552;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc1HkWW7RwTCkbssTfvpKaFrpYkHVbfzXM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4718376500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SP3BpUbS8vavzadbNxUZq5NLmz3Cmc39vp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4712397666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STdfjnFKxZh6p1gyZMFqz4ipf5dgrZ6nPD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4700000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbMxu3c3SoDJvwJxKGjGYr4CnP3cjLzm56"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4619516254;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScuoEeBp7nKTG9seWjAawybC96fPJAeHe3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4574642666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVtWbHrQkkx1r5kS8L1nk3mdrkSXc4vCGR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4491161001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjmP18YwsoRizRFmgTzzjUAhRrjFTbQQ6D"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4482061000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkJfFPLi5ASvEkD588NhHbtA9YQ5vDyczn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4419641332;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc4Ad6FUBuWAL9tagi5xFirFWLiP3PcEoK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4394581000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZC6rFkpjHQgT3miFbGtUAVAMBYHHBMcTW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4382129430;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sada3uuWch8MgrSnUyBqoMCeFJ74hrEfjp"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4355562834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRSR58qG6oGKk3Gx67tfrvFn2zd6U7UAuR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4321364000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbbkyMbeih1oQq1YTe8RKSMTpaDD7Y5PCa"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4279999999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjzxqtVhNCTapwxGHpsrdexTMAXDmNx64P"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4099782333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNqfjvevds5V3o37wQGsPyTtrKg5euAwbb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sbn3ULS1aYyiAVQYP2CK6kdogLE9kX9cmN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScCQunXDbmgUS4Y7BJw3a2aawSRqqNACAs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScWHci2GNDknAgzovLowVqioNRdnMw9kf4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdLi6hZfyXpBABAsLEp8Vkx8WHk4Txf3ir"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Si67PPFFR1ydLYvXv8jkuvJh8fqmkXQHbk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkANcXyUfgzdUGSyX3UUaxBFRKkYSD7jFk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNSqGBDV8cbVW16nuj5fsBPrEUtEyUqcor"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQp3A2hgft3jDsMcf1pAGjwJrewPWi3q4p"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQUWAMnQk1UW7aRtrd9dUggs7cgydd9kPL"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRBgidjnnwhHTzQisX23hnPgY9tG2ZuPqr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRey1QcXg6C3eSLW5xFkxN4PNeE5depfsy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRhvjK6orxNFTQMJ2auYzCGvUP264ZA6ok"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STw3aJJLeEbMBHbDQpgw1sdvdfceEgRLZ7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUjj1zYuTRbsE8G5oVU4fHVU5B9pNExEsE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUjNb84n26CtYxZFmvFxD9bcXtoXaG5fcN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWNeULb4gsZDoqupM6miqmSKTSgsVru2Af"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXgiXGCTxVgV8ZjisHYSmjHyXXAcrYi4ad"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYdQTVXDycFitewfqZ76w5bWNQHzuaNNhW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 4000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZgqKtmypzsS63otVBApKjArh3PPNrK7kD"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3979999999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfbguAg9eAJVN1g2spouyDAaCtj6qd6B4t"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3835069248;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SddhjMg5o537cpycWNuvmhoLGEBYVLWjoY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3619603714;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWyEv93SfAFeyaDtHQo5GjjvKqiizVVqMW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3548538000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sj7bBZtdEy6EZ8TVcKiYfyNAQBCyKkuv7i"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3533412833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRKVgx2sAa9Ui9h4hWkGrZGAVqudW7b97U"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3519410834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScgPKz4qCgW2asNyx5mjaHCbiT5HRTuFdt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3360000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdksV5rcz7sL2JrP7zAgpJGuUhwb6uwS1Q"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3345248833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPrzocTxgA8ciDpxmbgApnueu6wMV8ZP36"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3202398286;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg8zFhPfCJBDqGf5EQTLKoPQcy5LazfcDo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3186004001;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZ2xRvc2KBCbVw37xozugdU5SnAMz3cfer"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3147914166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SStLEuR12AhVRfJZe66iLtKmeQD3YtftEH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3137166999;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SScWpFFaak1vtyDpW66n3SrTVJMQzong9w"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3136780167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXuNYD5y2L4WNQrJCVek5R3AFxU1H81v1F"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3124127666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sf5ZKVDN8ZwCaZJXng42L87C79Ub9fnNVT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 3000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc5KxnJ5A2YBvD3k6uPQ8JQiGxtWJxvy4S"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2942731667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg2YS2qRSR6PJC8SPZMU9rDwpW8c7ipv12"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2928502170;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbqYdqygpydyTTFYMp8aVsFzcHeMPkrmr2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2806437501;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYixVPZVKpxgJbFjwufD9ytAkhWYztfhn2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2754859240;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkRjm3KrVteMjhoxHpxHz6uy4XtaDmsRCG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2690057333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiapitATwLifXfPAMjAqjUCJF66mCTMW43"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2667523508;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdmLHaXfP1sSKmGqpuCX9KFnQKKb2oX9uQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2611631000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPHyZDfrNwgUczQg8AK5yENxgyEUKgUbCv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2564340998;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPhW3ENaA65tEJurgvnTEkfb4qYuu78t1p"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2539177667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfxUpHYVdjcMMnu3RVKrTJLRDyZHWFfqni"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2528490167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SggxSFLHK7MPEzdrttLeqUQv3d1qf73c42"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2516580737;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ST9A7hMJyjyewYBiLYwqqz1AXybXGJ3wmT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2512961833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZvp5HftBYfgJLs2DNKFPeEzgbCRYdMC1E"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2481163833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU16uqocr3QqxMTnYRT1XDchpd6hTRmiq4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2355775334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShdEqErWyisS3sEWNUorx4L2EAvFmhHzsC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2354368835;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUjBBhvwM9MR5fuqQYWm28a5LD4gT3yXE5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2334486833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPmfZvwefXWdL73H9ErnAi11hogVnG9ZzQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2213323428;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdMRDwdYUadMDFTAggpQuMLPeRJ5oM1soq"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2152922333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZ5yfzhrzjnQs7FpPLTePwV9yxWsAsaPZh"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2136224364;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sbw7xASTefSyvwVreHTZjW6AYHjc5TD3jE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShawkA1Lp5G1obHZWtEvJdndxJWWbc9Uv9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiVgAYE6XZmPE5LUXdNXYXhZHsRand4WBX"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 2000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMyeG7QNzACyzKSLWWbUdMTgecG32jcUzF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1980000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYgB3mo13NpHQbMaScH37CiybdXEaSYVhx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1976010594;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY9JWS81BaFmMQkm6pDv17Xu1LPQQ2omWN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1972564832;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNHvqtFFzNtHYo1rMRWDEFco8nUH3RRiH5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1963071834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXwDYAYP4haEADbKZjuLVdVseBwHQ89FEZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1963062666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWeMNYdSLcE5ftUzNquuQP75RfaTMbT8Kg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1958700000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXfNAD47Et4V36sAgcmqK5NTPQpEFq3xxQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1940111000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SV6SdSbYboEw6SowtJwe7VhWAqXNJcv4J5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1923273833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SkHHYA7KgUgSoxJMxPB3FrYfkKriez76Ei"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1900000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SasyuGHY1hMN9cVZ7JLZqVgXD1u6tDkL6c"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1878830000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbBLf2g8xXGRKAwKvgRmTbHEfwYh5UzP78"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1875395833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSccJMp41KFG9ue77XsVTy2TUaPsu31Y2S"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1792096630;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbmrbXgpiMhWzA6k3SaoCar6hEgD4mj9EE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1661093000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sk57NoSZHM1EqztkPBKLEPPKHarXWJ7cc5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1623353167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaDX33oEQhH5AKNVVqbRspRCDPGC2ujASU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1597187167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sjc2TDhScmHt5jVguogvvoXLHJbvsCbg9V"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1588420833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNY3SnhXCov8mHj6d4RBP1CMkmdieJ4sZx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1582897500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUnuUNz64SH2fRToTuFn1qgnKGa1sjGF3w"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1582477499;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUsW5LPt2RhBTZQuvPct4swukXqi8z7g37"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1582362333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXqm7eHQnTQgCVs3s2qeX3mjESaZaZB2zU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1575897834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbtvGBYNLMXdVWJaFW9o3Ei8YbYsXdGUp5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1574746833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfGCoZv7bAAx5C1xtcMEHGZ9v6gSUR87gg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1566065500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVjXdgbBXPdUGae2VC32yzSHMWyTPQBoSF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1512281271;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSxZp5t3nLJNCHP8qqFsacGe4dB9kHiC7K"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPa6h3s5pbjm5CCSjY4pTXj9PoSYRM8wT4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQwCQgdkELGS1HV7Lv7uSjjVJcVvMURkbo"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRsqjJJkMPSf83cCmdZWPw7cxiahe6iYnP"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU6qYH3Z4G16Bt8ijP2uYw97XfADk8P3Zu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1500000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZT9NanJGeA1Zzs6t28Ghv8TcNkEXe7Yxf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1302337500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SP3HYoAFrr6kgctV7gtADPMtkFU7MAKYVg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1302196333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRWxAu3dGzvT6QZjDhvhZYNEvS5SN3Fosb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1302194000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STftY1ghA6tfaidc5mFt9LRWyV9oy7BmpV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1302137000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScucLEAe5Gad32QqqCguEw67D9Tyi8UXuE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1302038667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSk6ZeRUFpEoZfKFdPazLqA1NfbY7a41Zf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301890667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQHnGMPmmUTd7WyULimYSt9aXVHLY5CDuW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301873000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShBRVUxZ6RrDHhaL9xVLn42J7ApJshVMGM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301553666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXhD7Xg5gCTcRrKzG8oRctYT9mFNUzGFo9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301495167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSHrPN2tvtMfbeMWn8xnaqQbL9yzJ1hnc6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301404500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SV9L4ZJ2rXgCgvHPAapZUUjrqDLqpwVmu5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301265333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdRULdk99tt6Ef1h8Jcj5C2FUw4PAreibf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301233334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSjFXNNw1GV4fBWaVT22roAdinN1tnqLkG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301170000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVduWMM76ydXhC6mMNtDNZcjwnsqPH7hEg"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301087667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVdwKJC5N1zqYU5yZUg2rePodh7QWJm5Qe"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1301002000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZCw6Wb7VzdQFK2VobpWsAeBZjAc3LkXNF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300991833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STgCxxM7Z1FaB6baqMbo62LgrvbvjnZ2Vh"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300967333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWx2z7myKYzqGE5TMdqSrL1MEa1sWxCpPt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300880833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SeokcxTvFpkeD3iZo7A91o4hRVKtpT9Vv1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300755000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWpreJEWF4h7t7BXovRQxtobZuemeuy6Go"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300738000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgkW4y7SZJy69eqJeirx6VC5fXybEvAfiy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300670833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbLReEfhRdRYYbm3v1ULnxDbzU9Y3qyqc2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300304000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXQKr5mGEUxRj3wukt1EDiDtXYgJTekp3V"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300274167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPr7kfEBCYGGUSe7Mp8rFw2h43WuKoRciZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300239834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaV4ZwFEDmcuvd72ZxXffNWN7gNPFi1Q72"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1300231834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZBt1ZZguU3xVmPtwgLwaU2DZKuDqn5Sf4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1299941666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMecy7XST6UzPZG3uQeBdQvobwY5fqCTeW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1299613666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZX8fGmpWhnfmVtQn3tJ8ZFEtAhKoLthYC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1299584500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScfzNmyGa6zkQgvc6b76sKZMckUTG4QTJk"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1298370167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSMcn91k9hGS5KJs5zJJFdYvMkqKejCnX7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1298238667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScYNp6DszX2E1of7A3rgchxMAGDd1Erpxv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1298128333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVqENeAya5GuqrgUtrZVxTdMUvUW68vf6G"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1298115334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgVaUG79ZuCYL9EUdLZm8ciFsehGDAoLj3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1297570166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZPVGv9huQKdNNKHFQPsRxQZ34RdDwEnU7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1297076333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SU5qQ4fGZMNJ2r2vyaBYFZvZrM1DdLDARH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1296944000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sd3ijvTvQjyhr1wb9o8P4T6Cyh9QoXP81h"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1296851000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUP4aiTkswWhQVdVKj7KU4htetuxz3paa1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1296368000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRLTB64riFkAPD5rzgxfaXdGHPRAxC4QyV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1293557667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXw9Do6HS6efcamys3ZdGQvtdzT78QpvPV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1293537667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfRJzJh5TJ4okbJezxr3mRgfmYCj1HEYd4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1293320666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUK9F2E32z4pgYEXjgBcxao2m5jiFe9i6x"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1286359166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SXWorE1atGxLQ7iFQeMBhR48Y5Aj16LvDn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1286258000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfPw155Gyh8XFfFUQb1v21rQw1YBTiq5FK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1280044167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUpgCHb9ZGz6LFvmhdy8HpuUtMQGUnHCzB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1277024166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc1KMU4G74egsBFXLMqZk78NgLt86frmtH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1276991167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSYc3ayDAtHst8JBGvWXH75tpZsWtivQan"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1268400166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SS9xqSLfzdaP8ZqodBVvaTPMrfggzGG9T9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1267592834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQnaNCaXMmupYoSfWUNQi7zc3Ebws7FHn3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1264661333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQW3KaFzda9fzXMwinBmQ7VPGDvtasXLPH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1264119833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SavJRMKR6Zn15egPPEPWM7Mza6xcNtzRVW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1262619834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMvrL5Us4XFxBxbqk9T3jVDcYesQitxaqs"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1262250833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScJaodcYtPhkdUDvgNhj9gcZfY2ifdsr2N"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1261516333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STiofqihMhVnC5xofWryeUZkd5BPNLP59U"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1261482667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STSriwbhScPaKBAzWUa94cq3zGjj3hG4qW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1261159334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SedTqqhhjSR4QFRRMPJNrSocE7jZj2LMjz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1260878167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVZ7NDj99G2j14N9mWvtvhhqwiLpTxHdNT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1260641000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfquqFT5e7Fo3pFe5xhqp965VoCQUeRVPS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1259896833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg9LaSgmG4h7xLGizrogPrNyWXeWRSMjkU"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1259735167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SQdKj38gsN6w6byNDPjcW16AXHhpFxMkcz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1259313333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUXU16JYqJLYMhNGsKY7Gb3cpGTtu7wTq6"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1258557000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjGhH8zXBTvb4FvTFWsF9LKFr7zyctmh93"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1258517167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSZuALHzqDYSHiqJHXW44CGiuhUdDFQ9xS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1257859833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRqBY8gB9iVsfdK54zbd7uHPmxXFEsYNBK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1257107167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdXPn2M885PJssJki6BQCjbuNzWZpadpvZ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1255691167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Scgqnct6ghHnVabMjyv6J6LUCbSijtPDGm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1255214500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfgwbbUFznwBnGf8pS2NsuvBFrkmMWxnUS"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1254986833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNZTUjwXDzu7EQ8NCnDPaPwYDYrrKMGRXv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1254896666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiWQJBATnKTDxRSsLoMagnSyCTpe19T7SG"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1254775833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaHMXCV4o95PMYhxzqEFATpiZoSLGR81Nn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1254730333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNibJgm3WJk1zuufk8GBUHpkaHTRzCkHBM"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1254412833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNmfBxoftxwxVTntZQszLCDdZB2ddBPaWz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1253827500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfDvGsV3GGJvjE2HP2VHhhikVRDda3F3Ti"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1252226833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Scm3EsL9DepqRA2AgXeEb3JbheFTsnw1Zt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1252022333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScCVHWM9ddUuouBum6rZBK6BTf3eTmzjxd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1250675500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbwvTiPRTFKxduWhZSbBCMpcFq5gzfRgy4"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1250143666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SjQxZ2vRhpMhWt7K3wVoF2F5NoXC8osrZJ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1249419000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZL3D8qgAtjaveYdTMLJzbiAUpoHoVqfQy"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1248930500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SdKj5eWKqzLx7WCJhRYbWSUH6sMb5GnXtn"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1248823833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg8qtALqVyoc6LoKjrLoN3QhkhJAU3n2Vt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1248517000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgF1SqUdrX3dSq5XauWCqbmpwidW49Cp5u"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1248417500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SW4bxDEmug5GtA1p6gujbu5oNYYe52LPki"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247929333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SS4PieTP3swUZYsZRMmudGSyGsRubqoHav"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247846000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SScnA1tTQN2K5vBGjrrYfQMk8HoC31ecZ9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247733833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWGtfa4uV4FpwzyLDXZKVjmCbyoNxBcMAF"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247686833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SarwgjTY7LqgK1LzFmdRTfeF2FRFGNEsQu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247670500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sig1TZtk7rmupjstqbSbau2sBooCHLUUB9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1247171166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZtr85Qm9kGbkB8AethPhKmcRp5N5tsrwR"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1245171500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRyzkEzEXnuXPXpkZySkZjx8ngTuizw1Ny"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1244691000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sg6DZ8hEUsmNvwbShczhnRG51SZdL5uxqA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1243871487;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMeYm3eceW5KZKGFV8kYkV5Wxs7kcY7ELY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1243239834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfTtt7RruZXqrPx47GsS1FLhCo9HL8TWmW"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1242337667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShGJdVEf8bcyL8SeYpuDAhuDWvPwuYHVT2"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1242317333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMzCrZV1knimcTUcJJ9LUKQRDgeEoWUYCE"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1242074833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMzW2p86bqSEwiUrkVjpvCH8WokaNEGjpt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1241296333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSdN7AcBh7856M3Bz6W8ucssgRqkAzWEtd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1238822666;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVqqVT989n3opADs948tpW3gyFJYv3Thkm"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1234567890;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc91Uu7T2bzjsmL8pSELxJ4w9CmPpga3oz"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1234263166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVK1Y5r7cJAAg9LNTw3A1NKqEMcRfpr8Nh"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1228911834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRrGMaGsiTNSPaZZ5sHh6BbeDok3AGKvTv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1219965334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNJF1QneGkt5Brj9LRGvvJWZcveCXqX2yY"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1211526166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SY2owUxrCLyDFXq79g78eL2TV5SYTRS56E"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1204337333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMgWaq7bPLWDLFPxuLTEfEnXRhgn2seCQf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1203347334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShLMs266Z4K2WkZhx5BbTdBwpKRPUNUNcf"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1201000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPhkqrjTcMJodGkiPXgTw6ok23yP1GmWA9"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1191952000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STp41wnTrn5mvDzorkAQmtGFqWJQ9hj5YT"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1191459333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SYBQq72djVpcjsWj6arCAM8JPRYAU1y3Lr"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1189926667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SaJTu1JcpLevu9SBBP6ruSsnfU1KWAQdpx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1181601667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STxd3sx6iDhDze8Aj7SqwgbSxiiXoik6t1"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1181582334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sgi7XKV4VZC3aQHSGbdwPxRBrwF2uavf58"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1180933333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRBJC59YxU94QQBebHBkLYAoXe2yk8vpds"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1173620833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Seu23vJPQNaT5K3bgyXpCCJnPSsG6kFPbb"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1171953000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfVmj6mVP1Xotzo7Py786btsPkJjq4znYC"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1171795167;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SWVUyfuL2USFFFJwbymJ8nGxBYUnpeUxB7"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1171539500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ShqY8dFMKe8P914zza7VCeMoAieEmZYGTK"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1171435833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVgFtC2TMYG1FTAAEsGuLj5n9khXhMxc3B"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1166062333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SRNykBMLahmHqFueGhrwejHN7LtvpshitQ"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1165500000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SgytamD9cGYBTa1z4SfEWBs7S7HYXRhKYv"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1165106833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPT19brEPZ23K8KmCRhYPqUdKrHZZYjxNH"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1164304166;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SSzfYyRMEppg7MPvhJ6nvFaxTfwVqQRv1j"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1163083500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SUBEXUSythGjXDeKQB8bH4Z72DMWFv8Xa3"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1162851333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SctftDptGPrmi9f6wqQqgfLDLco6GBfrz8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1160676500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SbmUsHgX1evLoN3NoX6acF237PSMLwat9e"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1144211765;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STjKgL6kDJ6tUedPsFB4Fsd8A6gSgRZYKi"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1136516334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZytDbAmwp9soFm8E1D7wgBgU4G4SUVmci"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1135854500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiF3njYUDTUpbU9XEf43s5TpUqAVkxQj8X"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1134605333;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SPmG5L32uup98teeCmJD25g7WkM3TPDRDc"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1132263667;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("ScLHDGva22y8qLzF7j1vjnzQ99GLLJ6n49"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1083680500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("STDvUc67bAi7xyc3xSnCmWivbJuSQ4S5hA"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1073463500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SMx9voQGoj1qECREsypSETZDAFLE8HjMTu"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1058686833;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SiLa4Y1wjn1qSE3wHow7J6Y92yda2PvTxx"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1033107834;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SW3ey4KBB3jiLSWm6zQfPmFyfTYsNRtuYN"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1026599334;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("Sc8KwkyfNev6JgXQN5vxP8P9f9Kz6rVdec"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1015074992;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SP1JvP3bwi1SFM5KX4kmmWJi5kxQH1S3Mt"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1013572500;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SimnnRydS3GXoc1y9z3XRG2hRN2gkhj2xB"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1001000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SfsaurNR2WcHxo8YGyD7zXmRemnmoh7HzV"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SNJtrLt56n8wFqNBEQDtryryRWhhpzxyf8"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SVTR27SqxE5h5yC4jA22bhvsZ2zV28ZRU5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZ1ocFcUYcvGodUFDNtvkADQQLaKKV9bzd"))) << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        txNew.vout[0].nValue = 1000000000;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex(DecodeBase58ToHex(std::string("SZJnJaspRP1tSVPRr3mmJKeGRQBmmzZJy5"))) << OP_EQUALVERIFY << OP_CHECKSIG;
    }
    genesis.hashPrevBlock = 0;
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
};

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward, const string addr1, const string addr2, const string addr3)
{
    const char* pszTimestamp = "Bitcoin Block #531843: 00000000000000000004b8ac34227fc1932aaa01bf78e744dae90c15089320e1";
    const CScript genesisOutputScript = CScript() << OP_2 << ParseHex(DecodeBase58ToHex(addr1)) << ParseHex(DecodeBase58ToHex(addr2)) << ParseHex(DecodeBase58ToHex(addr3)) << OP_3 << OP_CHECKMULTISIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x0f;
        pchMessageStart[1] = 0x0a;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xe0;
        vAlertPubKey = ParseHex("0x"); // Disabled
        nDefaultPort = 9009;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Helium starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210240;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Helium: 1 day
        nTargetSpacing = 60;  // Helium: 1 minute
        nMaturity = 100;
        //nMaturity = 20; // Reduced maturation period to assist staking trial
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        //nLastPOWBlock = 2880; // 2 days @ 1440 per day (PIVX: 259200, Phore 200)
        nLastPOWBlock = 20160; // 14 days @ 1440 per day (PIVX: 259200, Phore 200)
        //if the lowest block height (vSortedByTimestamp[0]) is >= switch height, use new modifier calc
        // nModifierUpdateBlock = 0; // (PIVX: 615800)
        nZerocoinStartHeight = 999999999; // (PIVX: 863787, Phore 90000)
        nZerocoinStartTime = 4101895950; // December 25, 2099 9:32:30 AM GMT-06:00
        // nBlockEnforceSerialRange = 90003; //Enforce serial range starting this block (Phore 90003)
        nBlockRecalculateAccumulators = 999999; // (PIVX: 895400, Phore 90005) //Trigger a recalculation of accumulators
        // nBlockFirstFraudulent = 90002; // (PIVX: 908000, Phore 90002) //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999; // (PIVX: 891730, Phore 90005) //Last valid accumulator checkpoint
        // nBlockEnforceInvalidUTXO = 0; // (PIVX: 902850) //Start enforcing the invalid UTXO's
        // nInvalidAmountFiltered = 268200*COIN; // (PIVX: 268200) //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999; // (PIVX: 1153160) //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1525158000; // (PIVX: 1525158000) //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1527811200; // (PIVX: 1527811200) //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    82127,                               // nNonce
                    0x1e0ffff0,                          // nBits
                    3,                                   // nVersion
                   treasuryDeposit,                      // genesisReward (treasury deposit)
                   "STSzh125JxXtnsGwDVuP76i5ZS69s5VvUP",  // first NEW treasury address
                   "SNFpemXtZ2hdqUy2jTAXmWJRy7e8jqGiE7",  // second NEW treasury address
                   "SPqjnTbYLmp3TfRzccKBqFUiVJzePK9NRU"  // third NEW treasury address
                    );

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";



            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x00000d0b57455f1d5574e80d377561d4ca1b258a80b4f87b2389695c0bb0de59"));
            assert(genesis.hashMerkleRoot == uint256("0x5fbdbb8161ac36ca7fca837e9a55bce842222dc27dc06a814e119ba67071a52e"));
        }
	// Mainnet --- nonce: 851930 time: 1520801782 hash: 0x00000289d5c33bbc11a166ee53f3e76aa80863ffbc10f22b2484ffc40f7357b2 merklehash: 0x41af082a5c40201a598b994218ceb4aabc59a70999009f6e1bf6f9e063b794b9


        vSeeds.push_back(CDNSSeedData("heliumlabs", "seed.heliumlabs.org"));
        vSeeds.push_back(CDNSSeedData("Spread", "188.166.58.8"));
	vSeeds.push_back(CDNSSeedData("Kserv", "149.28.242.177"));

        // Helium addresses start with 'S'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        // Helium script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        // Helium private keys start with '7' (uncompressed) or 'V' (compressed)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,191);
        // Helium BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Helium BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Helium BIP44 coin type (pending BIP44-capable wallet, use Bitcoin type)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0xe2).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0499A7AF4806FC6DE640D23BC5936C29B77ADF2174B4F45492727F897AE63CF8D27B2F05040606E0D14B547916379FA10716E344E745F880EDC037307186AA25B7";
        strSporkKeyOld = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        strObfuscationPoolDummyAddress = "S87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1527634800; // 2018-05-30 00:00:00

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zpiv to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0x0c;
        pchMessageStart[3] = 0x0e;
        vAlertPubKey = ParseHex("");
        bnProofOfWorkLimit = ~uint256(0) >> 1; // 0x207fffff, Helium testnet starting difficulty
        nSubsidyHalvingInterval = 210240;
        nDefaultPort = 19009;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Helium: 1 day
        nTargetSpacing = 60;  // Helium: 1 minute
        nLastPOWBlock = 10000;
        nMaturity = 15;
        nMasternodeCountDrift = 2;
        // nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 21000000 * COIN;
        nZerocoinStartHeight = 999999999;
        nZerocoinStartTime = 1530801782;
        // nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        // nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint
        // nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's
        // nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    1426964,                               // nNonce
                    0x1e0ffff0,                          // nBits
                    3,                                   // nVersion
                    treasuryDeposit,                     // genesisReward (treasury deposit)
                   "msYBKKuARmcmMHmzMGxc8j8XYi8bqEeBJr", // first treasury address
                   "mfYcNVRnTNHDw6BwKPhk3Z8xXp4F8CEMtZ", // second treasury address
                   "mkGv2mrvZvKriZ1tzwQheHQzYyW5o9ir5J"  // third treasury address
                    );

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x00000f4e3a8c8c8bbf2dad765ec396a3d5c13b6bdf1a0151c71e6e1811f06bc3"));
            assert(genesis.hashMerkleRoot == uint256("0x3cea4614b210109440b3c05afd2b3e20670b8f94cf40657316c4dbb9a126ab3e"));
        }
	// Testnet --- nonce: 1497998 time: 1520801782 hash: 0x00000ad9f74009abda4c38fe49f4cf1c37cc8c956a931e669313cef5739157f3 merklehash: 0x53c6673d08fd145d707ccd623c5c254f1e4a283b1321662ca991dd9231d9b526

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("Minkiz", "minkiz.co"));
        vSeeds.push_back(CDNSSeedData("heliumna01", "heliumna01.heliumchain.org"));
        vSeeds.push_back(CDNSSeedData("heliumeu01", "heliumeu01.heliumchain.org"));
        vSeeds.push_back(CDNSSeedData("heliumap01", "heliumap01.heliumchain.org"));

        // Testnet Helium addresses start with 'm' or 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        // Testnet Helium script addresses start with '2'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        // Testnet private keys start with '9' (uncompressed) or 'c' (compressed)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet Helium BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Helium BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Helium BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        fSkipProofOfWorkCheck = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "";
        strSporkKeyOld = "";
        strObfuscationPoolDummyAddress = "m57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1527634800; //30th May 2018 00:00:00
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0x0a;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0x0e;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Helium: 1 day
        nTargetSpacing = 60;  // Helium: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 19004;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    5,                                   // nNonce
                    0x207fffff,                          // nBits
                    3,                                   // nVersion
                    treasuryDeposit,                     // genesisReward (treasury deposit)
                   "STSzh125JxXtnsGwDVuP76i5ZS69s5VvUP",  // first NEW treasury address
                   "SNFpemXtZ2hdqUy2jTAXmWJRy7e8jqGiE7",  // second NEW treasury address
                   "SPqjnTbYLmp3TfRzccKBqFUiVJzePK9NRU"  // third NEW treasury address
                    );

        hashGenesisBlock = genesis.GetHash();

        if (regenerate) {
            hashGenesisBlock = uint256S("");
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x3466bad752fbab0a6f04c084e0593b4d138de9a03bff704e2c9ce65b1edba961"));
            assert(genesis.hashMerkleRoot == uint256("0x5fbdbb8161ac36ca7fca837e9a55bce842222dc27dc06a814e119ba67071a52e"));
        }
	// Regtestnet --- nonce: 5 time: 1520801782 hash: 0x545594cf835ead5266cd10f0d6f5f8497f69910cd781940d53590bd36bc20d14 merklehash: 0x41af082a5c40201a598b994218ceb4aabc59a70999009f6e1bf6f9e063b794b9


        if (regenerate)
            exit(0);

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        // fSkipProofOfWorkCheck = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 19029;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
