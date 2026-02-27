#include "pages/ItemsShopPage.hpp"
#include "panels/ItemsPanel.hpp"
#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

ItemsShopPage::ItemsShopPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(createGoBackPanel(), 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(createWrapper(), 1);

    applyStyling();
}

QWidget* ItemsShopPage::createGoBackPanel()
{
    m_goBackPanel = new GoBackPanel(this);
    m_goBackPanel->setContentsMargins(0, 0, 0, 0);

    connect(m_goBackPanel, &GoBackPanel::GoBackClicked,
            this, &ItemsShopPage::GoBackClicked);

    return m_goBackPanel;
}

QWidget* ItemsShopPage::createShopPanel()
{
    auto *container = new ItemsPanel("Shop", "Buy");
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
    panelsWrapperLayout->addStretch();
    panelsWrapperLayout->addWidget(createShopPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());
    panelsWrapperLayout->addStretch();

    return panelsWrapperFrame;
}

void ItemsShopPage::applyStyling()
{
    setStyleSheet(R"(

    )");
}