#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QString>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QFrame>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>

#include "pages/CharacterCreationPage.hpp"
#include "panels/CharacterStatsPanel.hpp"
#include "panels/CharacterImagePanel.hpp"
#include "widgets/CreateCharacterFormBox.hpp"
#include "widgets/InfoBox.hpp"
#include "managers/RoleManager.hpp"
#include "utils.hpp"

int MAX_COLUMN_WIDTH = 400;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) 
    : QWidget(parent)
{
    initRoleMap();

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
    _formBox = new CreateCharacterFormBox(_role_map.keys());

    connect(_formBox, &CreateCharacterFormBox::classSelectUpdated,
        this, &CharacterCreationPage::updateSelectedClass);
    connect(_formBox, &CreateCharacterFormBox::characterCreated,
        this, &CharacterCreationPage::characterCreated);

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

void CharacterCreationPage::updateSelectedClass()
{
    const QString &className = _formBox->getCurrentSelectorText();
    Survivor *class_object = _role_map[className];
    
    bool isJester = dynamic_cast<Jester *>(class_object) != nullptr;
    if (isJester)
    {
        QStringList skillSymbols = {"🂡", "🂥", "🂧", "🂪", "🂫", "🂬"};
        QStringList attributeSymbols = {"♠", "♥", "♦", "♣"};

        _characterStatsPanel->setContentRandom(attributeSymbols, skillSymbols);
    }
    else {
        auto attributes = class_object->GetAttributes();
        auto skills = class_object->GetSkills();

        QStringList skillLines;
        for (const auto &skill : skills)
        {
            skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));
        }

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
            QString::fromStdString(class_object->GetRoleDescription()),
            skillLines.join("\n")
        );
    }
    
    _characterImagePanel->setImage(className);

}

void CharacterCreationPage::initRoleMap()
{
    auto& manager = RoleManager::instance();

    for (const QString& roleName : manager.availableRoles())
    {
        _role_map.insert(
            roleName,
            const_cast<Survivor*>(
                manager.getRole(roleName)));
    }
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
    
    style()->unpolish(this);
    style()->polish(this);
    update();
}
