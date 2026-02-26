#include "managers/SessionManager.hpp"
#include "models/SessionStateModel.hpp"

SessionManager& SessionManager::instance()
{
    static SessionManager instance;
    return instance;
}

SessionManager::SessionManager(QObject* parent)
    : QObject(parent)
{}

void SessionManager::startNewSession()
{
    _playerState = std::make_unique<PlayerState>();
    emit sessionStarted();
}

void SessionManager::clearSession()
{
    _playerState.reset();
    emit sessionCleared();
}

void SessionManager::setCharacterName(const QString& characterName)
{
    _playerState->characterName = characterName;
    emit playerStateChanged();
}

void SessionManager::setClassName(const QString& className)
{
    _playerState->className = className;
    emit playerStateChanged();
}

void SessionManager::addExperience(int amount)
{
    _playerState->experience += amount;
    emit playerStateChanged();
}

void SessionManager::applyDamage(int amount)
{
    _playerState->health -= amount;
    emit playerStateChanged();
}