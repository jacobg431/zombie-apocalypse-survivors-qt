#include "AppWindow.hpp"

#include "pages/MainMenuPage.hpp"
#include "pages/CharacterCreationPage.hpp"
#include "pages/ActionsMenuPage.hpp"
#include "pages/ItemsShopPage.hpp"

#include "panels/GoBackPanel.hpp"
#include "widgets/PauseMenu.hpp"

#include <QStackedWidget>
#include <QShortcut>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    // --- Window & Styling ---
    setWindowTitle("Zombie Apocalypse Survivors");

    // --- Pages ---
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // --- Pause menu ---
    pauseOverlay = new PauseMenu(this);
    pauseOverlay->hide();
    pauseOverlay->raise();

    connect(pauseOverlay, &PauseMenu::ResumeClicked, this, [this]
            { setPaused(false); });
    connect(pauseOverlay, &PauseMenu::ReturnToMenuClicked, this, [this]
            { setPaused(false); showMainMenu(); });

    // --- Pages ---
    mainMenu = new MainMenuPage(this);
    characterCreation = new CharacterCreationPage(this);
    actionsMenu = new ActionsMenuPage(this);
    itemsShop = new ItemsShopPage(this);

    stack->addWidget(mainMenu);
    stack->addWidget(characterCreation);
    stack->addWidget(actionsMenu);
    stack->addWidget(itemsShop);

    // --- Connections ---

    // Keyboard shortcuts
    auto *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(esc, &QShortcut::activated, this, [this]
            { if (!pauseAllowed()) return;setPaused(!isPaused()); });

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    connect(shortcut, &QShortcut::activated, this, [=]()
            {
                if (windowState() & Qt::WindowFullScreen)
                    showNormal();
                else
                    showFullScreen();
            });

    // Page navigation
    connect(mainMenu, &MainMenuPage::StartGameClicked,
            this, &AppWindow::showCharacterCreation);

    connect(mainMenu, &MainMenuPage::QuitGameClicked,
            this, &QWidget::close);

    connect(characterCreation, &CharacterCreationPage::characterCreated,
            this, &AppWindow::showActionsMenu);

    connect(actionsMenu, &ActionsMenuPage::GoToShopClicked,
            this, &AppWindow::showShopMenu);

    connect(itemsShop, &ItemsShopPage::GoBackClicked,
            this, &AppWindow::showActionsMenu);

    // --- Show menu at startup ---
    showMainMenu();
}

void AppWindow::showMainMenu()
{
    stack->setCurrentWidget(mainMenu);
}

void AppWindow::showCharacterCreation()
{
    stack->setCurrentWidget(characterCreation);
}

void AppWindow::showActionsMenu()
{
    stack->setCurrentWidget(actionsMenu);
}

void AppWindow::showShopMenu()
{
    stack->setCurrentWidget(itemsShop);
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
    return stack->currentWidget() != mainMenu;
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