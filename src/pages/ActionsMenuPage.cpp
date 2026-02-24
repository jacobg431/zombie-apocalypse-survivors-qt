#include "pages/ActionsMenuPage.hpp"
#include "widgets/HoverButton.hpp"

#include <QVBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QRandomGenerator>
#include <QMovie>
#include <QPainter>

ActionsMenuPage::ActionsMenuPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createMenuWrapper(), 0, Qt::AlignCenter);

    backgroundGif = new QMovie(":/resources/images/computer.gif");
    backgroundGif->setCacheMode(QMovie::CacheAll);
    backgroundGif->start();
    menuWrapper->installEventFilter(this);
    connect(backgroundGif, &QMovie::frameChanged, menuWrapper, [this]()
            { menuWrapper->update(); });

    applyStyling();
}

QFrame *ActionsMenuPage::createMenuWrapper()
{
    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuLayout->setContentsMargins(210, 120, 50, 300);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->addWidget(createTextPanel());
    menuLayout->addSpacing(50);
    menuLayout->addWidget(createOptionsPanel());

    menuWrapper = new QFrame;
    menuWrapper->setLayout(menuLayout);
    menuWrapper->setObjectName("menuWrapper");
    menuWrapper->setFixedSize(1000, 800);

    return menuWrapper;
}

QWidget *ActionsMenuPage::createTextPanel()
{
    auto *textPanel = new QWidget;

    titleLabel = new QLabel("", textPanel);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumWidth(600);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setObjectName("menuTitle");

    auto *textLayout = new QVBoxLayout(textPanel);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    return textPanel;
}

QWidget *ActionsMenuPage::createOptionsPanel()
{
    auto *optionsPanel = new QWidget;

    auto *optionsLayout = new QVBoxLayout(optionsPanel);
    optionsLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    auto *exploreButton = new HoverButton("Explore", optionsPanel);
    auto *restButton = new HoverButton("Rest", optionsPanel);
    auto *shopButton = new HoverButton("Go to Shop", optionsPanel);

    optionsLayout->addWidget(exploreButton, 0, Qt::AlignLeft | Qt::AlignTop);
    optionsLayout->addWidget(restButton, 0, Qt::AlignLeft | Qt::AlignTop);
    optionsLayout->addWidget(shopButton, 0, Qt::AlignLeft | Qt::AlignTop);
    optionsLayout->addStretch();

    connect(shopButton, &QPushButton::clicked,
            this, &ActionsMenuPage::GoToShopClicked);

    return optionsPanel;
}

void ActionsMenuPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (titleLabel)
    {
        startTypingText(titleLabel, "What would you like to do?", 30);
    }
}

bool ActionsMenuPage::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == menuWrapper && event->type() == QEvent::Paint)
    {
        QPainter painter(menuWrapper);

        if (backgroundGif)
        {
            QPixmap frame = backgroundGif->currentPixmap();
            painter.drawPixmap(menuWrapper->rect(), frame);
        }

        return false;
    }

    return QWidget::eventFilter(obj, event);
}

void ActionsMenuPage::startTypingText(QLabel *label, const QString &text, int msPerChar)
{
    if (!label)
    {
        return;
    }

    if (typeTimer)
    {
        typeTimer->stop();
        typeTimer->deleteLater();
        typeTimer = nullptr;
    }

    QString targetText = text;
    typeIndex = 0;
    label->setText("");

    typeTimer = new QTimer(this);
    connect(typeTimer, &QTimer::timeout, this, [this, label, targetText]()
            {
                if (typeIndex >= targetText.size())
                {
                    label->setText(targetText);
                    typeTimer->stop();
                    return;
                }
                label->setText(targetText.left(++typeIndex) + "▌"); });

    typeTimer->start(msPerChar);
}

void ActionsMenuPage::applyStyling()
{
    setStyleSheet(R"(
        QWidget {
            background: transparent;
        }

        #menuWrapper {
            border-radius: 15px;
            border-image: url(:/resources/images/computer.gif);
            font-family: 'AcPlus IBM EGA 8x14';
        }

        #menuTitle {
            color: #6eFF5733;
            font-size: 24px;
            font-weight: bold;
            font-family: 'AcPlus IBM EGA 8x14';
        }

        QPushButton {
            background: transparent;
            color: #6eFF5733;
            border: none;
            padding: 10px 20px;
            border-radius: 10px;
            font-size: 18px;
            font-family: 'AcPlus IBM EGA 8x14';
        }

    )");
}