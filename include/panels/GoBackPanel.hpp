#pragma once

#include <QFrame>
#include <QWidget>
#include <QString>
#include <QPushButton>

class GoBackPanel : public QWidget
{
public:
    explicit GoBackPanel(QWidget *parent = nullptr);
    void applyStyling();

private:
    QFrame* createWrapper();
    QPushButton* m_button = nullptr;
};