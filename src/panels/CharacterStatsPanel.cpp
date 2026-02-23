#include <QWidget>
#include <QFrame>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>

#include <ZasLib/Skill.hpp>

#include "panels/CharacterStatsPanel.hpp"
#include "managers/RoleManager.hpp"

CharacterStatsPanel::CharacterStatsPanel(Survivor *characterClass, QWidget *parent)
    : _characterClass(characterClass), QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());

    applyStyling();
}

QWidget* CharacterStatsPanel::createTitleLabel()
{
    // add this later: new QLabel(_characterClass->getName());
    auto *label = new QLabel("Character Name");
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("panelTitle");
    return label;
}

QFrame* CharacterStatsPanel::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("wrapper");
    auto wrapperLayout = new QVBoxLayout(wrapperFrame);
    wrapperLayout->addWidget(createTitleLabel());

    return wrapperFrame;
}

void CharacterStatsPanel::applyStyling()
{
    setStyleSheet(R"(

        QFrame {
            background-color: #2E2E2E;
            border-radius: 10px;
            padding: 15px;
        }

        QFrame#innerWrapper {
            border-radius: 10px;
            padding: 15px;
        }

    )");
}