#include <QWidget>
#include <QFrame>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>

#include <ZasLib/Skill.hpp>
#include "panels/CharacterStatsPanel.hpp"
#include "managers/RoleManager.hpp"

CharacterStatsPanel::CharacterStatsPanel(const QString& title, const Survivor *characterClass, QWidget *parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());    

    applyStyling();
}

QWdiget* CharacterStatsPanel::createTitleLabel(const QString& title)
{
    auto *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("panelTitle");
    return label;
}

QFrame* CharacterStatsPanel::createWrapper(const QString& title)
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("wrapper");
    auto wrapperLayout = new QVBoxLayout(this);
    wrapperLayout->createTitleLabel(title);

    return wrapperFrame;
}

void CharacterStatsPanel::applyStyling()
{
    setStyleSheet(R"(

    )");
}