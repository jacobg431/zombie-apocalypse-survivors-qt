#include "managers/SessionManager.hpp"
#include "managers/GameStateManager.hpp"

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
    GameStateManager::instance().createNewGame();
    emit sessionStarted();
}

void SessionManager::endSession()
{
    GameStateManager::instance().clear();
    emit sessionEnded();
}
