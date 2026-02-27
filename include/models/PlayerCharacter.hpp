#pragma once

#include <vector>

#include <QObject>
#include <QString>
#include <QStringList>

class QJsonObject;

class PlayerCharacter : public QObject
{
    Q_OBJECT

public:
    PlayerCharacter(QObject* parent = nullptr);

    QJsonObject toJson();
    bool fromJson(const QJsonObject& json);
    
    QString getCharacterName();
    QString getClassName();
    QString getDescription();
    QString getSkills();
    QStringList getSkillsStringList();
    QStringList getAttributesStringList();

    int getStrength();
    int getEndurance();
    int getAgility();
    int getCourage();
    int getIntelligence();
    int getLeadership();
    int getTrustWorthiness();

    std::vector<int> getAttributes();
    
    void setCharacterName(const QString& characterName);
    void setClassName(const QString& className);

    void setStrength(int value);
    void setEndurance(int value);
    void setAgility(int value);
    void setCourage(int value);
    void setIntelligence(int value);
    void setLeadership(int value);
    void setTrustWorthiness(int value);

    void setAttributes
    (
        int strength,
        int endurance,
        int agility,
        int courage,
        int intelligence,
        int leadership,
        int trustworthiness
    );

    void setDescription(const QString& description);
    void setSkills(const QStringList& skills);
    void addSkill(const QString& skill);

    void reset();

private:
    QString _characterName;
    QString _className;
    QString _description;
    QStringList _skills = {};

    int _strength = 0;
    int _endurance = 0;
    int _agility = 0;
    int _courage = 0;
    int _intelligence = 0;
    int _leadership = 0;
    int _trustworthiness = 0;

signals:
    void playerStateChanged();

};
