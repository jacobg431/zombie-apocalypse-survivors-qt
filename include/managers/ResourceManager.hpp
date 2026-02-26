#include <QApplication>

class QString;

class ResourceManager : public QObject
{
    Q_OBJECT

public:
    ResourceManager(QApplication* app, QObject* parent = nullptr);

private:
    inline static const QString THEME_FILE = "resources/styles/dark_theme.qss";
    QApplication* _app;
};
