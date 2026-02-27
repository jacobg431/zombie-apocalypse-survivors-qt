#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QFrame>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>

#include "pages/CharacterCreationPage.hpp"
#include "panels/CharacterStatsPanel.hpp"
#include "panels/CharacterImagePanel.hpp"
#include "widgets/CreateCharacterFormBox.hpp"
#include "widgets/InfoBox.hpp"
#include "managers/RoleManager.hpp"
#include "managers/GameStateManager.hpp"
#include "models/PlayerCharacter.hpp"
#include "utils.hpp"

int MAX_COLUMN_WIDTH = 400;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) 
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createWrapper());

    applyStyling();
    updateSelectedClass();
}

QWidget* CharacterCreationPage::createTitleLabel()
{
    auto *titleLabel = new QLabel("Create Your Survivor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageTitle");
    titleLabel->setFixedWidth(2 * MAX_COLUMN_WIDTH);

    return titleLabel;
}

QWidget* CharacterCreationPage::createLeftPanel()
{
    auto *leftPanel = new QWidget();
    leftPanel->setLayout(new QVBoxLayout());
    leftPanel->layout()->addWidget(createSurvivorForm());
    leftPanel->layout()->addWidget(createCharacterStatsPanel());

    return leftPanel;
}

QWidget *CharacterCreationPage::createSurvivorForm()
{
    auto& roleManager = RoleManager::instance();
    _formBox = new CreateCharacterFormBox(roleManager.availableRoles());

    connect(_formBox, &CreateCharacterFormBox::classSelectUpdated,
        this, &CharacterCreationPage::updateSelectedClass);
    connect(_formBox, &CreateCharacterFormBox::characterCreated,
        this, &CharacterCreationPage::onCharacterCreated);

    return _formBox;
}

QWidget *CharacterCreationPage::createSurvivorImage()
{
    _characterImagePanel = new CharacterImagePanel(_formBox->getCurrentSelectorText());
    return _characterImagePanel;
}

QWidget *CharacterCreationPage::createCharacterStatsPanel()
{
    _characterStatsPanel = new CharacterStatsPanel();
    return _characterStatsPanel;
}

QFrame* CharacterCreationPage::createInnerWrapper()
{
    auto *innerWrapperFrame = new QFrame;
    innerWrapperFrame->setObjectName("innerWrapper");

    auto *innerWrapperLayout = new QHBoxLayout(innerWrapperFrame);
    innerWrapperLayout->addStretch();
    innerWrapperLayout->addWidget(createLeftPanel(), 0, Qt::AlignCenter);
    innerWrapperLayout->addWidget(createSurvivorImage(), 0, Qt::AlignCenter);
    innerWrapperLayout->addStretch();

    return innerWrapperFrame;
}

QFrame* CharacterCreationPage::createWrapper()
{
    auto *wrapperFrame = new QFrame;
    wrapperFrame->setObjectName("wrapper");

    auto *wrapperLayout = new QVBoxLayout(wrapperFrame);
    wrapperLayout->addWidget(createTitleLabel(), 0, Qt::AlignHCenter);
    wrapperLayout->addWidget(createInnerWrapper());

    return wrapperFrame;
}

QStringList CharacterCreationPage::skillVectorToStringList(std::vector<Skill> skillVector)
{
    QStringList skillLines;
    for (const auto &skill : skillVector)
    {
        skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));
    }
    return skillLines;
}

void CharacterCreationPage::updateSelectedClass()
{
    const QString &className = _formBox->getCurrentSelectorText();
    auto& roleManager = RoleManager::instance();
    const Survivor *classObject = roleManager.getRole(className);
    
    bool isJester = dynamic_cast<const Jester *>(classObject) != nullptr;
    if (isJester)
    {
        QStringList skillSymbols = {"🂡", "🂥", "🂧", "🂪", "🂫", "🂬"};
        QStringList attributeSymbols = {"♠", "♥", "♦", "♣"};

        _characterStatsPanel->setContentRandom(attributeSymbols, skillSymbols);
    }
    else {
        auto attributes = classObject->GetAttributes();
        auto skills = skillVectorToStringList(classObject->GetSkills());

        const QStringList attributeValues = {
            QString::number(attributes.GetStrength()),
            QString::number(attributes.GetEndurance()),
            QString::number(attributes.GetAgility()),
            QString::number(attributes.GetCourage()),
            QString::number(attributes.GetIntelligence()),
            QString::number(attributes.GetLeadership()),
            QString::number(attributes.GetTrustworthiness())
        };

        _characterStatsPanel->setContent
        (
            attributeValues,
            QString::fromStdString(classObject->GetRoleDescription()),
            skills.join("\n")
        );
    }
    
    _characterImagePanel->setImage(className);

}

void CharacterCreationPage::onCharacterCreated()
{
    const QString &className = _formBox->getCurrentSelectorText();
    auto& roleManager = RoleManager::instance();
    const Survivor *classObject = roleManager.getRole(className);
    auto& playerCharacter = GameStateManager::instance()
        .getGameState()
        .getPlayer();
    
    playerCharacter.setDescription
    (
        QString::fromStdString(classObject->GetRoleDescription())
    );
    playerCharacter.setSkills(skillVectorToStringList(classObject->GetSkills()));
    playerCharacter.setStrength(classObject->GetAttributes().GetStrength());
    playerCharacter.setEndurance(classObject->GetAttributes().GetEndurance());
    playerCharacter.setAgility(classObject->GetAttributes().GetAgility());
    playerCharacter.setCourage(classObject->GetAttributes().GetCourage());
    playerCharacter.setIntelligence(classObject->GetAttributes().GetIntelligence());
    playerCharacter.setLeadership(classObject->GetAttributes().GetLeadership());
    playerCharacter.setTrustWorthiness(classObject->GetAttributes().GetTrustworthiness());

    emit characterCreated();
}

void CharacterCreationPage::applyStyling()
{
    setStyleSheet(R"(
        #pageTitle {
            font-size: 32px;
            color: #FF5733;
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch;
        }
    )");
}
