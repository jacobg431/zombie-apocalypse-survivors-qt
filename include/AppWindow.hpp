#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;
class ItemsShopPage;
class DisplayCharacterPage;
class GameMenuPanel;
class GoBackPanel;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QStackedWidget *_stack;
    MainMenuPage *_mainMenu;
    CharacterCreationPage *_characterCreation;
    ItemsShopPage *_itemsShop;
    DisplayCharacterPage *_displayCharacter;
    GameMenuPanel *_gameMenuPanel;
    GoBackPanel *_goBackPanel;

    void readyGameMenuPanel();
    void stackPages();
    void wireConnections();
    void openGameMenu();
    void closeGameMenu();
    bool isGameMenuOpen() const;
    bool isGameMenuAvailable() const;

public slots:
    void showMainMenu();
    void showCharacterCreation();
    void showDisplayCharacter();
    void showExplore();
    void showFight();
    void showShopMenu();

private slots:
    void onEscClicked();
    void onF11Clicked();

    void onNewGameClicked();
    void onLoadSaveClicked();

    void onCharacterCreated();
    void onGameMenuClicked();
    
    void onResumeClicked();
    void onSaveClicked();
    void onQuitClicked();

};