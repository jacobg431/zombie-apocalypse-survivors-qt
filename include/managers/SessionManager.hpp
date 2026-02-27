#pragma once

#include <vector>

#include <QApplication>
#include <QSessionManager>
#include <QSettings>

#include "models/PlayerCharacter.hpp"

class SessionManager : public QObject
{
    Q_OBJECT

public:
    static SessionManager& instance();
    
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    
    PlayerCharacter* getPlayerCharacter(); 

    void startNewSession();
    void clearSession();

private:
    explicit SessionManager(QObject* parent = nullptr); 
    PlayerCharacter* _playerCharacter = nullptr;

signals:
    void sessionStarted(); 
    void sessionCleared();
    void playerStateChanged();
};
