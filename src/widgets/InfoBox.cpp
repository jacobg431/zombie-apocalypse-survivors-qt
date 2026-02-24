#include <QGroupBox>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "widgets/InfoBox.hpp"
#include "utils.hpp"

InfoBox::InfoBox(const QString& title, const QString& content, QWidget *parent)
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

QLabel* InfoBox::createContentLabel(const QString& content)
{
    _contentLabel = new QLabel(this);
    _contentLabel->setWordWrap(true);
    _contentLabel->setMinimumHeight(FIXED_COLUMN_HEIGHT / 4);
    _contentLabel->setAlignment(Qt::AlignTop);

    return _contentLabel;
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

QLabel* InfoBox::getContentLabel()
{
    return _contentLabel;
}

void InfoBox::setContentLabel(const QString& content)
{
    setGlitchText(_contentLabel, content);
}
