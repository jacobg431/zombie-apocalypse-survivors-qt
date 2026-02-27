#pragma once

#include "panels/GoBackPanel.hpp"
#include "managers/ItemsManager.hpp"
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
    void goBackClicked();

private:
    GoBackPanel* m_goBackPanel;

    QWidget* createGoBackPanel();
    QWidget* createShopPanel();
    QWidget* createInventoryPanel();
    QFrame* createWrapper();
    void applyStyling();
};
