#pragma once

#include <QFrame>
#include <QWidget>

class QString;
class QToolButton;

class GoBackPanel : public QWidget
{
    Q_OBJECT
public:
    explicit GoBackPanel(QWidget *parent = nullptr);
    void applyStyling();
    void setButtonText(const QString &text);

signals:
    void GoBackClicked();

private:
    QFrame* createWrapper();
    QToolButton* _button = nullptr;
};