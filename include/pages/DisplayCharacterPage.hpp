#pragma once

#include <QWidget>
#include <QMap>

#include "managers/RoleManager.hpp"

class QPushButton;
class QString;
class QLabel;
class QFrame;
class CharacterStatsPanel;
class CharacterActionsPanel;
class CharacterImagePanel;
class ActionsMenuPanel;
class GoBackPanel;

class DisplayCharacterPage : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayCharacterPage(QWidget *parent = nullptr);
    void updateStatsPanelContent();

private:
    QMap<QString, QLabel *> _attributesMap;

    QWidget* createCharacterStatsPanel();
    QWidget* createCharacterImagePanel();
    QWidget* createCharacterActionsPanel();
    QWidget* createInventoryPanel();
    QWidget *createGoBackPanel();
    QFrame* createWrapper();

    void applyStyling();

    CharacterStatsPanel* _characterStatsPanel = nullptr;
    ActionsMenuPanel* _actionsMenuPanel = nullptr;
    CharacterImagePanel* _characterImagePanel = nullptr;
    GoBackPanel* _goBackPanel = nullptr;

signals:
    void exploreClicked();
    void fightClicked();
    void itemsShopClicked();
    void gameMenuClicked();
};
