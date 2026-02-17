#include "AppWindow.hpp"
#include <QStackedWidget>

#include "pages/MainMenuPage.hpp"

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Zombie Apocalypse Survivors");
    resize(600, 400);

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    menu = new MainMenuPage(this);
    stack->addWidget(menu);

    connect(menu, &MainMenuPage::QuitGameClicked, this, &QWidget::close);

    showMenu();
}

void AppWindow::showMenu()
{
    stack->setCurrentWidget(menu);
}