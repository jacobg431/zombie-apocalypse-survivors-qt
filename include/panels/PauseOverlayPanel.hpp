#pragma once

#include <QWidget>

class QFrame;
class QLabel;
class QPushButton;

class PauseOverlayPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PauseOverlayPanel(QWidget *parent = nullptr);

private:
    QLabel* _title = nullptr;
    QPushButton* _resumeButton = nullptr;
    QPushButton* _saveButton = nullptr;
    QPushButton* _quitButton = nullptr;

    QFrame* createWrapper();
    void setWidgets();
    void wireConnections();
    void applyStyling();

signals:
    void resumeClicked();
    void saveClicked();
    void quitClicked();
};