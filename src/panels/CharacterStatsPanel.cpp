#include <QWidget>
#include <QFrame>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

#include <ZasLib/Skill.hpp>

#include "panels/CharacterStatsPanel.hpp"
#include "widgets/InfoBox.hpp"
#include "managers/RoleManager.hpp"

CharacterStatsPanel::CharacterStatsPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());

    applyStyling();
}

QFrame* CharacterStatsPanel::createWrapper()
{   
    _descriptionInfoBox = new InfoBox("Class Description", "Some description");
    _attributesInfoBox = new InfoBox("Class Attributes", ATTRIBUTES, ATTRIBUTES_DEFAULT_VALUES);
    _skillsInfoBox = new InfoBox("Class Skills", "Some skills");

    auto *wrapperFrame = new QFrame();
    wrapperFrame->setObjectName("wrapper");
    auto *wrapperLayout = new QVBoxLayout(wrapperFrame);
    wrapperLayout->addWidget(_descriptionInfoBox);
    wrapperLayout->addWidget(_attributesInfoBox);
    wrapperLayout->addWidget(_skillsInfoBox);

    return wrapperFrame;
}

void CharacterStatsPanel::setContent
(
    const QStringList& attributeContent,
    const QString& descriptionContent,
    const QString& skillContent
)
{
    _attributesInfoBox->setContentForm(attributeContent);
    _descriptionInfoBox->setContentLabel(descriptionContent);
    _skillsInfoBox->setContentLabel(skillContent);
}

void CharacterStatsPanel::setContentRandom
(
    QStringList& attributeContent, 
    QStringList& skillContent
)
{
    _attributesInfoBox->setContentFormRandom(attributeContent);
    _skillsInfoBox->setContentLabelRandom(skillContent);
}

void CharacterStatsPanel::applyStyling()
{
    setStyleSheet(R"(

    )");
}