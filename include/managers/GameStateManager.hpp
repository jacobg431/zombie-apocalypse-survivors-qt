#pragma once

#include <memory>
#include <QObject>
#include "models/GameState.hpp"

class QString;

class GameStateManager : public QObject
{
    Q_OBJECT

public:
    static GameStateManager& instance();

    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;

    GameState& getGameState();
    const GameState& getGameState() const;

    void createNewGame();
    void clear();

    bool saveToSlot(const QString& slotName);
    bool loadFromSlot(const QString& slotName);

signals:
    void gameCreated();
    void gameLoaded();
    void gameCleared();

private:
    explicit GameStateManager(QObject* parent = nullptr);

    QString saveDirectory() const;
    bool writeFile(const QString& path, const QByteArray& data);
    QByteArray readFile(const QString& path) const;

private:
    std::unique_ptr<GameState> _gameState;
};