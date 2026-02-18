#include "pages/ItemsShopPage.hpp"
#include "panels/ItemsPanel.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>

ItemsShopPage::ItemsShopPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    mainLayout->addWidget(createShopPanel());
    mainLayout->addWidget(createInventoryPanel());

    applyStyling();
}

QWidget* ItemsShopPage::createShopPanel()
{
    auto *container = new ItemsPanel("Items Shop", "Buy");
    return container;
}

QWidget* ItemsShopPage::createInventoryPanel()
{
    auto *container = new ItemsPanel("Inventory", "Sell");
    return container;
}


void ItemsShopPage::applyStyling()
{
    setStyleSheet(R"(

        QWidget {
            background-color: #1e1e1e;
            color: #dddddd;
            font-family: Consolas, monospace;
            font-size: 14px;
        }

    )");
}