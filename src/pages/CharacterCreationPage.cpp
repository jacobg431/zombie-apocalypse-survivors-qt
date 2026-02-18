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
    auto *descriptionLabel_ = new QLabel(this);
    descriptionLabel_->setWordWrap(true);
    descriptionLabel_->setFixedWidth(220);
    
    auto *skillList_ = new QLabel(this);
    skillList_->setWordWrap(true);
    skillList_->setFixedWidth(220);
    
    // store attribute value labels so we can update them
    attributesMap_["Strength"]        = new QLabel(this);
    attributesMap_["Endurance"]       = new QLabel(this);
    attributesMap_["Agility"]         = new QLabel(this);
    attributesMap_["Courage"]         = new QLabel(this);
    attributesMap_["Intelligence"]    = new QLabel(this);
    attributesMap_["Leadership"]      = new QLabel(this);
    attributesMap_["Trustworthiness"] = new QLabel(this);

    auto addRowTo = [&](QFormLayout *form, const QString &label, QLabel *value)
    {
        value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        form->addRow(label, value);
    };

    auto *attrForm = new QFormLayout();

    // Fixed order (looks nicer than map order)
    const QStringList attribute_order = {
        "Strength", "Endurance", "Agility", "Courage",
        "Intelligence", "Leadership", "Trustworthiness"};

    for (const QString &attribute : attribute_order)
        addRowTo(attrForm, attribute, attributesMap_[attribute]);

    auto updateForClass = [=](const QString &class_string)
    {
        Survivor *class_object = role_map_.value(class_string, nullptr);
        if (!class_object)
            return;
            
        auto attributes = class_object->GetAttributes();
        auto skills = class_object->GetSkills();
        QStringList skillLines;

        descriptionLabel_->setText("[Description of " + class_string + " class goes here]");

        if (class_string == "Jester")
        {
            for (const auto &label : attributesMap_)
                label->setText("???");
            for (const auto &skill : skills)
                skillLines << "???";
            skillList_->setText("Skills:\n• " + skillLines.join("\n• "));
            return;
        }


        attributesMap_["Strength"]->setText(QString::number(attributes.GetStrength()));
        attributesMap_["Endurance"]->setText(QString::number(attributes.GetEndurance()));
        attributesMap_["Agility"]->setText(QString::number(attributes.GetAgility()));
        attributesMap_["Courage"]->setText(QString::number(attributes.GetCourage()));
        attributesMap_["Intelligence"]->setText(QString::number(attributes.GetIntelligence()));
        attributesMap_["Leadership"]->setText(QString::number(attributes.GetLeadership()));
        attributesMap_["Trustworthiness"]->setText(QString::number(attributes.GetTrustworthiness()));

        for (const auto &skill : skills)
            skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));

        skillList_->setText("Skills:\n• " + skillLines.join("\n• "));

        
    };
    
    // --- Right panel (class descriptions) ---

    auto *right_panel = new QVBoxLayout();

    right_panel->addWidget(new QLabel("Hero descriptions:"));
    right_panel->addWidget(descriptionLabel_);
    right_panel->addStretch();
    right_panel->addWidget(new QLabel("Attributes:"));
    right_panel->addLayout(attrForm);
    right_panel->addStretch();
    right_panel->addWidget(skillList_);
    right_panel->addStretch();

    layout->addLayout(hero_form);
    layout->addLayout(middle_panel);
    layout->addLayout(right_panel);

    connect(class_select, &QComboBox::currentTextChanged, this, updateForClass);
    updateForClass(class_select->currentText());
}

void CharacterCreationPage::initRoleMap()
{
    role_map_.insert("Hero", &hero_);
    role_map_.insert("CareGiver", &caregiver_);
    role_map_.insert("Outlaw", &outlaw_);
    role_map_.insert("Jester", &jester_);
}
