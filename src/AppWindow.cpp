#include <QStackedWidget>
#include <QShortcut>

#include "AppWindow.hpp"

#include "managers/SessionManager.hpp"

#include "pages/MainMenuPage.hpp"
#include "pages/CharacterCreationPage.hpp"
#include "pages/DisplayCharacterPage.hpp"
#include "pages/ItemsShopPage.hpp"

#include "panels/GoBackPanel.hpp"
#include "panels/PauseOverlayPanel.hpp"

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent)
{
    // --- Window & Styling ---
    setWindowTitle("Zombie Apocalypse Survivors");

    readyPauseOverlayPanel();
    stackPages();
    wireConnections();
    showMainMenu();
}

void AppWindow::readyPauseOverlayPanel()
{
    _pauseOverlay = new PauseOverlayPanel(this);
    _pauseOverlay->hide();
    _pauseOverlay->raise();
}

void AppWindow::stackPages()
{   
    _stack = new QStackedWidget(this);
    setCentralWidget(_stack);
    _mainMenu = new MainMenuPage(this);
    _characterCreation = new CharacterCreationPage(this);
    _displayCharacter = new DisplayCharacterPage(this);
    _itemsShop = new ItemsShopPage(this);

    _stack->addWidget(_mainMenu);
    _stack->addWidget(_characterCreation);
    _stack->addWidget(_displayCharacter);
    _stack->addWidget(_itemsShop);
}

void AppWindow::wireConnections()
{
    // --- Shortcuts ---
    auto *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(esc, &QShortcut::activated, 
        this, &AppWindow::onEscClicked);

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    connect(shortcut, &QShortcut::activated, 
        this, onF11Clicked);

    // --- Main Menu ---
    connect(_mainMenu, &MainMenuPage::newGameClicked, 
        this, &AppWindow::onNewGameClicked);
        
    connect(_mainMenu, &MainMenuPage::quitToDesktopClicked, 
        this, &QWidget::close);

    // --- Pause Overlay ---
    connect(_pauseOverlay, &PauseOverlayPanel::resumeClicked, 
        this, &AppWindow::onResumeClicked);

    connect(_pauseOverlay, &PauseOverlayPanel::saveClicked,
        this, &AppWindow::onSaveClicked);

    connect(_pauseOverlay, &PauseOverlayPanel::quitClicked, 
        this, &AppWindow::onQuitClicked);

    // --- Ingame Routing ---
    connect(_characterCreation, &CharacterCreationPage::characterCreated,
        this, &AppWindow::onCharacterCreated);

    connect(_itemsShop, &ItemsShopPage::goBackClicked,
        this, &AppWindow::showDisplayCharacter);

    connect(_displayCharacter, &DisplayCharacterPage::exploreClicked,
        this, &AppWindow::showExplore);

    connect(_displayCharacter, &DisplayCharacterPage::fightClicked,
        this, &AppWindow::showFight);
    
    connect(_displayCharacter, &DisplayCharacterPage::itemsShopClicked,
            this, &AppWindow::showShopMenu);

    connect(_displayCharacter, &DisplayCharacterPage::gameMenuClicked,
        this, &AppWindow::showMainMenu);
}

void AppWindow::showMainMenu()
{
    _stack->setCurrentWidget(_mainMenu);
}

void AppWindow::showCharacterCreation()
{
    _stack->setCurrentWidget(_characterCreation);
}

void AppWindow::showDisplayCharacter()
{
    _stack->setCurrentWidget(_displayCharacter);
}

void AppWindow::showExplore()
{
    return;
}

void AppWindow::showFight()
{
    return;
}

void AppWindow::showShopMenu()
{
    _stack->setCurrentWidget(_itemsShop);
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
    return _stack->currentWidget() != _mainMenu;
}

void AppWindow::setPaused(bool on)
{
    _pauseOverlay->setVisible(on);
    if (on)
    {
        _pauseOverlay->raise();
    }
}

void AppWindow::onEscClicked()
{
    if (!pauseAllowed()) return; 
    setPaused(!isPaused());
}

void AppWindow::onF11Clicked()
{
    if (windowState() & Qt::WindowFullScreen)
        showNormal();
    else
        showFullScreen();
}

void AppWindow::onNewGameClicked()
{
    auto &sessionManager = SessionManager::instance();
    sessionManager.startNewSession();
    showCharacterCreation();
}

void AppWindow::onLoadSaveClicked()
{}

void AppWindow::onCharacterCreated()
{
    _displayCharacter->updateStatsPanelContent();
    showDisplayCharacter();
}

void AppWindow::onGameMenuClicked()
{
    setPaused(true);
}

void AppWindow::onResumeClicked()
{
    setPaused(false);
}

void AppWindow::onSaveClicked()
{}

void AppWindow::onQuitClicked()
{
    setPaused(false); 
    auto &sessionManager = SessionManager::instance();
    sessionManager.clearSession();
    showMainMenu();
}