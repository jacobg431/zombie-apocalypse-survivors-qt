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

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>

#include "pages/CharacterCreationPage.hpp"
#include "managers/RoleManager.hpp"
#include "utils.hpp"

int MAX_COLUMN_WIDTH = 400;
int FIXED_COLUMN_HEIGHT = 875;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) 
    : QWidget(parent)
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

    connect(_classSelect, &QComboBox::currentTextChanged, this, 
        &CharacterCreationPage::classSelectUpdated);

    classSelectUpdated(_classSelect->currentText());
}

QWidget *CharacterCreationPage::createSurvivorForm()
{

    const int INPUT_WIDTH = 160;

    _nameEdit = new QLineEdit(this);
    _nameEdit->setObjectName("survivorNameEdit");
    _nameEdit->setFixedWidth(INPUT_WIDTH);

    _classSelect = new QComboBox(this);
    _classSelect->setObjectName("survivorClassSelect");
    _classSelect->addItems(_role_map.keys());
    _classSelect->setFixedWidth(INPUT_WIDTH);

    _submitButton = new QPushButton("Create Character", this);
    _submitButton->setObjectName("submitButton");
    _submitButton->setCursor(Qt::PointingHandCursor);
    _submitButton->setFixedWidth(INPUT_WIDTH);

    auto *layout = new QFormLayout();
    layout->setContentsMargins(16, 16, 32, 16);
    layout->setLabelAlignment(Qt::AlignHCenter);
    layout->setFormAlignment(Qt::AlignHCenter);
    layout->addRow(_nameEdit);
    layout->addRow(_classSelect);
    layout->addRow(_submitButton);

    auto *component = new QGroupBox();
    component->setLayout(layout);
    component->setObjectName("survivorInfoBox");
    component->setTitle("Name and Class");

    return component;
}

QWidget *CharacterCreationPage::createSurvivorImage()
{
    _classImageLabel = new QLabel(this);
    _classImageLabel->setScaledContents(true);
    _classImageLabel->setAlignment(Qt::AlignCenter);
    _classImageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto *component = new QWidget(this);
    component->setLayout(new QVBoxLayout());
    component->layout()->addWidget(_classImageLabel);

    return component;
}

QWidget *CharacterCreationPage::createSurvivorDesc()
{
    _descriptionLabel = new QLabel(this);
    _descriptionLabel->setWordWrap(true);
    _descriptionLabel->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
    _descriptionLabel->setAlignment(Qt::AlignTop);

    _skillList = new QLabel(this);
    _skillList->setWordWrap(true);
    _skillList->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
    _skillList->setAlignment(Qt::AlignTop);

    auto *attributeForm = new QFormLayout();

    const QStringList attribute_order = {
        "Strength", "Agility", "Endurance", "Intelligence",
        "Leadership", "Trustworthiness", "Courage"};

    for (const QString &attribute : attribute_order)
    {
        _attributesMap[attribute] = new QLabel(this);
        QLabel *label = new QLabel(attribute);
        QLabel *value = _attributesMap[attribute];

        value->setAlignment(Qt::AlignRight);
        attributeForm->addRow(label, value);
    }

    const int BOX_HEIGHT = 200;
    const int BOX_WIDTH = 230;

    auto *descBox = new QGroupBox("Class description");
    auto *descLay = new QVBoxLayout(descBox);
    descLay->addWidget(_descriptionLabel);
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
    skillsLay->addWidget(_skillList);
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
    Survivor *class_object = _role_map[class_string];
    auto attributes = class_object->GetAttributes();
    auto skills = class_object->GetSkills();

    QStringList skillLines;
    for (const auto &skill : skills)
    {
        skillLines << QString::fromStdString(SkillUtils::SkillToString(skill));
    }

    setGlitchText(
        _attributesMap["Strength"], 
        QString::number(attributes.GetStrength())
    );
    setGlitchText(
        _attributesMap["Endurance"], 
        QString::number(attributes.GetEndurance())
    );
    setGlitchText(
        _attributesMap["Agility"], 
        QString::number(attributes.GetAgility())
    );
    setGlitchText(
        _attributesMap["Courage"], 
        QString::number(attributes.GetCourage())
    );
    setGlitchText(
        _attributesMap["Intelligence"], 
        QString::number(attributes.GetIntelligence())
    );
    setGlitchText(
        _attributesMap["Leadership"], 
        QString::number(attributes.GetLeadership())
    );
    setGlitchText(
        _attributesMap["Trustworthiness"], 
        QString::number(attributes.GetTrustworthiness())
    );

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

        for (auto *attribute : _attributesMap)
        {
            setGlitchText(
                attribute, 
                attributeSymbols[rng() % attributeSymbols.size()]
            );
        }
    }

    setGlitchText(
        _descriptionLabel, QString::fromStdString(class_object->GetRoleDescription())
    );
    setGlitchText(
        _skillList, "Skills:\n• " + skillLines.join("\n• ")
    );

    const int IMAGE_HEIGHT = FIXED_COLUMN_HEIGHT;
    const int IMAGE_WIDTH = IMAGE_HEIGHT / 1.25;

    QPixmap pixmap(":/resources/images/" + class_string.toLower() + "-fried.png");
    glitchSwapPixmap(
        pixmap.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );
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
            _classImageLabel->setPixmap(makeGlitchFrame(base));
            (*i)++;
        } else {
            _classImageLabel->setPixmap(finalPixmap);
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
