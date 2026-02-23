#pragma once

class QWidget;
class QString;
class QFrame;

#include "managers/RoleManager.hpp"

class CharacterStatsPanel : public QWidget
{
    Q_OBJECT

public:
    CharacterStatsPanel(Survivor *characterClass = nullptr, QWidget *parent = nullptr);

private: 
    QWidget* createTitleLabel();
    QFrame* createWrapper();
    void applyStyling();
    Survivor* _characterClass;
};
