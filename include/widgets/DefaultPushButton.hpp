#pragma once

#include <QString>
#include <QWidget>
#include <QEvent>
#include <QPushButton>

class DefaultPushButton : public QPushButton
{
public:
    DefaultPushButton(const QString& text, QWidget* parent = nullptr);
    void applyStyling();

private:
    bool event(QEvent *event);
};


