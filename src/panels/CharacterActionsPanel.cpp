#include <QWidget>
#include <QFrame>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "panels/CharacterActionsPanel.hpp"
#include "widgets/DefaultPushButton.hpp"

CharacterActionsPanel::CharacterActionsPanel(QWidget *parent) 
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());
    applyStyling();
}

QWidget* CharacterActionsPanel::createTitleLabel()
{
    auto *label = new QLabel("Actions");
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("panelTitle");
    return label;
}

QFrame* CharacterActionsPanel::createButtonWrapper()
{
    _itemsShopButton = new DefaultPushButton("Item Shop");
    _fightButton = new DefaultPushButton("Fight!");
    _mainMenuButton = new DefaultPushButton("Main Menu");

    connect(_itemsShopButton, &QPushButton::clicked, 
        this, &CharacterActionsPanel::itemsShopClicked);
    connect(_fightButton, &QPushButton::clicked, 
        this, &CharacterActionsPanel::fightClicked);
    connect(_mainMenuButton, &QPushButton::clicked, 
        this, &CharacterActionsPanel::mainMenuClicked);

    auto *buttonWrapperFrame = new QFrame;
    buttonWrapperFrame->setObjectName("buttonWrapper");

    auto buttonWrapperLayout = new QVBoxLayout(buttonWrapperFrame);
    buttonWrapperLayout->setAlignment(Qt::AlignCenter);
    buttonWrapperLayout->addWidget(_itemsShopButton);
    buttonWrapperLayout->addSpacing(10);
    buttonWrapperLayout->addWidget(_fightButton);
    buttonWrapperLayout->addSpacing(10);
    buttonWrapperLayout->addWidget(_mainMenuButton);

    buttonWrapperLayout->setAlignment(_itemsShopButton, Qt::AlignCenter);
    buttonWrapperLayout->setAlignment(_fightButton, Qt::AlignCenter);
    buttonWrapperLayout->setAlignment(_mainMenuButton, Qt::AlignCenter);

    return buttonWrapperFrame;
}

QFrame* CharacterActionsPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("wrapper");
    auto *wrapperLayout = new QVBoxLayout(wrapperFrame);

    wrapperLayout->addWidget(createTitleLabel());
    wrapperLayout->addWidget(createButtonWrapper());

    return wrapperFrame;
}

void CharacterActionsPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame {
            background-color: #2E2E2E;
            border-radius: 10px;
            padding: 15px;
        }

        QFrame#wrapper {
            border-radius: 10px;
            padding: 15px;
        }

        QLabel#panelTitle {
            font-size: 32px;
            font-weight: bold;
            margin-bottom: 10px;
            max-height: 64px;
        }

    )");
}