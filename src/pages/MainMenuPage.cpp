#include "pages/MainMenuPage.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

MainMenuPage::MainMenuPage(QWidget *parent) : QWidget(parent)
{
    int BUTTON_WIDTH = 400;
    int BUTTON_HEIGHT = 100;

    QString TITLE_STYLE = "font-size: 56px; font-weight: bold; color: #FF5733;";
    QString BUTTON_STYLE = "font-size: 40px;";

    // --- Title Card ---
    auto *game_title = new QLabel("Zombie Apocalypse Survivors");

    game_title->setAlignment(Qt::AlignCenter);
    game_title->setStyleSheet(TITLE_STYLE);

    // --- Menu buttons ---
    auto *button_start = new QPushButton("Start Game");
    auto *button_quit = new QPushButton("Quit Game");

    button_start->setStyleSheet(button_start->styleSheet() + BUTTON_STYLE);
    button_quit->setStyleSheet(button_quit->styleSheet() + BUTTON_STYLE);

    button_start->setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    button_quit->setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    // --- Layout ---
    auto *layout = new QVBoxLayout(this);

    layout->addStretch();
    layout->addWidget(game_title);
    layout->addStretch();
    layout->addWidget(button_start, 0, Qt::AlignCenter);
    layout->addWidget(button_quit, 0, Qt::AlignCenter);
    layout->addStretch();

    QObject::connect(button_start, &QPushButton::clicked, 
        this, &MainMenuPage::startGameClicked);
    QObject::connect(button_quit, &QPushButton::clicked, 
        this, &MainMenuPage::quitToDesktopClicked);
}