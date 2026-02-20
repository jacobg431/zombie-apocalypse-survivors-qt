#include "pages/ItemsShopPage.hpp"
#include "panels/ItemsPanel.hpp"
#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

ItemsShopPage::ItemsShopPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(createGoBackPanel());
    mainLayout->addWidget(createWrapper());

    applyStyling();
}

QWidget* ItemsShopPage::createGoBackPanel()
{
    m_goBackPanel = new GoBackPanel(this);
    m_goBackPanel->setContentsMargins(15, 15, 15, 15);

    connect(m_goBackPanel, &GoBackPanel::GoBackClicked,
            this, &ItemsShopPage::GoBackClicked);

    return m_goBackPanel;
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

QFrame* ItemsShopPage::createWrapper()
{
    auto *panelsWrapperFrame = new QFrame;
    panelsWrapperFrame->setObjectName("panelsWrapper");
    auto *panelsWrapperLayout = new QHBoxLayout(panelsWrapperFrame);
    panelsWrapperLayout->setSpacing(30);
    panelsWrapperLayout->setContentsMargins(20, 20, 20, 20);

    panelsWrapperLayout->addWidget(createShopPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());

    return panelsWrapperFrame;
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