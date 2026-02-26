#include <memory>

#include "models/SessionStateModel.hpp"

class PlayerCharacter
{

public:
    PlayerCharacter() = default;
    
    QString getCharacterName();
    QString getClassName();
    QString getDescription();
    QStringList getSkills();

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
    void setSkills(QStringList& skills);
    void addSkill(const QString& skill);

    void reset();

private:
    std::unique_ptr<PlayerState> _playerState;

signals:
    void playerStateChanged();

};
