// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2020 The Helium developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZSQRCONTROLDIALOG_H
#define ZSQRCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zsqr/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZSqrControlDialog;
}

class CZSqrControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZSqrControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZSqrControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZSqrControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZSqrControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZSqrControlDialog(QWidget *parent);
    ~ZSqrControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZSqrControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZSqrControlWidgetItem;

private Q_SLOTS:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZSQRCONTROLDIALOG_H
