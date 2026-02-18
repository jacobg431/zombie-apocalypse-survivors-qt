#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>

class ItemsShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsShopPage(QWidget *parent = nullptr);

private:
    QWidget* createShopPanel();
    QWidget* createInventoryPanel();
    void applyStyling();

    QPushButton* m_buyButton = nullptr;
    QPushButton* m_sellButton = nullptr;

    QVector<QPushButton*> m_shopItemButtons;
    QVector<QPushButton*> m_inventoryItemButtons;
};
