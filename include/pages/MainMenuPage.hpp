#pragma once

#include <QWidget>

class QFrame;
class QLabel;
class QPushButton;

class MainMenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuPage(QWidget *parent = nullptr);

private:
    static const int BUTTON_WIDTH = 400;
    static const int BUTTON_HEIGHT = 100;

    QLabel* _title = nullptr;
    QPushButton* _newGameButton = nullptr;
    QPushButton* _loadSaveButton = nullptr;
    QPushButton* _quitToDesktopButton = nullptr;

    QFrame* createWrapper();
    void setWidgets();
    void wireConnections();
    void applyStyling();

signals:
    void newGameClicked();
    void loadSaveClicked();
    void quitToDesktopClicked();
};