#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>
#include <ZasLib/SurvivorAttributes.hpp>

#include "pages/DisplayCharacterPage.hpp"
#include "panels/CharacterStatsPanel.hpp"
#include "panels/CharacterImagePanel.hpp"
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
    auto *container = new CharacterStatsPanel();
    return container;
}

QWidget* DisplayCharacterPage::createCharacterImagePanel()
{
    auto& manager = RoleManager::instance();
    const QString& role = manager.availableRoles()[0];
    _characterImagePanel = new CharacterImagePanel(role);
    return _characterImagePanel;
}

QWidget* DisplayCharacterPage::createCharacterActionsPanel()
{
    _characterActionsPanel = new CharacterActionsPanel();
    
    connect(_characterActionsPanel, &CharacterActionsPanel::itemsShopClicked,
        this, &DisplayCharacterPage::itemsShopClicked);
    connect(_characterActionsPanel, &CharacterActionsPanel::fightClicked,
        this, &DisplayCharacterPage::fightClicked);
    connect(_characterActionsPanel, &CharacterActionsPanel::mainMenuClicked,
        this, &DisplayCharacterPage::mainMenuClicked);

    return _characterActionsPanel;
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
    panelsWrapperLayout->addWidget(createCharacterImagePanel());
    panelsWrapperLayout->addWidget(createCharacterActionsPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());

    return panelsWrapperFrame;
}

void DisplayCharacterPage::applyStyling()
{
    setStyleSheet(R"(
    
    )");
}