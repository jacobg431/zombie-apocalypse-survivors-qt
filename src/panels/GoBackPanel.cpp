#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>
#include <QPainter>
#include <QStyle>
#include <QFont>

GoBackPanel::GoBackPanel(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(createWrapper(), 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addStretch();
    
    applyStyling();
}

void GoBackPanel::setButtonText(const QString &text)
{
    if (_button)
    {
        _button->setText(text);
    }
}

QFrame* GoBackPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("goBackWrapper");

    auto *wrapperLayout = new QHBoxLayout(wrapperFrame);
    wrapperLayout->setContentsMargins(0, 0, 0, 0);
    wrapperLayout->setSpacing(0);

    _button = new QToolButton();
    _button->setText("Go Back");
    _button->setObjectName("goBackButton");
    _button->setMinimumHeight(200);
    _button->setFixedWidth(240);
    _button->setCursor(Qt::PointingHandCursor);

    _button->setIcon(QIcon(":/resources/icons/arrow-big-left.svg"));
    _button->setIconSize(QSize(24, 24));
    _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QFont font = _button->font();
    font.setPointSize(24);
    _button->setFont(font);

    connect(_button, &QToolButton::clicked, this, &GoBackPanel::GoBackClicked);

    wrapperLayout->addWidget(_button);
    wrapperLayout->setAlignment(Qt::AlignLeft);

    return wrapperFrame;
}

void GoBackPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame#goBackWrapper {
            background: transparent;
            margin-left: 32px;
        }

        QToolButton#goBackButton {
            background: transparent;
            border: none;
            outline: none;
            color: #060606;
            border-image: url(:/resources/images/hanging-sign.png) 0 0 0 0 stretch;

            text-align: center bottom;

            padding-top: 96px;
            padding-left: 44px;
            padding-right: 32px;

            margin-top: -32px;
            margin-bottom: 32px;
        }

        QToolButton#goBackButton:hover {
            background-color: transparent;
            border-image: url(:/resources/images/hanging-sign-hover.png) 0 0 0 0 stretch;
        }

        QToolButton#goBackButton:pressed {
            background: transparent;
            border-image: url(:/resources/images/hanging-sign-selected.png) 0 0 0 0 stretch;
            color: #7f0000;
        }

    )");
}