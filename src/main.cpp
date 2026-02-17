#include <QApplication>
#include "AppWindow.hpp"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/resources/fonts/DoubleHomicide.ttf");
    try
    {
        const auto families = QFontDatabase::applicationFontFamilies(fontId);
        app.setFont(QFont(families.first()));
    }
    catch (...)
    {
        qWarning() << "Failed to load font from resource";
    }

    AppWindow window;
    window.show();

    return app.exec();
}
