#include <QApplication>
#include <QSessionManager>
#include <QSettings>

#include "models/SessionStateModel.hpp"

class SessionManager : public QObject
{
    Q_OBJECT

public:
    static SessionManager& instance();
    
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    
    void startNewSession();
    void clearSession();

    void setCharacterName(const QString& characterName);
    void setClassName(const QString& className);
    void addExperience(int amount);
    void applyDamage(int amount);

private:
    explicit SessionManager(QObject* parent = nullptr); 
    std::unique_ptr<PlayerState> _playerState;

signals:
    void sessionStarted(); 
    void sessionCleared();
    void playerStateChanged();
};
