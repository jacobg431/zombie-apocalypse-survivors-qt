#include "panels/GoBackPanel.hpp"
#include "widgets/DefaultPushButton.hpp"
#include <QWidget>
#include <QHBoxLayout>

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
    auto *wrapperLayout = new QHBoxLayout(wrapperFrame);
    
    m_button = new DefaultPushButton("Go Back");
    wrapperLayout->addWidget(m_button);
    wrapperLayout->setAlignment(Qt::AlignLeft);

    return wrapperFrame;
}

void GoBackPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame {
            background-color: #2E2E2E;
            margin: 0px;
            padding: 15px;
        }

    )");
}