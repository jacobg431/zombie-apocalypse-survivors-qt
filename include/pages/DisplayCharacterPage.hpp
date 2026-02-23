#pragma once

#include <QWidget>
#include <QMap>

#include "managers/RoleManager.hpp"

class QPushButton;
class QString;
class QLabel;
class QFrame;

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

    QPushButton* _actionsButton = nullptr;
    QPushButton* _itemsShopButton = nullptr;
    QPushButton* _mainMenuButton = nullptr;

signals:
    void actionsClicked();
    void itemsShopClicked();
    void mainMenuClicked();
};
