#pragma once

#include <QString>
#include <QWidget>
#include <QEvent>
#include <QPushButton>

class ItemPushButton : public QPushButton
{
public:
    ItemPushButton(const QString& text, QWidget* parent = nullptr);
    void applyStyling();

private:
    bool event(QEvent *event);
};


