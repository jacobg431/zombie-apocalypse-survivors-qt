#include <QGroupBox>

class QWidget;
class QString;

class InfoBox : public QGroupBox
{
    Q_OBJECT

public:
    InfoBox(const QString& title, const QString& content, QWidget *parent = nullptr);
    QLabel* getContentLabel();
    void setContentLabel(const QString& content);

private:
    QLabel* createContentLabel(const QString& content);

    void applyStyling();

    const int BOX_HEIGHT = 200;
    const int BOX_WIDTH = 230;
    const int FIXED_COLUMN_HEIGHT = 875;

    QLabel* _contentLabel = nullptr;
};


