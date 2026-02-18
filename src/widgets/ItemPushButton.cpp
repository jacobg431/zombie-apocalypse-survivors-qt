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
    applyStyling();
}

void ItemPushButton::applyStyling()
{
    setStyleSheet(R"(
        QPushButton {
            background-color: #3a3a3a;
            border: 1px solid #555;
            border-radius: 6px;
            max-height: 96px;
            min-height: 96px;
            max-width: 96px;
            min-width: 96px;
        }

        QPushButton:hover {
            background-color: #505050;
        }

        QPushButton:checked {
            background-color: #007acc;
            border: 2px solid #00bfff;
        }

        QPushButton:disabled {
            background-color: #222;
            color: #666;
            border: 1px solid #444;
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