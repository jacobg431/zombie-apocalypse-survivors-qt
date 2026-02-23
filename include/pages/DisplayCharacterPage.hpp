#pragma once

#include <QWidget>
#include <QMap>

#include "managers/RoleManager.hpp"

class QPushButton;
class QString;
class QLabel;
class QFrame;
class CharacterActionsPanel;

class DisplayCharacterPage : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayCharacterPage(QWidget *parent = nullptr);

private:
    QMap<QString, QLabel *> _attributesMap;

    QWidget* createCharacterStatsPanel();
    QWidget* createCharacterActionsPanel();
    QWidget* createInventoryPanel();
    QFrame* createWrapper();

    void applyStyling();

    CharacterActionsPanel* _characterActionsPanel;

signals:
    void itemsShopClicked();
    void fightClicked();
    void mainMenuClicked();
};
