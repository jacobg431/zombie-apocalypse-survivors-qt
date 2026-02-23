#pragma once

class QWidget;
class QString;
class QFrame;

#include "managers/RoleManager.hpp"

class CharacterStatsPanel : public QWidget
{
    Q_OBJECT

public:
    CharacterStatsPanel(const QString& name, const Survivor *characterClass, QWidget *parent = nullptr);

private: 
    QWidget* createTitleLabel(const QString& title);
    QFrame* createWrapper(const QString& title);
    void applyStyling();
    Survivor* _characterClass;
};
