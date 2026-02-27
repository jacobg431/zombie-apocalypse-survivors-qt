#include <memory>

#include <QJsonObject>

#include "models/GameState.hpp"
#include "models/PlayerCharacter.hpp"

GameState::GameState()
    : _playerCharacter(std::make_unique<PlayerCharacter>())
{}

PlayerCharacter& GameState::getPlayer()
{
    return *_playerCharacter;
}

const PlayerCharacter& GameState::getPlayer() const
{
    return *_playerCharacter;
}

QJsonObject GameState::toJson() const
{
    QJsonObject root;
    root["saveVersion"] = CURRENT_SAVE_VERSION;
    root["player"] = _playerCharacter->toJson();
}

bool GameState::fromJson(const QJsonObject& json)
{
    if (!json.contains("saveVersion")) return false;

    int saveVersion = json["saveVersion"].toInt();
    if (saveVersion != CURRENT_SAVE_VERSION) return false;
    if (!json.contains("player")) return false;

    return _playerCharacter->fromJson(json["player"].toObject());
}

void GameState::reset()
{
    _playerCharacter->reset();
}