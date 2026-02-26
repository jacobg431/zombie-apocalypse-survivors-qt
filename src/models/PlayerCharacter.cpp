#include "models/PlayerCharacter.hpp"

// Getters
QString PlayerCharacter::getCharacterName()
{
    return _playerState->characterName;
}
QString PlayerCharacter::getClassName()
{
    return _playerState->className;
}
QString PlayerCharacter::getDescription()
{
    return _playerState->description;
}
QStringList PlayerCharacter::getSkills()
{
    return _playerState->skills;
}

int PlayerCharacter::getStrength()
{
    return _playerState->strength;
}
int PlayerCharacter::getEndurance()
{
    return _playerState->endurance;
}
int PlayerCharacter::getAgility()
{
    return _playerState->agility;
}
int PlayerCharacter::getCourage()
{
    return _playerState->courage;
}
int PlayerCharacter::getIntelligence()
{
    return _playerState->intelligence;
}
int PlayerCharacter::getLeadership()
{
    return _playerState->leadership;
}
int PlayerCharacter::getTrustWorthiness()
{
    return _playerState->trustworthiness;
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
    _playerState->characterName = characterName;
    emit playerStateChanged();
}
void PlayerCharacter::setClassName(const QString& className)
{
    _playerState->className = className;
    emit playerStateChanged();
}

void PlayerCharacter::setStrength(int value)
{
    _playerState->strength = value;
}
void PlayerCharacter::setEndurance(int value)
{
    _playerState->endurance = value;
}
void PlayerCharacter::setAgility(int value)
{
    _playerState->agility = value;
}
void PlayerCharacter::setCourage(int value)
{
    _playerState->courage = value;
}
void PlayerCharacter::setIntelligence(int value)
{
    _playerState->intelligence = value;
}
void PlayerCharacter::setLeadership(int value)
{
    _playerState->leadership = value;
}
void PlayerCharacter::setTrustWorthiness(int value)
{
    _playerState->trustworthiness = value;
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
    _playerState->description = description;
}
void PlayerCharacter::setSkills(QStringList& skills)
{
    _playerState->skills = skills;
}
void PlayerCharacter::addSkill(const QString& skill)
{
    _playerState->skills.push_back(skill);
}

void PlayerCharacter::reset()
{
    setCharacterName("");
    setClassName("");
    setDescription("");
    setSkills({});
    setAttributes(0, 0, 0, 0, 0, 0, 0);
        
}