#include "pages/CharacterCreationPage.hpp"

#include <ZasLib/Skill.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QMap>
#include <QString>
#include <QListWidget>

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    initRoleMap();

    auto *layout = new QHBoxLayout(this);

    // --- Left panel (pick name & class) ---
    auto *name_select = new QLineEdit(this);
    name_select->setMaximumWidth(250);

    auto *class_select = new QComboBox(this);
    class_select->addItems(role_map_.keys());
    class_select->setMaximumWidth(250);

    auto *hero_form = new QFormLayout();
    hero_form->setLabelAlignment(Qt::AlignLeft);
    hero_form->setFormAlignment(Qt::AlignTop);
    hero_form->addRow("Hero Name:", name_select);
    hero_form->addRow("Hero Class:", class_select);

    // --- Middle panel (class picture) ---
    auto *middle_panel = new QVBoxLayout();
    middle_panel->addWidget(new QLabel("Placeholder image"));

    // Right panel widgets
    auto *right_panel = HeroDescComponent();

    layout->addLayout(hero_form);
    layout->addLayout(middle_panel);
    layout->addLayout(right_panel);

    connect(class_select, &QComboBox::currentTextChanged, this, &CharacterCreationPage::classSelectUpdated);
    emit classSelectUpdated(class_select->currentText());
}

auto CharacterCreationPage::heroFormComponent()
{
}

auto CharacterCreationPage::heroImageComponent()
{
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
