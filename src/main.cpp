#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QList>

#include "AppWindow.hpp"
#include "managers/ResourceManager.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ResourceManager resourceManager(&app);

    AppWindow window;
    window.show();
    window.setWindowState(Qt::WindowFullScreen);

    return app.exec();
}
