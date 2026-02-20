#include "pages/CharacterCreationPage.hpp"
#include "utils.hpp"

#include <ZasLib/Skill.hpp>

#include <algorithm>
#include <random>

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
#include <QRandomGenerator>
#include <QPainter>

int MAX_COL_WIDTH = 300;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    initRoleMap();

    auto *title_wrapper = new QVBoxLayout(this);

    auto *titleLabel = new QLabel("Create Your Survivor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageTitle");
    titleLabel->setFixedWidth(2 * MAX_COL_WIDTH);
    title_wrapper->addWidget(titleLabel, 0, Qt::AlignHCenter);

    auto *layout = new QHBoxLayout();
    title_wrapper->addLayout(layout);

    // --- Character form and class description ---
    auto *leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(12, 12, 12, 12);
    leftLayout->setSpacing(12);

    auto *formWidget = new QWidget(this);
    formWidget->setLayout(heroFormComponent());

    auto *descWidget = new QWidget(this);
    descWidget->setLayout(HeroDescComponent());

    leftLayout->addWidget(formWidget);
    leftLayout->addWidget(descWidget);

    auto *leftPanel = new QWidget(this);
    leftPanel->setLayout(leftLayout);

    // --- Character image ---
    auto *rightPanel = heroImageComponent();

    // --- Layout & connections ---
    layout->addStretch();
    layout->addWidget(leftPanel, 0, Qt::AlignCenter);
    layout->addLayout(rightPanel, 0);
    layout->addStretch();

    connect(classSelect_, &QComboBox::currentTextChanged, this, &CharacterCreationPage::classSelectUpdated);
    classSelectUpdated(classSelect_->currentText());
    applyStyling();
}

QFormLayout *CharacterCreationPage::heroFormComponent()
{
    nameEdit_ = new QLineEdit(this);
    nameEdit_->setObjectName("survivorNameEdit");
    nameEdit_->setMaximumWidth(MAX_COL_WIDTH);

    classSelect_ = new QComboBox(this);
    classSelect_->setObjectName("survivorClassSelect");
    classSelect_->addItems(role_map_.keys());
    classSelect_->setMaximumWidth(MAX_COL_WIDTH);

    submitButton_ = new QPushButton("Create Character", this);
    submitButton_->setMaximumWidth(MAX_COL_WIDTH);

    auto *component = new QFormLayout();
    component->setLabelAlignment(Qt::AlignLeft);
    component->setFormAlignment(Qt::AlignTop);

    component->addRow(new QLabel("Choose a name & class:"));
    component->addRow(nameEdit_);
    component->addRow(classSelect_);
    component->addRow(submitButton_);

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
    descriptionLabel_->setMinimumHeight(parentWidget()->height() / 3);
    descriptionLabel_->setAlignment(Qt::AlignTop);

    skillList_ = new QLabel(this);
    skillList_->setWordWrap(true);
    skillList_->setMinimumHeight(parentWidget()->height() / 3);
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

    const int BOX_HEIGHT = 200;
    const int BOX_WIDTH = 230;

    auto *descBox = new QGroupBox("Class description");
    auto *descLay = new QVBoxLayout(descBox);
    descLay->addWidget(descriptionLabel_);
    descLay->setAlignment(Qt::AlignTop);
    descLay->setContentsMargins(24, 8, 32, 0);
    descBox->setFixedHeight(BOX_HEIGHT);
    descBox->setFixedWidth(BOX_WIDTH);
    descBox->setObjectName("survivorInfoBox");

    auto *attrBox = new QGroupBox("Class Attributes");
    auto *attrLay = new QVBoxLayout(attrBox);
    attrLay->addLayout(attributeForm);
    descLay->setAlignment(Qt::AlignTop);
    attrLay->setContentsMargins(24, 8, 40, 0);
    attrBox->setObjectName("survivorInfoBox");
    attrBox->setFixedHeight(BOX_HEIGHT);
    attrBox->setFixedWidth(BOX_WIDTH);

    auto *skillsBox = new QGroupBox("Class Skills");
    auto *skillsLay = new QVBoxLayout(skillsBox);
    skillsLay->addWidget(skillList_);
    skillsLay->setAlignment(Qt::AlignTop);
    skillsLay->setContentsMargins(24, 8, 30, 0);
    skillsBox->setFixedHeight(BOX_HEIGHT);
    skillsBox->setFixedWidth(BOX_WIDTH);
    skillsBox->setObjectName("survivorInfoBox");

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

    QStringList skillLines;
    for (const auto &skill : skills)
    {
        skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));
    }

    setGlitchText(attributesMap_["Strength"], QString::number(attributes.GetStrength()));
    setGlitchText(attributesMap_["Endurance"], QString::number(attributes.GetEndurance()));
    setGlitchText(attributesMap_["Agility"], QString::number(attributes.GetAgility()));
    setGlitchText(attributesMap_["Courage"], QString::number(attributes.GetCourage()));
    setGlitchText(attributesMap_["Intelligence"], QString::number(attributes.GetIntelligence()));
    setGlitchText(attributesMap_["Leadership"], QString::number(attributes.GetLeadership()));
    setGlitchText(attributesMap_["Trustworthiness"], QString::number(attributes.GetTrustworthiness()));

    bool isJester = dynamic_cast<Jester *>(class_object) != nullptr;
    if (isJester)
    {
        QStringList skillSymbols = {"🂡", "🂥", "🂧", "🂪", "🂫", "🂬"};
        QStringList attributeSymbols = {"♠", "♥", "♦", "♣"};

        std::mt19937 rng(QRandomGenerator::global()->generate());

        std::shuffle(skillSymbols.begin(), skillSymbols.end(), rng);
        std::shuffle(attributeSymbols.begin(), attributeSymbols.end(), rng);

        skillLines.clear();
        skillLines << skillSymbols.join("");

        for (auto *attribute : attributesMap_)
        {
            setGlitchText(attribute, attributeSymbols[rng() % attributeSymbols.size()]);
        }
    }

    setGlitchText(descriptionLabel_, QString::fromStdString(class_object->GetRoleDescription()));
    setGlitchText(skillList_, "Skills:\n• " + skillLines.join("\n• "));

    const int IMAGE_WIDTH = 650;
    const int IMAGE_HEIGHT = 650 * 1.25;
    QPixmap pixmap(":/resources/images/" + class_string.toLower() + "-fried.png");
    glitchSwapPixmap(pixmap.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CharacterCreationPage::initRoleMap()
{
    role_map_.insert("Hero", &hero_);
    role_map_.insert("CareGiver", &caregiver_);
    role_map_.insert("Outlaw", &outlaw_);
    role_map_.insert("Jester", &jester_);
}

void CharacterCreationPage::glitchSwapPixmap(const QPixmap &finalPixmap)
{
    const int frames = 8;
    const int intervalMs = 16;

    QPixmap base = finalPixmap;

    int *i = new int(0);
    auto *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this, timer, base, finalPixmap, i]() mutable
            {
        if (*i < 8) {
            classImageLabel_->setPixmap(makeGlitchFrame(base));
            (*i)++;
        } else {
            classImageLabel_->setPixmap(finalPixmap);
            timer->stop();
            timer->deleteLater();
            delete i;
        } });

    timer->start(intervalMs);
}

