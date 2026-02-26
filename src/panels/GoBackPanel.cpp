#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>

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
    if (m_button)
    {
        m_button->setText(text);
    }
}

QFrame* GoBackPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("goBackWrapper");

    auto *wrapperLayout = new QHBoxLayout(wrapperFrame);
    wrapperLayout->setContentsMargins(0, 0, 0, 0);
    wrapperLayout->setSpacing(0);

    m_button = new QPushButton(" ⬅ Go Back  ");
    m_button->setObjectName("goBackButton");
    m_button->setMinimumHeight(200);
    m_button->setFixedWidth(240);
    m_button->setCursor(Qt::PointingHandCursor);

    connect(m_button, &QPushButton::clicked, this, &GoBackPanel::GoBackClicked);

    wrapperLayout->addWidget(m_button);
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

        QPushButton#goBackButton {
            background: transparent;
            border: none;
            outline: none;
            font-size: 32px;
            color: #060606;
            border-image: url(:/resources/images/hanging-sign.png) 0 0 0 0 stretch;

            text-align: center bottom;

            padding-bottom: 32px;
            padding-left: 32px;
            padding-right: 32px;

            margin-top: -32px;
            margin-bottom: 32px;
            }

        QPushButton#goBackButton:hover {
            background-color: transparent;
            border-image: url(:/resources/images/hanging-sign-hover.png) 0 0 0 0 stretch;
            }

        QPushButton#goBackButton:pressed {
            background: transparent;
            border-image: url(:/resources/images/hanging-sign-selected.png) 0 0 0 0 stretch;
            color: #7f0000;
            }

    )");
}