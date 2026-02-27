#pragma once

#include "panels/GoBackPanel.hpp"
#include "managers/ItemsManager.hpp"
#include "panels/ItemsPanel.hpp"
#include "ZasLib/Equipment.hpp"

#include <QWidget>
#include <QPushButton>
#include <QVector>

class ItemsShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsShopPage(QWidget *parent = nullptr);

signals:
    void GoBackClicked();

private:
    GoBackPanel* m_goBackPanel;
    ItemsPanel* m_inventoryPanel = nullptr;
    QWidget* createGoBackPanel();
    ItemsPanel* createShopPanel();
    ItemsPanel* createInventoryPanel();
    QFrame* createWrapper();
    void applyStyling();
    QMap<QString, int> itemsInInventory;
    QVector<QString> inventoryDisplayList() const;
    QString baseItemName(const QString& displayName) const; 

};
