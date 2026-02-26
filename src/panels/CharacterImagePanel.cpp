#include <QWidget>
#include <QString>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

#include "panels/CharacterImagePanel.hpp"
#include "utils.hpp"

CharacterImagePanel::CharacterImagePanel(const QString& className, QWidget* parent)
    : _className(className), QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(createWrapper());
    applyStyling();
}

QFrame* CharacterImagePanel::createWrapper()
{
    _classImageLabel = new QLabel(this);
    _classImageLabel->setScaledContents(true);
    _classImageLabel->setAlignment(Qt::AlignCenter);
    _classImageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto *wrapperFrame = new QFrame;
    auto *wrapperLayout = new QVBoxLayout(wrapperFrame);
    wrapperLayout->addWidget(_classImageLabel);

    return wrapperFrame;
}

void CharacterImagePanel::setImage(const QString& className)
{
    const int IMAGE_HEIGHT = 875;
    const int IMAGE_WIDTH = IMAGE_HEIGHT / 1.25;

    QPixmap pixmap(":/resources/images/" + className.toLower() + "-fried.png");
    swapImageGlitchEffect
    (
        pixmap.scaled
        (
            IMAGE_WIDTH, 
            IMAGE_HEIGHT, 
            Qt::KeepAspectRatio, 
            Qt::SmoothTransformation
        )
    );
}

void CharacterImagePanel::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    setImage(_className);
}

void CharacterImagePanel::swapImageGlitchEffect(const QPixmap &finalPixmap)
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

void CharacterImagePanel::applyStyling()
{
    setStyleSheet(R"(

    )");
}