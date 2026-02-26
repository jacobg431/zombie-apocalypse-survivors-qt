#include <QWidget>

class QFrame;
class QLabel;
class QShowEvent;

class CharacterImagePanel : public QWidget
{
    Q_OBJECT

public:
    CharacterImagePanel(const QString& className, QWidget* parent = nullptr);
    void setImage(const QString& imageUrl);

private:
    QString _className;
    QLabel* _classImageLabel = nullptr;

    QFrame* createWrapper();
    void showEvent(QShowEvent* event) override;
    void swapImageGlitchEffect(const QPixmap &finalPixmap);
    void applyStyling();
};
