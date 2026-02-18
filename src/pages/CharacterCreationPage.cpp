#include "pages/CharacterCreationPage.hpp"

#include <ZasLib/Skill.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QLabel>

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    initRoleMap();

    auto *layout = new QHBoxLayout(this);

    // --- Left panel (pick name & class) ---
    auto *left_panel = heroFormComponent();

    // --- Middle panel (class picture) ---
    auto *middle_panel = heroImageComponent();

    // Right panel widgets
    auto *right_panel = HeroDescComponent();

    layout->addLayout(left_panel);
    layout->addLayout(middle_panel);
    layout->addLayout(right_panel);

    connect(classSelect_, &QComboBox::currentTextChanged, this, &CharacterCreationPage::classSelectUpdated);
    classSelectUpdated(classSelect_->currentText());
}

QFormLayout *CharacterCreationPage::heroFormComponent()
{
    nameEdit_ = new QLineEdit(this);
    nameEdit_->setMaximumWidth(250);

    classSelect_ = new QComboBox(this);
    classSelect_->addItems(role_map_.keys());
    classSelect_->setMaximumWidth(250);

    auto *component = new QFormLayout();
    component->setLabelAlignment(Qt::AlignLeft);
    component->setFormAlignment(Qt::AlignTop);
    component->addRow("Hero Name:", nameEdit_);
    component->addRow("Hero Class:", classSelect_);

    return component;
}

QVBoxLayout *CharacterCreationPage::heroImageComponent()
{
    auto *component = new QVBoxLayout();
    component->addWidget(new QLabel("Placeholder image"));
    return component;
}

QVBoxLayout *CharacterCreationPage::HeroDescComponent()
{
    descriptionLabel_ = new QLabel(this);
    descriptionLabel_->setWordWrap(true);
    descriptionLabel_->setFixedWidth(220);

    skillList_ = new QLabel(this);
    skillList_->setWordWrap(true);
    skillList_->setFixedWidth(220);

    auto *attributeForm = new QFormLayout();

    const QStringList attribute_order = {
        "Strength", "Agility", "Endurance", "Intelligence",
        "Leadership", "Trustworthiness", "Courage"};

    for (const QString &attribute : attribute_order)
    {
        attributesMap_[attribute] = new QLabel(this);
        QLabel *label = new QLabel(attribute);
        QLabel *value = attributesMap_[attribute];

        value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        attributeForm->addRow(label, value);
    }

    auto *component = new QVBoxLayout();
    component->addWidget(new QLabel("Hero descriptions:"));
    component->addWidget(descriptionLabel_);
    component->addStretch();
    component->addWidget(new QLabel("Attributes:"));
    component->addLayout(attributeForm);
    component->addStretch();
    component->addWidget(skillList_);
    component->addStretch();

    return component;
}

void CharacterCreationPage::classSelectUpdated(const QString &class_string)
{
    Survivor *class_object = role_map_[class_string];
    auto attributes = class_object->GetAttributes();
    auto skills = class_object->GetSkills();

    descriptionLabel_->setText("[Description of " + class_string + " class goes here]");

    attributesMap_["Strength"]->setText(QString::number(attributes.GetStrength()));
    attributesMap_["Endurance"]->setText(QString::number(attributes.GetEndurance()));
    attributesMap_["Agility"]->setText(QString::number(attributes.GetAgility()));
    attributesMap_["Courage"]->setText(QString::number(attributes.GetCourage()));
    attributesMap_["Intelligence"]->setText(QString::number(attributes.GetIntelligence()));
    attributesMap_["Leadership"]->setText(QString::number(attributes.GetLeadership()));
    attributesMap_["Trustworthiness"]->setText(QString::number(attributes.GetTrustworthiness()));

    QStringList skillLines;
    for (const auto &skill : skills)
    {
        skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));
    }

    bool isJester = dynamic_cast<Jester *>(class_object) != nullptr;
    if (isJester)
    {
        skillLines.fill("???", skillLines.size());

        for (auto *attribute : attributesMap_)
        {
            attribute->setText("???");
        }
    }

    skillList_->setText("Skills:\n• " + skillLines.join("\n• "));
}

void CharacterCreationPage::initRoleMap()
{
    role_map_.insert("Hero", &hero_);
    role_map_.insert("CareGiver", &caregiver_);
    role_map_.insert("Outlaw", &outlaw_);
    role_map_.insert("Jester", &jester_);
}
