#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

GoBackPanel::GoBackPanel(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QHBoxLayout(this);
    layout->addWidget(createWrapper());
    layout->setContentsMargins(0, 0, 0, 0);
    applyStyling();
}

QFrame* GoBackPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("goBackWrapper");
    auto *wrapperLayout = new QHBoxLayout(wrapperFrame);
    
    m_button = new DefaultPushButton("Go Back");
    connect(m_button, &QPushButton::clicked, this, &GoBackPanel::GoBackClicked);

    wrapperLayout->addWidget(m_button);
    wrapperLayout->setAlignment(Qt::AlignLeft);

    return wrapperFrame;
}

void GoBackPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame#goBackWrapper {
            background-color: #2E2E2E;
            border-radius: 10px;
            margin: 0px;
            padding: 15px;
        }

    )");
}