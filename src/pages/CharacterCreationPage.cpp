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
#include <QFrame>

#include <ZasLib/Roles.hpp>
#include <ZasLib/Skill.hpp>

#include "pages/CharacterCreationPage.hpp"
#include "widgets/InfoBox.hpp"
#include "managers/RoleManager.hpp"
#include "utils.hpp"

int MAX_COLUMN_WIDTH = 400;
int FIXED_COLUMN_HEIGHT = 875;

CharacterCreationPage::CharacterCreationPage(QWidget *parent) 
    : QWidget(parent)
{
    initRoleMap();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createWrapper());

    applyStyling();

    connect(_classSelect, &QComboBox::currentTextChanged, this, 
        &CharacterCreationPage::classSelectUpdated);

    classSelectUpdated(_classSelect->currentText());
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
    leftPanel->layout()->addWidget(createSurvivorDesc());

    return leftPanel;
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
    connect(_submitButton, &QPushButton::clicked, 
        this, &CharacterCreationPage::characterCreated);

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

    _descriptionInfoBox = new InfoBox("Class Description", "Some description");
    _attributesInfoBox = new InfoBox("Class Attributes", "Some attributes");
    _skillsInfoBox = new InfoBox("Class Skills", "Some skills");

    auto *component = new QWidget();
    component->setLayout(new QVBoxLayout());
    component->layout()->addWidget(_descriptionInfoBox);
    component->layout()->addWidget(_attributesInfoBox);
    component->layout()->addWidget(_skillsInfoBox);

    return component;
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

    _descriptionInfoBox->setContentLabel(QString::fromStdString(class_object->GetRoleDescription()));
    _skillsInfoBox->setContentLabel("Skills:\n• " + skillLines.join("\n• "));

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
    )");
    
    style()->unpolish(this);
    style()->polish(this);
    update();
}
