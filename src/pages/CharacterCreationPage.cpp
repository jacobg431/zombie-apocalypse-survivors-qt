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

int MAX_COLUMN_WIDTH = 400;
int FIXED_COLUMN_HEIGHT = 875;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    initRoleMap();
    applyStyling();

    // --- Title ---
    auto *titleLabel = new QLabel("Create Your Survivor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageTitle");
    titleLabel->setFixedWidth(2 * MAX_COLUMN_WIDTH);

    // --- Character form and description ---
    auto *leftPanel = new QWidget();
    leftPanel->setLayout(new QVBoxLayout());
    leftPanel->layout()->addWidget(createSurvivorForm());
    leftPanel->layout()->addWidget(createSurvivorDesc());

    // --- Class image ---
    auto *rightPanel = createSurvivorImage();

    // --- Layout & connections ---
    auto *uiLayout = new QHBoxLayout();
    uiLayout->addStretch();
    uiLayout->addWidget(leftPanel, 0, Qt::AlignCenter);
    uiLayout->addWidget(rightPanel, 0, Qt::AlignCenter);
    uiLayout->addStretch();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addLayout(uiLayout);

    connect(classSelect_, &QComboBox::currentTextChanged, this, &CharacterCreationPage::classSelectUpdated);

    classSelectUpdated(classSelect_->currentText());
}

QWidget *CharacterCreationPage::createSurvivorForm()
{

    const int INPUT_WIDTH = 160;

    nameEdit_ = new QLineEdit(this);
    nameEdit_->setObjectName("survivorNameEdit");
    nameEdit_->setFixedWidth(INPUT_WIDTH);

    classSelect_ = new QComboBox(this);
    classSelect_->setObjectName("survivorClassSelect");
    classSelect_->addItems(role_map_.keys());
    classSelect_->setFixedWidth(INPUT_WIDTH);

    submitButton_ = new QPushButton("Create Character", this);
    submitButton_->setObjectName("submitButton");
    submitButton_->setCursor(Qt::PointingHandCursor);
    submitButton_->setFixedWidth(INPUT_WIDTH);

    auto *layout = new QFormLayout();
    layout->setContentsMargins(16, 16, 32, 16);
    layout->setLabelAlignment(Qt::AlignHCenter);
    layout->setFormAlignment(Qt::AlignHCenter);
    layout->addRow(nameEdit_);
    layout->addRow(classSelect_);
    layout->addRow(submitButton_);

    auto *component = new QGroupBox();
    component->setLayout(layout);
    component->setObjectName("survivorInfoBox");
    component->setTitle("Name and Class");

    connect(submitButton_, &QPushButton::clicked,
            this, &CharacterCreationPage::characterCreated);

    return component;
}

QWidget *CharacterCreationPage::createSurvivorImage()
{
    classImageLabel_ = new QLabel(this);
    classImageLabel_->setScaledContents(true);
    classImageLabel_->setAlignment(Qt::AlignCenter);
    classImageLabel_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto *component = new QWidget(this);
    component->setLayout(new QVBoxLayout());
    component->layout()->addWidget(classImageLabel_);

    return component;
}

QWidget *CharacterCreationPage::createSurvivorDesc()
{
    descriptionLabel_ = new QLabel(this);
    descriptionLabel_->setWordWrap(true);
    descriptionLabel_->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
    descriptionLabel_->setAlignment(Qt::AlignTop);

    skillList_ = new QLabel(this);
    skillList_->setWordWrap(true);
    skillList_->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
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

    auto *component = new QWidget();
    component->setLayout(new QVBoxLayout());
    component->layout()->addWidget(descBox);
    component->layout()->addWidget(attrBox);
    component->layout()->addWidget(skillsBox);

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

    const int IMAGE_HEIGHT = FIXED_COLUMN_HEIGHT;
    const int IMAGE_WIDTH = IMAGE_HEIGHT / 1.25;

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
        }

        QLineEdit#survivorNameEdit {
            background-color: #c91e1e1e;
            color: white;
            padding-left: 12px;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;
            height: 30px; 
        }

        QLineEdit#survivorNameEdit:focus {
            border-color: #c9ff5733;
        }

        QComboBox#survivorClassSelect {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;

            height: 30px; 
            padding-left: 12px;
            
        }

        QComboBox#survivorClassSelect::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 28px;
            border-left: 2px solid #c91e1e1e;
            border-top-right-radius: 6px;
            border-bottom-right-radius: 6px;
            background: #c91e1e1e;
            padding: 6px 6px;
        }

        QComboBox#survivorClassSelect::down-arrow {
            image: url(:/resources/images/chevron-down.png);
        }

        QComboBox#survivorClassSelect QAbstractItemView {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c9ff5733;
            selection-background-color: #c91e1e1e;
            selection-color: white;
            background-clip: border;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item {
            background: #c91e1e1e;
            padding: 6px 12px;
            margin: 2px;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item:selected {
            background: #c91e1e1e;
        }

        QComboBox#survivorClassSelect QAbstractItemView::item:hover {
            background: #c91e1e1e;
        }

        QPushButton#submitButton {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;
            padding: 6px 12px;
            text-align: center;
            margin-top: 24px;
            margin-bottom: 12px;
            }

        QPushButton#submitButton:hover {
            background-color: #c91e1e1e;
            border-color: #5bff5733;
        }

        QPushButton#submitButton:pressed {
            background-color: #c9ff5733;
            padding: 4px 10px;
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
