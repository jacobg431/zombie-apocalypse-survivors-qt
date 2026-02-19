#include "panels/ItemsPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include "widgets/ItemPushButton.hpp"

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

ItemsPanel::ItemsPanel(const QString& title, const QString& buttonText, QWidget *parent) 
{
    auto *layout = new QVBoxLayout(this);

    auto *labelTitle = new QLabel(title);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setObjectName("panelTitle");

    // 4x4 Grid
    auto *gridWrapperFrame = new QFrame;
    gridWrapperFrame->setObjectName("gridWrapper");
    auto *grid = new QGridLayout(gridWrapperFrame);
    grid->setSpacing(8);
    grid->setContentsMargins(0,0,0,0); 

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

    grid->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum), 4, 0);

    m_selectedItemLabel = new QLabel("No item selected");
    m_selectedItemLabel->setObjectName("selectedItemText");
    m_selectedItemLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    m_button = new DefaultPushButton(buttonText);
    m_button->setEnabled(false);

    auto *bottomWrapperFrame = new QFrame;
    bottomWrapperFrame->setObjectName("bottomWrapper");
    auto *bottomWrapperLayout = new QHBoxLayout(bottomWrapperFrame);
    bottomWrapperLayout->setContentsMargins(0,0,0,0);    

    bottomWrapperLayout->addWidget(m_selectedItemLabel);
    bottomWrapperLayout->addStretch();
    bottomWrapperLayout->addWidget(m_button);

    auto *innerWrapperFrame = new QFrame;
    innerWrapperFrame->setObjectName("innerWrapper");
    auto *innerWrapperLayout = new QVBoxLayout(innerWrapperFrame);

    innerWrapperLayout->addWidget(labelTitle, 0);
    innerWrapperLayout->addWidget(gridWrapperFrame, 1);
    innerWrapperLayout->addSpacing(10);
    innerWrapperLayout->addWidget(bottomWrapperFrame, 0);

    layout->addWidget(innerWrapperFrame);
    layout->setAlignment(m_button, Qt::AlignCenter);

    applyStyling();
}

void ItemsPanel::applyStyling() {
    setStyleSheet(R"(

        QFrame {
            background-color: #2b2b2b;
            border-radius: 10px;
            padding: 15px;
        }

        QFrame#innerWrapper {
            border-radius: 10px;
            padding: 15px;
        }

        QFrame#gridWrapper {
            padding: 0px;
        }

        QFrame#bottomWrapper {
            padding: 0px;
        }

        QLabel#panelTitle {
            font-size: 32px;
            font-weight: bold;
            margin-bottom: 10px;
            max-height: 64px;
        }

        QLabel#selectedItemText {
            font-size: 16px;
            color: #ddd;
            padding: 0px;
        }

    )");
}