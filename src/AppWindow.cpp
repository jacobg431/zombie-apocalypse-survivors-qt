#include "AppWindow.hpp"
#include <QStackedWidget>

#include "pages/MainMenuPage.hpp"

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    // --- Window & Styling ---
    setWindowTitle("Zombie Apocalypse Survivors");

    // --- Pages ---
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    menu = new MainMenuPage(this);
    stack->addWidget(menu);

    // --- Connect signals ---
    connect(menu, &MainMenuPage::QuitGameClicked, this, &QWidget::close);

    // --- Show menu at startup ---
    showMenu();
}

void AppWindow::showMenu()
{
    stack->setCurrentWidget(menu);
}