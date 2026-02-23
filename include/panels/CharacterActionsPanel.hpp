#include <QWidget>

class QFrame;
class QString;

class CharacterActionsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterActionsPanel(QWidget *parent = nullptr);

private:
    QFrame* createWrapper();
    void applyStyling();

};
