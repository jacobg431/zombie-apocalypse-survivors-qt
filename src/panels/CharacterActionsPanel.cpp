#include <QWidget>
#include <QFrame>
#include <QString>
#include <QVBoxLayout>

#include "panels/CharacterActionsPanel.hpp"

CharacterActionsPanel::CharacterActionsPanel(QWidget *parent) 
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());
    applyStyling();
}

QFrame* CharacterActionsPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("wrapper");
    auto *wrapperLayout = new QVBoxLayout(wrapperFrame);

    return wrapperFrame;
}

void CharacterActionsPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame {
            background-color: #2E2E2E;
            border-radius: 10px;
            padding: 15px;
        }

        QFrame#wrapper {
            border-radius: 10px;
            padding: 15px;
        }

    )");
}