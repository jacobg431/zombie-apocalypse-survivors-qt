#include "pages/CharacterCreationPage.hpp"

#include <ZasLib/Skill.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QString>
#include <QLabel>
#include <QGroupBox>

int MAX_COL_WIDTH = 300;
QString TITLE_STYLE = "font-size: 32px; color: #FF5733;";

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    initRoleMap();

    auto *title_wrapper = new QVBoxLayout(this);

    auto *titleLabel = new QLabel("Create Your Survivor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageTitle");
    titleLabel->setStyleSheet(TITLE_STYLE);
    title_wrapper->addWidget(titleLabel);

    auto *layout = new QHBoxLayout();
    title_wrapper->addLayout(layout);

    // --- Character form and class description ---
    auto *left_layout = new QVBoxLayout();
    left_layout->setContentsMargins(12, 12, 12, 12);
    left_layout->setSpacing(12);

    auto *formWidget = new QWidget(this);
    formWidget->setLayout(heroFormComponent());

    auto *descWidget = new QWidget(this);
    descWidget->setLayout(HeroDescComponent());

    left_layout->addWidget(formWidget);
    left_layout->addWidget(descWidget);

    auto *left_panel = new QWidget(this);
    left_panel->setLayout(left_layout);

    // --- Character image ---
    auto *right_panel = heroImageComponent();

    // --- Layout & connections ---
    layout->addStretch();
    layout->addWidget(left_panel, 0, Qt::AlignCenter);
    layout->addLayout(right_panel, 0);
    layout->addStretch();

    connect(classSelect_, &QComboBox::currentTextChanged, this, &CharacterCreationPage::classSelectUpdated);
    classSelectUpdated(classSelect_->currentText());
}

QFormLayout *CharacterCreationPage::heroFormComponent()
{
    nameEdit_ = new QLineEdit(this);
    nameEdit_->setMaximumWidth(MAX_COL_WIDTH);

    classSelect_ = new QComboBox(this);
    classSelect_->addItems(role_map_.keys());
    classSelect_->setMaximumWidth(MAX_COL_WIDTH);

    auto *component = new QFormLayout();
    component->setLabelAlignment(Qt::AlignLeft);
    component->setFormAlignment(Qt::AlignTop);

    component->addRow(new QLabel("Choose a name:"));
    component->addRow(nameEdit_);

    component->addRow(new QLabel("Choose a class:"));
    component->addRow(classSelect_);

    return component;
}

QVBoxLayout *CharacterCreationPage::heroImageComponent()
{
    classImageLabel_ = new QLabel(this);
    classImageLabel_->setScaledContents(true);
    classImageLabel_->setAlignment(Qt::AlignCenter);
    classImageLabel_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto *component = new QVBoxLayout();
    component->addStretch();
    component->addSpacing(60);
    component->addWidget(classImageLabel_, 0, Qt::AlignHCenter);
    component->addStretch();

    return component;
}

QVBoxLayout *CharacterCreationPage::HeroDescComponent()
{
    descriptionLabel_ = new QLabel(this);
    descriptionLabel_->setWordWrap(true);
    descriptionLabel_->setAlignment(Qt::AlignTop);

    skillList_ = new QLabel(this);
    skillList_->setWordWrap(true);
    skillList_->setAlignment(Qt::AlignTop);
    
    auto *attributeForm = new QFormLayout();

    const QStringList attribute_order = {
        "Strength", "Agility", "Endurance", "Intelligence",
        "Leadership", "Trustworthiness", "Courage"};

    for (const QString &attribute : attribute_order)
    {
        attributesMap_[attribute] = new QLabel(this);
        QLabel *label = new QLabel(attribute);
        QLabel *value = attributesMap_[attribute];

        value->setAlignment(Qt::AlignRight);
        attributeForm->addRow(label, value);
    }

    const int MIN_BOX_HEIGHT = 200;
    const int MIN_BOX_WIDTH = 230;

    auto *descBox = new QGroupBox("Class description");
    auto *descLay = new QVBoxLayout(descBox);
    descLay->addWidget(descriptionLabel_);
    descBox->setMinimumHeight(MIN_BOX_HEIGHT);
    descBox->setMinimumWidth(MIN_BOX_WIDTH);
    descBox->setObjectName("woodenBox");

    auto *attrBox = new QGroupBox("Class Attributes");
    auto *attrLay = new QVBoxLayout(attrBox);
    attrLay->addLayout(attributeForm);
    attrBox->setObjectName("woodenBox");

    auto *skillsBox = new QGroupBox("Class Skills");
    auto *skillsLay = new QVBoxLayout(skillsBox);
    skillsLay->addWidget(skillList_);
    skillsBox->setMinimumHeight(MIN_BOX_HEIGHT);
    skillsBox->setObjectName("woodenBox");

    auto *component = new QVBoxLayout();
    component->addWidget(descBox);
    component->addWidget(attrBox);
    component->addWidget(skillsBox);
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


    const int IMAGE_WIDTH = 640;
    const int IMAGE_HEIGHT = 640*1.25;
    QPixmap pixmap(":/resources/images/" + class_string.toLower() + "-fried.png");
    classImageLabel_->setPixmap(pixmap.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CharacterCreationPage::initRoleMap()
{
    role_map_.insert("Hero", &hero_);
    role_map_.insert("CareGiver", &caregiver_);
    role_map_.insert("Outlaw", &outlaw_);
    role_map_.insert("Jester", &jester_);
}
