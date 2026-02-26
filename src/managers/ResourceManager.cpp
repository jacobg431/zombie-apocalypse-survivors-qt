#include <stdexcept>
#include <string>

#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QList>
#include <QString>

#include "managers/ResourceManager.hpp"

ResourceManager::ResourceManager(QApplication* app, QObject* parent)
    : _app(app), QObject(parent)
{
    QFile file(THEME_FILE);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::string msg = "Failed to open styling file: " + 
            file.errorString().toStdString();
        throw new std::runtime_error(msg);
    }
    _app->setStyleSheet(file.readAll());

    QList<int> fontIdList = {
        QFontDatabase::addApplicationFont(":/resources/fonts/IBM-EGA-8x14.ttf"),
        QFontDatabase::addApplicationFont(":/resources/fonts/alagard.ttf"),
    };
    
    for (int fontId : fontIdList) {
        try
        {
            const auto families = QFontDatabase::applicationFontFamilies(fontId);
            _app->setFont(QFont(families.first()));
        }
        catch (...)
        {
            qWarning() << "Failed to load font from resource";
        }
    }
}