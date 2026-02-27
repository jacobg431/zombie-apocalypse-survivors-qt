#pragma once

#include <vector>

#include <QApplication>
#include <QSessionManager>
#include <QSettings>

class SessionManager : public QObject
{
    Q_OBJECT

public:
    static SessionManager& instance();
    
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    
    PlayerCharacter* getPlayerCharacter(); 

    void startNewSession();
    void endSession();

private:
    explicit SessionManager(QObject* parent = nullptr); 

signals:
    void sessionStarted(); 
    void sessionEnded();
};
