#pragma once

#include <QString>
#include <memory>

struct PlayerState
{
    QString characterName;
    QString className;
    int level = 1;
    int health = 100;
    int experience = 0;
};