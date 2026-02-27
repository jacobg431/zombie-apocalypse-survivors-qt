#pragma once
#include <QWidget>

class MainMenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuPage(QWidget *parent = nullptr);

signals:
    void startGameClicked();
    void quitToDesktopClicked();
};