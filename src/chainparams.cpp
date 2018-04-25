// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
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
    (0, uint256("0x00000b1bc7563cc8c6772e335f9ebc905047faee14d98905b989a644f2bc0625"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1510948627, // * UNIX timestamp of last checkpoint block
    1842739,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000007ab0c41b98c07c05a914c2737cb924ea320ff964b6a68975df9d12263b9"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1520851782,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x1aea68bb3a50c9a0045d8fa24877ca06a3b50b5586915bc9009fbc1da1db83f4"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1520851782,
    0,
    100};
libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
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
    genesis.hashPrevBlock = 0;
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
};

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward, const string addr1, const string addr2, const string addr3)
{
    const char* pszTimestamp = "Bitcoin Block #513069: 00000000000000000049f7a375c89a21aa05aa566546749f4a32607578b02bf9";
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
        nTargetTimespan = 1 * 60; // Helium: 1 day
        nTargetSpacing = 1 * 60;  // Helium: 1 minute
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 100000;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 9999999;
        nZerocoinStartTime = 1530801782; // Later
        nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 0; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's
        nReward = 432870.87949961 * COIN;

        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    138356,                              // nNonce
                    0x1e0ffff0,                          // nBits
                    3,                                   // nVersion
                   treasuryDeposit,                      // genesisReward (treasury deposit)
                   "Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P", // first treasury address
                   "SeYn7AmvjB3Wr3QqdJK6UsW85dPKeEKmSg", // second treasury address
                   "Sbe6m4y6wGhUo6FoS6Sab2PxnScXm8HQTf"  // third treasury address
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
                // Mainnet --- nonce: 138356 time: 1520801782 hash: 0x00000b1bc7563cc8c6772e335f9ebc905047faee14d98905b989a644f2bc0625 merklehash: 0x2b55c858456639d19304fc159f56a75e1af56269e359aa6061bbd2912005209f
            }
        } else {
            std::cout << "Mainnet ---\n";
            std::cout << " nonce: " << genesis.nNonce <<  "\n";
            std::cout << " time: " << genesis.nTime << "\n";
            std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str() << "\n";
            std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
            assert(hashGenesisBlock == uint256("0x00000b1bc7563cc8c6772e335f9ebc905047faee14d98905b989a644f2bc0625"));
            assert(genesis.hashMerkleRoot == uint256("0x2b55c858456639d19304fc159f56a75e1af56269e359aa6061bbd2912005209f"));
        }


        vSeeds.push_back(CDNSSeedData("Minkiz", "minkiz.co"));           // Single node address

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
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x00).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
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
        nTargetTimespan = 1 * 60; // Helium: 1 day
        nTargetSpacing = 1 * 60;  // Helium: 1 minute
        nLastPOWBlock = 100000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 210000 * COIN;
        nZerocoinStartHeight = 9999999;
        nZerocoinStartTime = 1530801782;
        nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's
        nReward = 10000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    1694927,                             // nNonce
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
                // Testnet --- nonce: 1694927 time: 1520801782 hash: 0x000007ab0c41b98c07c05a914c2737cb924ea320ff964b6a68975df9d12263b9 merklehash: 0xa911e17f757700907d75e02837c7f079160a63652a5e54161728f54a14a63b9a
            }
        } else {
            std::cout << "Testnet ---\n";
            std::cout << " nonce: " << genesis.nNonce <<  "\n";
            std::cout << " time: " << genesis.nTime << "\n";
            std::cout << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
            std::cout << " merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
            assert(hashGenesisBlock == uint256("0xff76401c9ab020c724d1cac4aeb2c847e8912a2907d0b53423b14f2efda9966c"));
            assert(genesis.hashMerkleRoot == uint256("0xe2581d080f3f4dbbe6834c64ca8a7fd133b09e02e3ef87a35909fac0eaa8b075"));
        }

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("Minkiz", "minkiz.co"));

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
        nTargetTimespan = 1 * 60; // Helium: 1 day
        nTargetSpacing = 1 * 60;  // Helium: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 19004;
        nReward = 432870.87949961 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis = CreateGenesisBlock(
                    1520801782,                          // nTime
                    3,                                   // nNonce
                    0x207fffff,                          // nBits
                    3,                                   // nVersion
                    treasuryDeposit,                     // genesisReward (treasury deposit)
                   "Spor5rpxvaGQ4cW8dptj3zW94MxuAwW4P", // first treasury address
                   "SeYn7AmvjB3Wr3QqdJK6UsW85dPKeEKmSg", // second treasury address
                   "Sbe6m4y6wGhUo6FoS6Sab2PxnScXm8HQTf"  // third treasury address
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
                // Regtestnet --- nonce: 3 time: 1520801782 hash: 0x1877e38bd4192e57d00e80a4c1aeaf0d661b079203b604e222c1ebeb9555a811 merklehash: 0x73e495a7b3b074263077479a2915dca021c188f33ec2ec05a590350b459ffa27
            }
        } else {
            std::cout << "Regtestnet ---\n";
            std::cout << " nonce: " << genesis.nNonce <<  "\n";
            std::cout << " time: " << genesis.nTime << "\n";
            std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str() << "\n";
            std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
            assert(hashGenesisBlock == uint256("0x1877e38bd4192e57d00e80a4c1aeaf0d661b079203b604e222c1ebeb9555a811"));
            assert(genesis.hashMerkleRoot == uint256("0x73e495a7b3b074263077479a2915dca021c188f33ec2ec05a590350b459ffa27"));
        }

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
        nDefaultPort = 51478;
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
