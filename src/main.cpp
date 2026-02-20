#include <QApplication>
#include "AppWindow.hpp"
#include <QFontDatabase>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("resources/styles/dark_theme.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Failed to open styling file: " << file.errorString();
        return -1;
    }
    app.setStyleSheet(file.readAll());

    int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/alagard.ttf");

    try
    {
        const auto families = QFontDatabase::applicationFontFamilies(fontId);
        app.setFont(QFont(families.first()));
    }
    catch (...)
    {
        qWarning() << "Failed to load font from resource";
    }

    // --- Main window ---

    AppWindow window;
    window.show();

    return app.exec();
}
