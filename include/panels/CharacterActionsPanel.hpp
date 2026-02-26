#pragma once

#include <QWidget>

class QFrame;
class QString;
class QPushButton;

class CharacterActionsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterActionsPanel(QWidget *parent = nullptr);

signals:
    void itemsShopClicked();
    void fightClicked();
    void mainMenuClicked();

private:
    QWidget* createTitleLabel();
    QFrame* createButtonWrapper();
    QFrame* createWrapper();
    void applyStyling();

    QPushButton* _itemsShopButton;
    QPushButton* _fightButton;
    QPushButton* _mainMenuButton;

};
