#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;
class ItemsShopPage;
class DisplayCharacterPage;
class PauseOverlayPanel;
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
    PauseOverlayPanel *_pauseOverlay;
    GoBackPanel *_goBackPanel;

    void readyPauseOverlayPanel();
    void stackPages();
    void wireConnections();
    void setPaused(bool on);
    bool isPaused() const;
    bool pauseAllowed() const;

public slots:
    void showMainMenu();
    void showCharacterCreation();
    void showDisplayCharacter();
    void showFight();
    void showShopMenu();

private slots:
    void onEscClicked();
    void onF11Clicked();
    void onCharacterCreated();
    void onResumeClicked();
    void onSaveClicked();
    void onQuitClicked();
};