#pragma once

#include <QFrame>
#include <QWidget>
#include <QString>
#include <QPushButton>

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
    QPushButton* m_button = nullptr;
};