void CharacterCreationPage::applyStyling()
{
    setStyleSheet(R"(
        #pageTitle {
            font-size: 32px;
            color: #FF5733;
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch;
            padding: 4px 16px;
        }

        QLineEdit#survivorNameEdit {
            background-color: #444;
            color: white;
            border: 2px solid #666;
            padding: 4px;
            border-radius: 6px;
        }

        QComboBox#survivorClassSelect {
            background-color: #444;
            color: white;
            border: 2px solid #666;
            padding: 4px;
            border-radius: 6px;
        }

        QComboBox#survivorClassSelect::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 28px;
            border-left: 2px solid #666;
            border-top-right-radius: 6px;
            border-bottom-right-radius: 6px;
            background: #444;
        }

        QComboBox#survivorClassSelect::down-arrow {
            width: 12px;
            height: 12px;
        }

        QComboBox#survivorClassSelect QAbstractItemView {
            background-color: #444;
            color: white;
            border: 2px solid #666;
            selection-background-color: #555;
            selection-color: white;
            border-radius: 6px;
            outline: 0;
            background-clip: border;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item {
            background: #444;     /* force item background */
            padding: 6px 10px;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item:selected {
            background: #555;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item:hover {
            background: #555;
        }

        QGroupBox {
            border: 2px solid #222;
            border-radius: 6px;

            margin-top: 20px;
            padding: 14px;
        }
    
        QGroupBox#survivorInfoBox {
            background-color: transparent;
            border-image: url(:/resources/images/wooden-sign-square-fried.png);
            border: none;

            margin: -8px;

            margin-top: -4px;
            margin-bottom: -8px;
            margin-left: -16px;
            margin-right: -16px;

            padding-left: 32px;
            padding-top: 32px;
            }

        QGroupBox#survivorInfoBox::title {
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch stretch;
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 0px;
            right: 0px;
            width: 100%;

            color: #FF5733;
        }
    )");
    style()->unpolish(this);
    style()->polish(this);
    update();
}
