#pragma once

#include <memory>

#include <QString>
#include <QStringList>

struct PlayerState
{
    QString characterName;
    QString className;
    QString description;
    QStringList skills = {};

    int strength = 0;
    int endurance = 0;
    int agility = 0;
    int courage = 0;
    int intelligence = 0;
    int leadership = 0;
    int trustworthiness = 0;
};