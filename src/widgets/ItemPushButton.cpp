#include "widgets/ItemPushButton.hpp"
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QHoverEvent>
#include <QEvent>

ItemPushButton::ItemPushButton(const QString& text, QWidget* parent) 
    : QPushButton(text, parent) 
{
    setCheckable(true);
    setDisabled(true);
    applyStyling();
}

void ItemPushButton::applyStyling()
{
    setStyleSheet(R"(
        QPushButton {
            background-color: #8c000000;
            border: 2px solid #5b000000;
            max-height: 96px;
            min-height: 96px;
            max-width: 96px;
            min-width: 96px;
        }

        QPushButton:hover {
            border-color: #5bff5733;
        }

        QPushButton:checked {
            background-color: #c9ff5733;
        }

        QPushButton:disabled {
            background-color: #8c3e3e3e;
            border-color: #5b3e3e3e;
            color: #929292;
        }
    )");
}

bool ItemPushButton::event(QEvent *event) {
    switch (event->type())
    {
    case QEvent::HoverEnter:
        setCursor(Qt::PointingHandCursor);
        break;
    case QEvent::HoverLeave:
        setCursor(Qt::ArrowCursor);
        break;
    default:
        break;
    }

    return QPushButton::event(event);
}