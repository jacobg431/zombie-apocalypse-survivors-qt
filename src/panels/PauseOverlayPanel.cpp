#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "panels/PauseOverlayPanel.hpp"
#include "widgets/DefaultPushButton.hpp"

PauseOverlayPanel::PauseOverlayPanel(QWidget *parent) 
    : QWidget(parent)
{
    setObjectName("pauseMenu");
    setAttribute(Qt::WA_StyledBackground, true);
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());

    applyStyling();
    wireConnections();
}

QFrame* PauseOverlayPanel::createWrapper()
{
    auto* wrapperFrame = new QFrame;
    auto* wrapperLayout = new QVBoxLayout(wrapperFrame);

    setWidgets();

    wrapperLayout->addStretch(); 
    wrapperLayout->addWidget(_title);
    wrapperLayout->addWidget(_resumeButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(_saveButton, 0, Qt::AlignCenter);
    wrapperLayout->addWidget(_quitButton, 0, Qt::AlignCenter);
    wrapperLayout->addStretch();
    
    return wrapperFrame;
}

void PauseOverlayPanel::setWidgets()
{
    _title = new QLabel("Game Paused", this);   
    _title->setAlignment(Qt::AlignCenter);

    _resumeButton = new DefaultPushButton("Resume", this);
    _resumeButton->setFixedWidth(200);

    _saveButton = new DefaultPushButton("Save", this);
    _saveButton->setFixedWidth(200);

    _quitButton = new DefaultPushButton("Quit", this);
    _quitButton->setFixedWidth(200);
}

void PauseOverlayPanel::wireConnections()
{
    connect(_resumeButton, &QPushButton::clicked, 
        this, &PauseOverlayPanel::ResumeClicked);
    connect(_saveButton, &QPushButton::clicked, 
        this, &PauseOverlayPanel::ResumeClicked);
    connect(_quitButton, &QPushButton::clicked, 
        this, &PauseOverlayPanel::ReturnToMenuClicked);
}

void PauseOverlayPanel::applyStyling()
{
    setStyleSheet(R"(

        QWidget#pauseMenu { 
            background-color: rgba(0,0,0,200); 
        }
            
    )");
}