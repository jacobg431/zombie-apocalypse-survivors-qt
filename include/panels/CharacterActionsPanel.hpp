#include <QWidget>

class QFrame;
class QString;
class QPushButton;

class CharacterActionsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterActionsPanel(QWidget *parent = nullptr);

private:
    QWidget* createTitleLabel();
    QFrame* createButtonWrapper();
    QFrame* createWrapper();
    void applyStyling();

    QPushButton* _itemsShopButton;
    QPushButton* _fightButton;

};
