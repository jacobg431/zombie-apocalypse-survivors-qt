#include "pages/ItemsShopPage.hpp"
#include "panels/ItemsPanel.hpp"
#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

ItemsShopPage::ItemsShopPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);

    auto *panelsWrapperFrame = new QFrame;
    panelsWrapperFrame->setObjectName("panelsWrapper");
    auto *panelsWrapperLayout = new QHBoxLayout(panelsWrapperFrame);
    panelsWrapperLayout->setSpacing(30);
    panelsWrapperLayout->setContentsMargins(20, 20, 20, 20);

    panelsWrapperLayout->addWidget(createShopPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());

    mainLayout->addWidget(createGoBackPanel());
    mainLayout->addWidget(panelsWrapperFrame);

    applyStyling();
}

QWidget* ItemsShopPage::createGoBackPanel()
{
    auto *container = new GoBackPanel();
    container->setContentsMargins(15, 15, 15, 15);
    return container;
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