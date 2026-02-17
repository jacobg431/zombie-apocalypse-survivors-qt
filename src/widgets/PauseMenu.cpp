#include "widgets/PauseMenu.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

PauseMenu::PauseMenu(QWidget *parent) : QWidget(parent)
{
    setObjectName("pauseMenu");
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("#pauseMenu { background-color: rgba(0,0,0,160); }");

    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Game Paused", this);   
    title->setAlignment(Qt::AlignCenter);

    auto *resumeButton = new QPushButton("Resume", this);
    auto *returnToMenuButton = new QPushButton("Return to Menu", this);

    layout->addStretch(); 
    layout->addWidget(title);
    layout->addWidget(resumeButton);
    layout->addWidget(returnToMenuButton);
    layout->addStretch();

    connect(resumeButton, &QPushButton::clicked, this, &PauseMenu::ResumeClicked);
    connect(returnToMenuButton, &QPushButton::clicked, this, &PauseMenu::ReturnToMenuClicked);
}