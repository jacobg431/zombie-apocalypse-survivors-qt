#include "managers/SessionManager.hpp"
#include "models/PlayerCharacter.hpp"

SessionManager& SessionManager::instance()
{
    static SessionManager instance;
    return instance;
}

SessionManager::SessionManager(QObject* parent)
    : QObject(parent), _playerCharacter(new PlayerCharacter())
{
    connect(_playerCharacter, &PlayerCharacter::playerStateChanged,
    this, &SessionManager::playerStateChanged);
}

PlayerCharacter* SessionManager::getPlayerCharacter()
{
    return _playerCharacter;
}

void SessionManager::startNewSession()
{
    _playerCharacter->reset();
    emit sessionStarted();
}

void SessionManager::clearSession()
{
    _playerCharacter->reset();
    emit sessionCleared();
}
