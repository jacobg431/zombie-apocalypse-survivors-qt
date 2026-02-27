#include "pages/MainMenuPage.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFrame>

MainMenuPage::MainMenuPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());
    applyStyling();
    wireConnections();
}

QFrame* MainMenuPage::createWrapper()
{
    auto* wrapperFrame = new QFrame;
    auto* wrapperLayout = new QVBoxLayout(wrapperFrame);

    setWidgets();

    wrapperLayout->addStretch();
    wrapperLayout->addWidget(_title);
    wrapperLayout->addStretch();
    wrapperLayout->addWidget(_newGameButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(_loadSaveButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(_quitToDesktopButton, 0, Qt::AlignCenter);
    wrapperLayout->addStretch();

    return wrapperFrame;
}

void MainMenuPage::setWidgets()
{
    _title = new QLabel("Zombie Apocalypse Survivors");
    _title->setObjectName("title");
    _title->setAlignment(Qt::AlignCenter);

    _newGameButton = new QPushButton("New Game");
    _newGameButton->setObjectName("mainMenuButton");
    _newGameButton->setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    
    _loadSaveButton = new QPushButton("Load Save");
    _loadSaveButton->setObjectName("mainMenuButton");
    _loadSaveButton->setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    _quitToDesktopButton = new QPushButton("Quit Game");
    _quitToDesktopButton->setObjectName("mainMenuButton");
    _quitToDesktopButton->setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
}

void MainMenuPage::wireConnections()
{
    QObject::connect(_newGameButton, &QPushButton::clicked, 
        this, &MainMenuPage::newGameClicked);
    QObject::connect(_loadSaveButton, &QPushButton::clicked, 
        this, &MainMenuPage::loadSaveClicked);
    QObject::connect(_quitToDesktopButton, &QPushButton::clicked, 
        this, &MainMenuPage::quitToDesktopClicked);
}

void MainMenuPage::applyStyling()
{
    setStyleSheet(R"(

        QLabel#title {
            font-size: 56px; 
            font-weight: bold; 
            color: #FF5733;
        }

        QPushButton#mainMenuButton {
            font-size: 40px;
        }

    )");
}