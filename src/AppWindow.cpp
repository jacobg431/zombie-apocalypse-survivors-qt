#include "AppWindow.hpp"

#include "pages/MainMenuPage.hpp"
#include "pages/CharacterCreationPage.hpp"
#include "pages/DisplayCharacterPage.hpp"
#include "pages/ItemsShopPage.hpp"
#include "panels/GoBackPanel.hpp"
#include "widgets/PauseMenu.hpp"

#include <QStackedWidget>
#include <QShortcut>

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    // --- Window & Styling ---
    setWindowTitle("Zombie Apocalypse Survivors");

    readyPauseMenu();
    stackPages();
    wireConnections();
    showMenu();
}

void AppWindow::readyPauseMenu()
{
    _pauseOverlay = new PauseMenu(this);
    _pauseOverlay->hide();
    _pauseOverlay->raise();
}

void AppWindow::stackPages()
{   
    _stack = new QStackedWidget(this);
    setCentralWidget(_stack);
    _menu = new MainMenuPage(this);
    _characterCreation = new CharacterCreationPage(this);
    _displayCharacter = new DisplayCharacterPage(this);
    _itemsShop = new ItemsShopPage(this);

    _stack->addWidget(_menu);
    _stack->addWidget(_characterCreation);
    _stack->addWidget(_displayCharacter);
    _stack->addWidget(_itemsShop);
}

void AppWindow::wireConnections()
{
    // --- Main Menu ---
    connect(_menu, &MainMenuPage::StartGameClicked, 
        this, &AppWindow::showDisplayCharacter);
    connect(_menu, &MainMenuPage::QuitGameClicked, 
        this, &QWidget::close);

    // --- Paused Menu ---
    auto *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(esc, &QShortcut::activated, this, [this]
            { if (!pauseAllowed()) return;setPaused(!isPaused()); });
    connect(_pauseOverlay, &PauseMenu::ResumeClicked, this, [this]
            { setPaused(false); });
    connect(_pauseOverlay, &PauseMenu::ReturnToMenuClicked, this, [this]
            { setPaused(false); showMenu(); });

    // --- Ingame Routing ---
    connect(_characterCreation, &CharacterCreationPage::characterCreated,
        this, &AppWindow::showDisplayCharacter);
    connect(_itemsShop, &ItemsShopPage::GoBackClicked,
        this, &AppWindow::showDisplayCharacter);
    connect(_displayCharacter, &DisplayCharacterPage::itemsShopClicked,
        this, &AppWindow::showItemsShop);
    connect(_displayCharacter, &DisplayCharacterPage::fightClicked,
        this, &AppWindow::showFight);
    connect(_displayCharacter, &DisplayCharacterPage::mainMenuClicked,
        this, &AppWindow::showMenu);
}

void AppWindow::showMenu()
{
    _stack->setCurrentWidget(_menu);
}

void AppWindow::showCharacterCreation()
{
    _stack->setCurrentWidget(_characterCreation);
}

void AppWindow::showDisplayCharacter()
{
    _stack->setCurrentWidget(_displayCharacter);
}

void AppWindow::showItemsShop()
{
    _stack->setCurrentWidget(_itemsShop);
}

void AppWindow::showFight()
{
    return;
}

void AppWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (_pauseOverlay)
    {
        _pauseOverlay->setGeometry(centralWidget()->rect());
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
    return _pauseOverlay->isVisible();
}

bool AppWindow::pauseAllowed() const
{
    return _stack->currentWidget() != _menu;
}

void AppWindow::setPaused(bool on)
{
    _pauseOverlay->setVisible(on);
    if (on)
    {
        _pauseOverlay->raise();
    }

    // pause game things here
}