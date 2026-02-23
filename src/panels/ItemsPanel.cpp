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
    grid->setSpacing(16);
    grid->setContentsMargins(0, 0, 0, 0); 

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

                const bool isSelected = button->isChecked();
                m_button->setEnabled(button->isChecked());

                if (isSelected) 
                {
                    m_selectedItemLabel->setText(button->text());
                }
                else
                {
                    m_selectedItemLabel->setText("No item selected");
                } 
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
    bottomWrapperLayout->setContentsMargins(0, 0, 0, 0);
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
    innerLayout->addSpacing(32);
    innerLayout->addWidget(createBottomWrapper(buttonText), 0);

    return innerWrapperFrame;
}

void ItemsPanel::applyStyling() 
{
    setStyleSheet(R"(

        QFrame {
            background-color: transparent;
            border-radius: 10px;
            padding: 0px;
        }

        QFrame#innerWrapper {
            border-radius: 10px;
            padding: 15px;

            border-image: url(:resources/images/parchment.png) 0 0 0 0 stretch stretch;
        }

        QFrame#gridWrapper {
            padding: 32px;
        }

        QFrame#bottomWrapper {
            padding: 0px;
        }

        QLabel#panelTitle {
            font-size: 32px;
            margin-bottom: 10px;
            max-height: 64px;
            color: #FF5733;
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch;
            margin-left: 64px;
            margin-right: 64px;
        }

        QLabel#selectedItemText {
            font-size: 16px;
            color: #FF5733;
            padding: 0px;
            margin: 12px;
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch;
        }
    )");
}