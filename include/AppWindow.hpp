#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include <QResizeEvent>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;
class PauseMenu;

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
    MainMenuPage *menu;
    CharacterCreationPage *characterCreation;
    PauseMenu *pauseOverlay;


    void setPaused(bool on);
    bool isPaused() const;
    bool pauseAllowed() const;

    void showMenu();
    void showCharacterCreation();
};