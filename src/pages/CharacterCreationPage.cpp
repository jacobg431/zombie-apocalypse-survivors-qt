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
#include "widgets/CreateCharacterFormBox.hpp"
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
    leftPanel->layout()->addWidget(createSurvivorDesc());

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

    _descriptionInfoBox = new InfoBox("Class Description", "Some description");
    _attributesInfoBox = new InfoBox("Class Attributes", ATTRIBUTES, ATTRIBUTES_DEFAULT_VALUES);
    _skillsInfoBox = new InfoBox("Class Skills", "Some skills");

    auto *infoBoxWrapper = new QWidget();
    auto *infoBoxWrapperLayout = new QVBoxLayout(infoBoxWrapper);
    infoBoxWrapperLayout->addWidget(_descriptionInfoBox);
    infoBoxWrapperLayout->addWidget(_attributesInfoBox);
    infoBoxWrapperLayout->addWidget(_skillsInfoBox);

    return infoBoxWrapper;
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

        _attributesInfoBox->setContentFormRandom(attributeSymbols);
        _skillsInfoBox->setContentLabelRandom(skillSymbols);
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

        _attributesInfoBox->setContentForm(attributeValues);

        _descriptionInfoBox->setContentLabel(QString::fromStdString(class_object->GetRoleDescription()));
        _skillsInfoBox->setContentLabel(skillLines.join("\n"));
    }
    
    const int IMAGE_HEIGHT = FIXED_COLUMN_HEIGHT;
    const int IMAGE_WIDTH = IMAGE_HEIGHT / 1.25;

    QPixmap pixmap(":/resources/images/" + className.toLower() + "-fried.png");
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
    )");
    
    style()->unpolish(this);
    style()->polish(this);
    update();
}
