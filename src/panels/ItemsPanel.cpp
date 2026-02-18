#include "panels/ItemsPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include "widgets/ItemPushButton.hpp"

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>

ItemsPanel::ItemsPanel(const QString& title, const QString& buttonText, QWidget *parent) 
{
    auto *layout = new QVBoxLayout(this);

    auto *labelTitle = new QLabel(title);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setObjectName("panelTitle");

    layout->addWidget(labelTitle);

    // 4x4 Grid
    auto *grid = new QGridLayout;
    grid->setSpacing(8);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            auto *button = new ItemPushButton("Empty");

            m_itemButtons.append(button);
            grid->addWidget(button, row, col);

            connect(button, &ItemPushButton::clicked, this, [this, button]() {
                for (auto *b : m_itemButtons)
                    if (b != button)
                        b->setChecked(false);

                m_button->setEnabled(button->isChecked());
            });
        }
    }

    layout->addLayout(grid);

    // Buy Button
    m_button = new DefaultPushButton(buttonText);
    m_button->setEnabled(false);

    layout->addSpacing(10);
    layout->addWidget(m_button);

    applyStyling();
}

void ItemsPanel::applyStyling() {
    setStyleSheet(R"(

        QFrame {
            background-color: #2b2b2b;
            border-radius: 10px;
            padding: 15px;
        }

        QLabel#panelTitle {
            font-size: 32px;
            font-weight: bold;
            margin-bottom: 10px;
        }

    )");
}