#include "widgets/DefaultPushButton.hpp"
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QHoverEvent>
#include <QEvent>

DefaultPushButton::DefaultPushButton(const QString& text, QWidget* parent) 
    : QPushButton(text, parent) 
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    applyStyling();
}

void DefaultPushButton::applyStyling()
{
    setStyleSheet(R"(
        QPushButton {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;
            padding: 6px 12px;
            text-align: center;
            font-size: 32px;
        }

        QPushButton:hover {
            background-color: #c91e1e1e;
            border-color: #5bff5733;
        }
        
        QPushButton:pressed {
            background-color: #c9ff5733;
            padding: 4px 10px;
        }

        QPushButton:disabled {
            background-color: #222;
            color: #666;
            border: 1px solid #444;
        }
    )");
}

bool DefaultPushButton::event(QEvent *event) {
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