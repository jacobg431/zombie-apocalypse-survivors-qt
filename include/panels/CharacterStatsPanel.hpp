#pragma once

#include <QStringList>

#include "managers/RoleManager.hpp"

class QWidget;
class QString;
class QFrame;
class InfoBox;

class CharacterStatsPanel : public QWidget
{
    Q_OBJECT

public:
    CharacterStatsPanel(QWidget *parent = nullptr);
    void setContent
    (
        const QStringList& attributeContent,
        const QString& descriptionContent,
        const QString& skillContent
    );
    void setContentRandom
    (
        QStringList& attributeContent, 
        QStringList& skillContent
    );

private: 
    inline static const QStringList ATTRIBUTES = {
        "Strength", "Agility", "Endurance", "Intelligence",
        "Leadership", "Trustworthiness", "Courage"
    };
    inline static const QStringList ATTRIBUTES_DEFAULT_VALUES = {
        "0", "0", "0", "0", "0", "0", "0"
    };

    InfoBox* _descriptionInfoBox = nullptr;
    InfoBox* _attributesInfoBox = nullptr;
    InfoBox* _skillsInfoBox = nullptr;

    QFrame* createWrapper();
    void applyStyling();
};
