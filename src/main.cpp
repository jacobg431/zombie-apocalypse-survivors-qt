#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QList>

#include "AppWindow.hpp"
#include "managers/ResourceManager.hpp"
#include "managers/SessionManager.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ResourceManager resourceManager(&app);

    // --- Main window ---

    AppWindow window;
    window.show();
    window.setWindowState(Qt::WindowFullScreen);

    return app.exec();
}
