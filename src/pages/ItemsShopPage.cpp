#include "pages/ItemsShopPage.hpp"
#include "widgets/DefaultPushButton.hpp"
#include "widgets/ItemPushButton.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

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
    auto *container = new QFrame;
    auto *layout = new QVBoxLayout(container);

    auto *title = new QLabel("Items Shop");
    title->setAlignment(Qt::AlignCenter);
    title->setObjectName("panelTitle");

    layout->addWidget(title);

    // 4x4 Grid
    auto *grid = new QGridLayout;
    grid->setSpacing(8);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            auto *button = new ItemPushButton("Empty");
            button->setCheckable(true);
            button->setMinimumSize(80, 60);

            m_shopItemButtons.append(button);
            grid->addWidget(button, row, col);

            connect(button, &ItemPushButton::clicked, this, [this, button]() {
                for (auto *b : m_shopItemButtons)
                    if (b != button)
                        b->setChecked(false);

                m_buyButton->setEnabled(button->isChecked());
            });
        }
    }

    layout->addLayout(grid);

    // Buy Button
    m_buyButton = new DefaultPushButton("Buy");
    m_buyButton->setEnabled(false);
    m_buyButton->setMinimumHeight(40);

    layout->addSpacing(10);
    layout->addWidget(m_buyButton);

    return container;
}

QWidget* ItemsShopPage::createInventoryPanel()
{
    auto *container = new QFrame;
    auto *layout = new QVBoxLayout(container);

    auto *title = new QLabel("Inventory");
    title->setAlignment(Qt::AlignCenter);
    title->setObjectName("panelTitle");

    layout->addWidget(title);

    // 4x4 Grid
    auto *grid = new QGridLayout;
    grid->setSpacing(8);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            auto *button = new ItemPushButton("Empty");
            button->setCheckable(true);
            button->setMinimumSize(80, 60);

            m_inventoryItemButtons.append(button);
            grid->addWidget(button, row, col);

            connect(button, &ItemPushButton::clicked, this, [this, button]() {
                for (auto *b : m_inventoryItemButtons)
                    if (b != button)
                        b->setChecked(false);

                m_sellButton->setEnabled(button->isChecked());
            });
        }
    }

    layout->addLayout(grid);

    // Sell Button
    m_sellButton = new DefaultPushButton("Sell");
    m_sellButton->setEnabled(false);
    m_sellButton->setMinimumHeight(40);

    layout->addSpacing(10);
    layout->addWidget(m_sellButton);

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

        QFrame {
            background-color: #2b2b2b;
            border-radius: 10px;
            padding: 15px;
        }

        QLabel#panelTitle {
            font-size: 18px;
            font-weight: bold;
            margin-bottom: 10px;
        }

    )");
}