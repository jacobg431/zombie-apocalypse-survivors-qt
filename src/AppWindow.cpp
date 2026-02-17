#include "AppWindow.hpp"
#include <QStackedWidget>

#include "pages/MainMenuPage.hpp"
#include "pages/CharacterCreationPage.hpp"

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Zombie Apocalypse Survivors");
    resize(600, 400);

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    
    menu = new MainMenuPage(this);
    characterCreation = new CharacterCreationPage(this);

    stack->addWidget(menu);
    stack->addWidget(characterCreation);

    connect(menu, &MainMenuPage::StartGameClicked, this, &AppWindow::showCharacterCreation);
    connect(menu, &MainMenuPage::QuitGameClicked, this, &QWidget::close);

    showMenu();
}

void AppWindow::showMenu()
{
    stack->setCurrentWidget(menu);
}

void AppWindow::showCharacterCreation()
{
    stack->setCurrentWidget(characterCreation);
}