#include <QGroupBox>
#include <QMap>
#include <QStringList>

class QWidget;
class QString;
class QFormLayout;
class QLabel;

class InfoBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit InfoBox
    (
        const QString& title, 
        const QString& content, 
        QWidget *parent = nullptr
    );
    explicit InfoBox
    (
        const QString& title, 
        const QStringList& leftContent, 
        const QStringList& rightContent, 
        QWidget *parent = nullptr
    );

    void setContentLabel(const QString& content);
    void setContentLabelRandom(QStringList& contentLines);

    void setContentFormRow
    (
        const QString& left, 
        const QString& right
    );
    void setContentForm(const QStringList& contentRows);
    void setContentFormRandom(QStringList& contentRows);

private:
    QLabel* createContentLabel(const QString& content);
    QFormLayout* createContentForm
    (
        const QStringList& leftContent, 
        const QStringList& rightContent
    );

    void applyStyling();

    const int BOX_HEIGHT = 200;
    const int BOX_WIDTH = 230;
    const int FIXED_COLUMN_HEIGHT = 875;

    QMap<QString, QLabel *> _contentFormMap;
    QLabel* _contentLabel = nullptr;
};


