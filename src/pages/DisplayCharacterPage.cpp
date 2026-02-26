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
#include "panels/ActionsMenuPanel.hpp"
#include "panels/GoBackPanel.hpp"
#include "managers/RoleManager.hpp"
#include "managers/SessionManager.hpp"
#include "models/PlayerCharacter.hpp"

DisplayCharacterPage::DisplayCharacterPage(QWidget *parent)
    : QWidget(parent)
{    
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(createGoBackPanel(), 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(createWrapper(), 1);

    applyStyling();
}

QWidget* DisplayCharacterPage::createCharacterStatsPanel()
{
    auto playerCharacter = SessionManager::instance().getPlayerCharacter();
    const QStringList attributes = playerCharacter->getAttributesStringList();
    const QString description = playerCharacter->getDescription();
    const QString skills = playerCharacter->getSkills();

    auto *container = new CharacterStatsPanel();
    container->setContent(attributes, description, skills);
    return container;
}

QWidget* DisplayCharacterPage::createCharacterImagePanel()
{
    auto& sessionManager = SessionManager::instance();
    const QString className = sessionManager
        .getPlayerCharacter()->getClassName();

    _characterImagePanel = new CharacterImagePanel(className);
    return _characterImagePanel;
}

QWidget* DisplayCharacterPage::createCharacterActionsPanel()
{
    //_characterActionsPanel = new CharacterActionsPanel();
    _actionsMenuPanel = new ActionsMenuPanel();

    connect(_actionsMenuPanel, &ActionsMenuPanel::GoToShopClicked,
        this, &DisplayCharacterPage::itemsShopClicked);
    connect(_actionsMenuPanel, &ActionsMenuPanel::FightClicked,
        this, &DisplayCharacterPage::fightClicked);
    connect(_actionsMenuPanel, &ActionsMenuPanel::MainMenuClicked,
        this, &DisplayCharacterPage::mainMenuClicked);

    return _actionsMenuPanel;
}

QWidget* DisplayCharacterPage::createInventoryPanel()
{
    auto *container = new ItemsPanel("Inventory");
    container->setMaximumHeight(700);
    return container;
}

QWidget *DisplayCharacterPage::createGoBackPanel()
{
    _goBackPanel = new GoBackPanel(this);
    _goBackPanel->setContentsMargins(0, 0, 0, 0);
    _goBackPanel->setButtonText(" ⬅ To Menu ");

    connect(_goBackPanel, &GoBackPanel::GoBackClicked,
            this, &DisplayCharacterPage::mainMenuClicked);

    return _goBackPanel;
}

QFrame* DisplayCharacterPage::createWrapper()
{
    auto panelsWrapperFrame = new QFrame;
    auto panelsWrapperLayout = new QHBoxLayout(panelsWrapperFrame);
    panelsWrapperLayout->setContentsMargins(20, 20, 20, 20);

    panelsWrapperLayout->addWidget(createCharacterStatsPanel(), 1, Qt::AlignLeft);
    panelsWrapperLayout->addWidget(createCharacterActionsPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel(), 2, Qt::AlignRight);

    return panelsWrapperFrame;
}

void DisplayCharacterPage::applyStyling()
{
    setStyleSheet(R"(
    
    )");
}