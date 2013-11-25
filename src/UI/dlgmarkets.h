#ifndef DLGMARKETS_H
#define DLGMARKETS_H

#include <QPointer>
#include <QVariant>
#include <QDialog>
#include <QMap>
#include <QMultiMap>

#include "Handlers/contacthandler.h"

namespace Ui {
class DlgMarkets;
}

namespace OTDB {
class MarketList;
}

class MTDetailEdit;

class Moneychanger;

class DlgMarkets : public QDialog
{
    Q_OBJECT

public:
    explicit DlgMarkets(QWidget *parent);
    ~DlgMarkets();

    void FirstRun();

    void dialog();

    void RefreshRecords(); // For servers and nyms.
    void RefreshMarkets(); // For markets and offers.

    QString GetNymID() { return m_nymId; }

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    void SetCurrentNymIDBasedOnIndex   (int index);
    void SetCurrentServerIDBasedOnIndex(int index);
    // -----------------------------------------------
    bool RetrieveMarketList(mapIDName & the_map);
    bool LowLevelRetrieveMarketList(QString qstrServerID, QString qstrNymID, mapIDName & the_map);
    // -----------------------------------------------
    bool LoadMarketList(mapIDName & the_map);
    bool LowLevelLoadMarketList(QString qstrServerID, QString qstrNymID, mapIDName & the_map);
    // -----------------------------------------------
    OTDB::MarketList * LoadMarketListForServer(const std::string & serverID);

private slots:
    void on_pushButtonRefresh_clicked();

    void on_comboBoxServer_currentIndexChanged(int index);

    void on_comboBoxNym_currentIndexChanged(int index);

private:
    void ClearMarketMap();

    QMultiMap<QString, QVariant> m_mapMarkets; // market/scale, marketdata

    mapIDName m_mapServers;
    mapIDName m_mapNyms;

    QString m_serverId;
    QString m_nymId;

    bool m_bFirstRun;
    bool m_bHaveRetrievedFirstTime;

    QPointer<MTDetailEdit> m_pMarketDetails;
    QPointer<MTDetailEdit> m_pOfferDetails;

    Ui::DlgMarkets *ui;
};

#endif // DLGMARKETS_H