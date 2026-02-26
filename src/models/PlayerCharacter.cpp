
#include <QString>
#include <QStringList>

#include "models/PlayerCharacter.hpp"

// Getters
QString PlayerCharacter::getCharacterName()
{
    return _characterName;
}
QString PlayerCharacter::getClassName()
{
    return _className;
}
QString PlayerCharacter::getDescription()
{
    return _description;
}
QString PlayerCharacter::getSkills()
{
    return _skills.join("\n");
}
QStringList PlayerCharacter::getSkillsStringList()
{
    return _skills;
}
QStringList PlayerCharacter::getAttributesStringList()
{
    QStringList attributes = {};
    
    attributes.push_back(QString::number(getStrength()));
    attributes.push_back(QString::number(getEndurance()));
    attributes.push_back(QString::number(getAgility()));
    attributes.push_back(QString::number(getCourage()));
    attributes.push_back(QString::number(getIntelligence()));
    attributes.push_back(QString::number(getLeadership()));
    attributes.push_back(QString::number(getTrustWorthiness()));

    return attributes;
}

int PlayerCharacter::getStrength()
{
    return _strength;
}
int PlayerCharacter::getEndurance()
{
    return _endurance;
}
int PlayerCharacter::getAgility()
{
    return _agility;
}
int PlayerCharacter::getCourage()
{
    return _courage;
}
int PlayerCharacter::getIntelligence()
{
    return _intelligence;
}
int PlayerCharacter::getLeadership()
{
    return _leadership;
}
int PlayerCharacter::getTrustWorthiness()
{
    return _trustworthiness;
}

std::vector<int> PlayerCharacter::getAttributes()
{
    std::vector<int> attributes;

    attributes.push_back(getStrength());
    attributes.push_back(getEndurance());
    attributes.push_back(getAgility());
    attributes.push_back(getCourage());
    attributes.push_back(getIntelligence());
    attributes.push_back(getLeadership());
    attributes.push_back(getTrustWorthiness());

    return attributes;
}

// Setters
void PlayerCharacter::setCharacterName(const QString& characterName)
{
    _characterName = characterName;
    emit playerStateChanged();
}
void PlayerCharacter::setClassName(const QString& className)
{
    _className = className;
    emit playerStateChanged();
}

void PlayerCharacter::setStrength(int value)
{
    _strength = value;
}
void PlayerCharacter::setEndurance(int value)
{
    _endurance = value;
}
void PlayerCharacter::setAgility(int value)
{
    _agility = value;
}
void PlayerCharacter::setCourage(int value)
{
    _courage = value;
}
void PlayerCharacter::setIntelligence(int value)
{
    _intelligence = value;
}
void PlayerCharacter::setLeadership(int value)
{
    _leadership = value;
}
void PlayerCharacter::setTrustWorthiness(int value)
{
    _trustworthiness = value;
}

void PlayerCharacter::setAttributes
(
    int strength,
    int endurance,
    int agility,
    int courage,
    int intelligence,
    int leadership,
    int trustworthiness
)
{
    setStrength(strength);
    setEndurance(endurance);
    setAgility(agility);
    setCourage(courage);
    setIntelligence(intelligence);
    setLeadership(leadership);
    setTrustWorthiness(trustworthiness);
}

void PlayerCharacter::setDescription(const QString& description)
{
    _description = description;
}
void PlayerCharacter::setSkills(QStringList& skills)
{
    _skills = skills;
}
void PlayerCharacter::addSkill(const QString& skill)
{
    _skills.push_back(skill);
}

void PlayerCharacter::reset()
{
    setCharacterName("");
    setClassName("");
    setDescription("");
    setSkills({});
    setAttributes(0, 0, 0, 0, 0, 0, 0);
        
}