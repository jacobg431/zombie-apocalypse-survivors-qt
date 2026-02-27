#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

#include "managers/GameStateManager.hpp"

GameStateManager& GameStateManager::instance()
{
    static GameStateManager instance;
    return instance;
}

GameStateManager::GameStateManager(QObject* parent)
    : QObject(parent)
{}

GameState& GameStateManager::getGameState()
{
    return *_gameState;
}

const GameState& GameStateManager::getGameState() const
{
    return *_gameState;
}

void GameStateManager::createNewGame()
{
    _gameState = std::make_unique<GameState>();
    emit gameCreated();
}

void GameStateManager::clear()
{
    _gameState.reset();
    emit gameCleared();
}

QString GameStateManager::saveDirectory() const
{
    QString base =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(base);
    if (!dir.exists("saves")) dir.mkdir("saves");

    return base + "/saves/";
}

bool GameStateManager::saveToSlot(const QString& slotName)
{
    if (!_gameState)
        return false;

    QString path = saveDirectory() + slotName + ".json";

    QJsonDocument doc(_gameState->toJson());
    return writeFile(path, doc.toJson(QJsonDocument::Indented));
}

bool GameStateManager::loadFromSlot(const QString& slotName)
{
    QString path = saveDirectory() + slotName + ".json";

    QByteArray data = readFile(path);
    if (data.isEmpty()) return false;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return false;

    auto newState = std::make_unique<GameState>();
    if (!newState->fromJson(doc.object())) return false;

    _gameState = std::move(newState);

    emit gameLoaded();
    return true;
}

bool GameStateManager::writeFile(const QString& path, const QByteArray& data)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) return false;

    file.write(data);
    file.close();
    return true;
}

QByteArray GameStateManager::readFile(const QString& path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return {};

    QByteArray data = file.readAll();
    file.close();
    return data;
}