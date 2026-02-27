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

ItemsPanel* ItemsShopPage::createShopPanel()
{
    auto& itemsManager = ItemsManager::instance();
    QVector<QString> items = itemsManager.availableItems();

    auto *container = new ItemsPanel("Shop", "Buy", items, this);

    connect(container, &ItemsPanel::actionClicked, this,
            [this](const QString& name){

        itemsInInventory[name] += 1;

        if (m_inventoryPanel)
            m_inventoryPanel->setItems(inventoryDisplayList());
    });

    return container;
}

ItemsPanel* ItemsShopPage::createInventoryPanel()
{
    auto *container = new ItemsPanel("Inventory", "Sell",
                                     inventoryDisplayList(), this);

    connect(container, &ItemsPanel::actionClicked, this,
            [this](const QString& displayName){

        QString base = baseItemName(displayName);

        if (itemsInInventory.contains(base) && itemsInInventory[base] > 0)
        {
            itemsInInventory[base] -= 1;
            if (itemsInInventory[base] == 0)
                itemsInInventory.remove(base);
        }

        if (m_inventoryPanel)
            m_inventoryPanel->setItems(inventoryDisplayList());
    });

    return container;
}

QString ItemsShopPage::baseItemName(const QString& displayName) const
{
    int idx = displayName.indexOf(" x");
    if (idx != -1)
        return displayName.left(idx);
    return displayName;
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
    m_inventoryPanel = createInventoryPanel();
    panelsWrapperLayout->addWidget(m_inventoryPanel);
    panelsWrapperLayout->addStretch();

    return panelsWrapperFrame;
}

void ItemsShopPage::applyStyling()
{
    setStyleSheet(R"(

    )");
}


QVector<QString> ItemsShopPage::inventoryDisplayList() const
{
    QVector<QString> list;

    for (auto it = itemsInInventory.begin(); it != itemsInInventory.end(); ++it)
    {
        if (it.value() > 1)
            list.append(it.key() + " x" + QString::number(it.value()));
        else
            list.append(it.key());
    }

    return list;
}
