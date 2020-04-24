// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2020 The Helium developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZSQRCONTROLDIALOG_H
#define ZSQRCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zhlm/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZHlmControlDialog;
}

class CZHlmControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZHlmControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZHlmControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZHlmControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZHlmControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZHlmControlDialog(QWidget *parent);
    ~ZHlmControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZHlmControlDialog *ui;
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
    friend class CZHlmControlWidgetItem;

private Q_SLOTS:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZSQRCONTROLDIALOG_H
