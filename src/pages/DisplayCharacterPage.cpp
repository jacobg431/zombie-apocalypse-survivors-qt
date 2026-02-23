#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>
#include <ZasLib/SurvivorAttributes.hpp>

#include "pages/DisplayCharacterPage.hpp"
#include "panels/CharacterStatsPanel.hpp"
#include "panels/CharacterActionsPanel.hpp"
#include "panels/ItemsPanel.hpp"
#include "managers/RoleManager.hpp"

DisplayCharacterPage::DisplayCharacterPage(QWidget *parent)
    : QWidget(parent)
{    
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createWrapper());

    applyStyling();
}

QWidget* DisplayCharacterPage::createCharacterStatsPanel()
{
    auto *container = new CharacterStatsPanel(new CareGiver("Character Name"));
    return container;
}

QWidget* DisplayCharacterPage::createCharacterActionsPanel()
{
    auto *container = new CharacterActionsPanel();
    return container;
}

QWidget* DisplayCharacterPage::createInventoryPanel()
{
    auto *container = new ItemsPanel("Inventory");
    return container;
}

QFrame* DisplayCharacterPage::createWrapper()
{
    auto panelsWrapperFrame = new QFrame;
    auto panelsWrapperLayout = new QHBoxLayout(panelsWrapperFrame);
    panelsWrapperLayout->setContentsMargins(20, 20, 20, 20);

    panelsWrapperLayout->addWidget(createCharacterStatsPanel());
    panelsWrapperLayout->addWidget(createCharacterActionsPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());

    return panelsWrapperFrame;
}

void DisplayCharacterPage::applyStyling()
{
    setStyleSheet(R"(
    
    )");
}