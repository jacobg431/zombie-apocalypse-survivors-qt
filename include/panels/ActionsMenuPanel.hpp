#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QLabel;
class QTimer;
class QMovie;

class ActionsMenuPanel : public QWidget
{
    Q_OBJECT

public:
    ActionsMenuPanel(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QWidget* createTextPanel();
    QWidget* createOptionsPanel();
    QFrame *createMenuWrapper();

    void startTypingText(QLabel *label, const QString &text, int msPerChar);

    void applyStyling();

    QTimer *typeTimer = nullptr;
    QLabel *titleLabel = nullptr;
    int typeIndex = 0;

    QFrame *menuWrapper = nullptr;
    QMovie *backgroundGif = nullptr;

signals:
    void goToShopClicked();
    void fightClicked();
    void exploreClicked();
};