#include <stdexcept>

#include <QGroupBox>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QFormLayout>
#include <QStringList>

#include "widgets/InfoBox.hpp"
#include "utils.hpp"

InfoBox::InfoBox
(
    const QString& title, 
    const QString& content, 
    QWidget *parent
)
    : QGroupBox(title, parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createContentLabel(content));
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(24, 8, 32, 0);
    this->setFixedHeight(BOX_HEIGHT);
    this->setFixedWidth(BOX_WIDTH);
    
    applyStyling();
}

InfoBox::InfoBox
(
    const QString& title, 
    const QStringList& leftContent, 
    const QStringList& rightContent,
    QWidget *parent
) 
    : QGroupBox(title, parent)
{
    auto *layout = createContentForm(leftContent, rightContent);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(24, 8, 40, 0);
    this->setFixedHeight(BOX_HEIGHT);
    this->setFixedWidth(BOX_WIDTH);

    applyStyling();
}
    

QLabel* InfoBox::createContentLabel(const QString& content)
{
    _contentLabel = new QLabel(this);
    _contentLabel->setWordWrap(true);
    _contentLabel->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
    _contentLabel->setAlignment(Qt::AlignTop);

    return _contentLabel;
}

QFormLayout* InfoBox::createContentForm
(
    const QStringList& leftContent, 
    const QStringList& rightContent
)
{
    auto formLayout = new QFormLayout(this);
    if (leftContent.size() != rightContent.size())
    {
        throw new std::invalid_argument("Column size of form does not match");
    }

    for (int i = 0; i < leftContent.size(); ++i)
    {
        QLabel* leftLabel = new QLabel(leftContent[i]);
        QLabel* rightLabel = new QLabel(rightContent[i]);
        _contentFormMap[leftContent[i]] = rightLabel;
        rightLabel->setAlignment(Qt::AlignRight);

        formLayout->addRow(leftLabel, rightLabel);
    }

    return formLayout;
}

void InfoBox::applyStyling()
{
    setStyleSheet(R"(  
        QGroupBox {
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

        QGroupBox::title {
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch stretch;
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 0px;
            right: 0px;
            width: 100%;

            color: #FF5733;
        }
    )");
}

void InfoBox::setContentLabel(const QString& content)
{
    setGlitchText(_contentLabel, content);
}

void InfoBox::setContentFormRow
(
    const QString& left, 
    const QString& right
)
{
    setGlitchText(_contentFormMap[left], right);
}
