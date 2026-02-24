#include "widgets/HoverButton.hpp"

#include <QEnterEvent>
#include <QEvent>
#include <QString>

HoverButton::HoverButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    normalText = "  " + text;
    hoverText = "> " + text;

    setText(normalText);
    setCursor(Qt::PointingHandCursor);
}

void HoverButton::enterEvent(QEnterEvent *event)
{
    setText(hoverText);
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event)
{
    setText(normalText);
    QPushButton::leaveEvent(event);
}