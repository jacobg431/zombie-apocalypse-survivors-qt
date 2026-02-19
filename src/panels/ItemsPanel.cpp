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

    auto *innerWrapper = createInnerWrapper(title, buttonText);
    layout->addWidget(innerWrapper);
    layout->setAlignment(m_button, Qt::AlignCenter);

    applyStyling();
}

QLabel* ItemsPanel::createTitleLabel(const QString& title)
{
    auto *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("panelTitle");
    return label;
}

QFrame* ItemsPanel::createGrid()
{
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

    return gridWrapperFrame;
}

QFrame* ItemsPanel::createBottomWrapper(const QString& buttonText)
{
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

    return bottomWrapperFrame;
}

QFrame* ItemsPanel::createInnerWrapper(const QString& title, const QString& buttonText)
{
    auto *innerWrapperFrame = new QFrame;
    innerWrapperFrame->setObjectName("innerWrapper");

    auto *innerLayout = new QVBoxLayout(innerWrapperFrame);

    innerLayout->addWidget(createTitleLabel(title), 0);
    innerLayout->addWidget(createGrid(), 1);
    innerLayout->addSpacing(10);
    innerLayout->addWidget(createBottomWrapper(buttonText), 0);

    return innerWrapperFrame;
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