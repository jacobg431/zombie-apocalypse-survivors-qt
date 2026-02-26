#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QList>

#include "AppWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("resources/styles/dark_theme.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Failed to open styling file: " << file.errorString();
        return -1;
    }
    app.setStyleSheet(file.readAll());

    QList<int> fontIdList = {
        QFontDatabase::addApplicationFont(":/resources/fonts/IBM-EGA-8x14.ttf"),
        QFontDatabase::addApplicationFont(":/resources/fonts/alagard.ttf"),
    };
    
    for (int fontId : fontIdList) {
        try
        {
            const auto families = QFontDatabase::applicationFontFamilies(fontId);
            app.setFont(QFont(families.first()));
        }
        catch (...)
        {
            qWarning() << "Failed to load font from resource";
        }
    }

    // --- Main window ---

    AppWindow window;
    window.show();
    window.setWindowState(Qt::WindowFullScreen);

    return app.exec();
}
