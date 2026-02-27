#pragma once
#include <QWidget>

class PauseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PauseMenu(QWidget *parent = nullptr);

signals:
    void ResumeClicked();
    void ReturnToMenuClicked();
};