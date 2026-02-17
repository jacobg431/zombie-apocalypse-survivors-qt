#include <QApplication>
#include "AppWindow.hpp"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // --- Global styling ---
    app.setStyleSheet(R"(
        QMainWindow { background-color: #2E2E2E; }

        QLabel { color: white; }

        QPushButton {
            background-color: #444;
            color: white;
            border: 4px solid #666;
            padding: 8px;
            border-radius: 20px;
            qproperty-flat: false;
        }

        QPushButton:hover {
            background-color: #555;
        }

        QPushButton:pressed {
            background-color: #333;
        }
    )");

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
