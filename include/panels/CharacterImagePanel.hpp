#include <QWidget>

class QFrame;
class QLabel;

class CharacterImagePanel : public QWidget
{
    Q_OBJECT

public:
    CharacterImagePanel(const QString& className, QWidget* parent = nullptr);
    void setImage(const QString& imageUrl);

private:
    QLabel* _classImageLabel = nullptr;

    QFrame* createWrapper();
    void swapImageGlitchEffect(const QPixmap &finalPixmap);
    void applyStyling();
};
