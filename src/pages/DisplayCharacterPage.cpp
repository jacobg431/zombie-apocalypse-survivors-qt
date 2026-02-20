#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>
#include <ZasLib/SurvivorAttributes.hpp>

#include "pages/DisplayCharacterPage.hpp"
#include "panels/ItemsPanel.hpp"
#include "managers/RoleManager.hpp"

DisplayCharacterPage::DisplayCharacterPage(QWidget *parent)
    : QWidget(parent)
{    
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createWrapper());

    applyStyling();
}

QWidget* DisplayCharacterPage::createSurvivorImagePanel()
{
    return new QWidget();
}

QWidget* DisplayCharacterPage::createSurviorDescriptionPanel()
{
    return new QWidget();
}

QWidget* DisplayCharacterPage::createInventoryPanel()
{
    auto *container = new ItemsPanel("Inventory", "Sell");
    return container;
}

QFrame* DisplayCharacterPage::createWrapper()
{
    auto panelsWrapperFrame = new QFrame;
    auto panelsWrapperLayout = new QHBoxLayout(panelsWrapperFrame);
    panelsWrapperLayout->setContentsMargins(20, 20, 20, 20);

    panelsWrapperLayout->addWidget(createSurvivorImagePanel());
    panelsWrapperLayout->addWidget(createSurviorDescriptionPanel());
    panelsWrapperLayout->addWidget(createInventoryPanel());

    return panelsWrapperFrame;
}

void DisplayCharacterPage::applyStyling()
{
    setStyleSheet(R"(
    
    )");
}