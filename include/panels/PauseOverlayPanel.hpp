#pragma once
#include <QWidget>

class PauseOverlayPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PauseOverlayPanel(QWidget *parent = nullptr);

private:
    void applyStyling();

signals:
    void ResumeClicked();
    void ReturnToMenuClicked();
};