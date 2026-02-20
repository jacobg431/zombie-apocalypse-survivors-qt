#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;
class ItemsShopPage;
class DisplayCharacterPage;
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
    QStackedWidget *_stack;
    MainMenuPage *_menu;
    CharacterCreationPage *_characterCreation;
    ItemsShopPage *_itemsShop;
    DisplayCharacterPage *_displayCharacter;
    PauseMenu *_pauseOverlay;
    GoBackPanel *_goBackPanel;

    void setPaused(bool on);
    bool isPaused() const;
    bool pauseAllowed() const;

public slots:
    void showMenu();
    void showCharacterCreation();
    void showDisplayCharacter();
    void showItemsShop();
};