#include "pages/MainMenuPage.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

MainMenuPage::MainMenuPage(QWidget *parent) : QWidget(parent)
{
    int BUTTON_WIDTH = 400;
    int BUTTON_HEIGHT = 100;


    // --- Title Card ---
    auto *game_title = new QLabel("Zombie Apocalypse Survivors");

    game_title->setAlignment(Qt::AlignCenter);
    game_title->setStyleSheet("font-size: 56px;" "font-weight: bold;");

    // --- Menu buttons ---
    auto *button_start = new QPushButton("Start Game");
    auto *button_quit = new QPushButton("Quit Game");

    button_start->setStyleSheet("font-size: 40px;");
    button_quit->setStyleSheet("font-size: 40px;");

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

    QObject::connect(button_quit, &QPushButton::clicked, this, &MainMenuPage::QuitGameClicked);
    QObject::connect(button_start, &QPushButton::clicked, this, &MainMenuPage::StartGameClicked);
}