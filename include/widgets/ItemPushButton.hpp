#include <QString>
#include <QWidget>
#include <QEvent>

class ItemPushButton
{
public:
    ItemPushButton(const QString& text, QWidget* parent = nullptr);
    void applyStyling();

private:
    bool event(QEvent *event);
};


