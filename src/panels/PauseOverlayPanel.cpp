#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "panels/PauseOverlayPanel.hpp"
#include "widgets/DefaultPushButton.hpp"

PauseOverlayPanel::PauseOverlayPanel(QWidget *parent) : QWidget(parent)
{
    setObjectName("pauseMenu");
    setAttribute(Qt::WA_StyledBackground, true);

    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Game Paused", this);   
    title->setAlignment(Qt::AlignCenter);

    auto *resumeButton = new DefaultPushButton("Resume", this);
    resumeButton->setFixedWidth(200);

    auto *returnToMenuButton = new DefaultPushButton("Quit", this);
    returnToMenuButton->setFixedWidth(200);

    layout->addStretch(); 
    layout->addWidget(title);
    layout->addWidget(resumeButton, 0, Qt::AlignCenter);
    layout->addWidget(returnToMenuButton, 0, Qt::AlignCenter);
    layout->addStretch();

    applyStyling();

    connect(resumeButton, &QPushButton::clicked, this, &PauseOverlayPanel::ResumeClicked);
    connect(returnToMenuButton, &QPushButton::clicked, this, &PauseOverlayPanel::ReturnToMenuClicked);
}

void PauseOverlayPanel::applyStyling()
{
    setStyleSheet(R"(

        QWidget#pauseMenu { 
            background-color: rgba(0,0,0,200); 
        }
            
    )");
}