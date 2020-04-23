// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Helium developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/transaction.h"
#include "main.h"
#include "test_helium.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(main_tests, TestingSetup)

CAmount nMoneySupplyPoWEnd = 8891432 * COIN;
CAmount nMoneySupplyPoSEnd = 21679663 * COIN;

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    CAmount nSum = 0;
//    for (int nHeight = 0; nHeight < 1; nHeight += 1) {
        /* premine in block 1 (60,001 HLM) */
//        CAmount nSubsidy = GetBlockValue(nHeight);
//        BOOST_CHECK(nSubsidy <= 60001 * COIN);
//        nSum += nSubsidy;
//    }

    /* Test public ledger emission */
    CAmount nSubsidy = GetBlockValue(1);
    BOOST_CHECK(nSubsidy <= 8891033 * COIN);

    for (int nHeight = 2; nHeight < 401; nHeight += 1) {
        /* PoW Phase */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 1 * COIN);
        BOOST_CHECK(MoneyRange(nSubsidy));
        nSum += nSubsidy;
        BOOST_CHECK(nSum > 0 && nSum <= nMoneySupplyPoWEnd);
     }

    for (int nHeight = 401; nHeight < 20561; nHeight += 1) {
        /* PoS Phase One */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 0.2 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 20561; nHeight < 526001; nHeight += 1) {
        /* PoS Phase Two */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 5 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 526001; nHeight < 1052001; nHeight += 1) {
        /* PoS Phase Three */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 4.5 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 1052001; nHeight < 1578001; nHeight += 1) {
        /* PoS Phase Four */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 4 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 1578001; nHeight < 2104001; nHeight += 1) {
        /* PoS Phase Five */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 3.5 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 2104001; nHeight < 2630001; nHeight += 1) {
        /* PoS Phase Six */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 3 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 2630001; nHeight < 3156001; nHeight += 1) {
        /* PoS Phase Seven */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 2.5 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 3156001; nHeight < 3682001; nHeight += 1) {
        /* PoS Phase Eight */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 2 * COIN);
        BOOST_CHECK(MoneyRange(nSubsidy));
        nSum += nSubsidy;
        BOOST_CHECK(nSum > 0 && nSum <= nMoneySupplyPoSEnd);
    }
    //BOOST_CHECK(nSum == 4109975100000000ULL);
}

BOOST_AUTO_TEST_SUITE_END()
