#pragma once

#include <memory>

#include "models/PlayerCharacter.hpp"

class QJsonObject;

class GameState
{
public:
    explicit GameState();

    PlayerCharacter& getPlayer();
    const PlayerCharacter& getPlayer() const;

    QJsonObject toJson() const;
    bool fromJson(const QJsonObject& json);

    void reset();

private:
    static const int CURRENT_SAVE_VERSION = 1;
    std::unique_ptr<PlayerCharacter> _playerCharacter;

};
