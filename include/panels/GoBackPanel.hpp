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

signals:
    void GoBackClicked();

private:
    QFrame* createWrapper();
    QPushButton* m_button = nullptr;
};