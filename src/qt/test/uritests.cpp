// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2020 The Helium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("helium://Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("helium:Sapor5rpxvaGQ4cW8dptj3zW94MxuAwW4P?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
