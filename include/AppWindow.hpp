#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;
class ActionsMenuPage;
class ItemsShopPage;
class PauseMenu;
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
    QStackedWidget *stack;
    MainMenuPage *mainMenu;
    CharacterCreationPage *characterCreation;
    ActionsMenuPage *actionsMenu;
    ItemsShopPage *itemsShop;
    PauseMenu *pauseOverlay;
    GoBackPanel *goBackPanel;


    void setPaused(bool on);
    bool isPaused() const;
    bool pauseAllowed() const;

public slots:
    void showMainMenu();
    void showCharacterCreation();
    void showActionsMenu();
    void showShopMenu();
};