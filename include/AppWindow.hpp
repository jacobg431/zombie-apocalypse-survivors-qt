#pragma once
#include <QMainWindow>

class QStackedWidget;
class MainMenuPage;
class CharacterCreationPage;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    MainMenuPage *menu;
    CharacterCreationPage *characterCreation;

    void showMenu();
    void showCharacterCreation();
};