#include "AppWindow.hpp"

#include "pages/MainMenuPage.hpp"
#include "pages/CharacterCreationPage.hpp"
#include "widgets/PauseMenu.hpp"

#include <QStackedWidget>
#include <QShortcut>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Zombie Apocalypse Survivors");
    resize(600, 400);

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // --- Pause menu ---
    pauseOverlay = new PauseMenu(this);
    pauseOverlay->hide();
    pauseOverlay->raise();

    connect(pauseOverlay, &PauseMenu::ResumeClicked, this, [this]
            { setPaused(false); });
    connect(pauseOverlay, &PauseMenu::ReturnToMenuClicked, this, [this]
            { setPaused(false); showMenu(); });

    // --- Pages ---
    menu = new MainMenuPage(this);
    characterCreation = new CharacterCreationPage(this);

    stack->addWidget(menu);
    stack->addWidget(characterCreation);

    // --- Connections ---
    auto *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(esc, &QShortcut::activated, this, [this]
            { if (!pauseAllowed()) return;setPaused(!isPaused()); });

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

void AppWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (pauseOverlay)
    {
        pauseOverlay->setGeometry(centralWidget()->rect());
    }
}

void AppWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && pauseAllowed())
        setPaused(!isPaused());

    else
        QMainWindow::keyPressEvent(event);
}

bool AppWindow::isPaused() const
{
    return pauseOverlay->isVisible();
}

bool AppWindow::pauseAllowed() const
{
    return stack->currentWidget() != menu;
}

void AppWindow::setPaused(bool on)
{
    pauseOverlay->setVisible(on);
    if (on)
    {
        pauseOverlay->raise();
    }

    // pause game things here
}