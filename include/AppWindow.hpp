#pragma once
#include <QMainWindow>

class QStackedWidget;
class MainMenuPage;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    MainMenuPage *menu;

    void showMenu();
};