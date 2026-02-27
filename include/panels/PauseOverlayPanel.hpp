#pragma once
#include <QWidget>

class PauseOverlayPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PauseOverlayPanel(QWidget *parent = nullptr);

signals:
    void ResumeClicked();
    void ReturnToMenuClicked();
};