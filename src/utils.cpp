#include "utils.hpp"
#include <QTimer>
#include <QRandomGenerator>
#include <QPainter>
#include <QLabel>
#include <QElapsedTimer>
#include <QString>

QPixmap makeGlitchFrame(const QPixmap &src)
{
    if (src.isNull())
        return src;

    QPixmap out(src.size());
    out.fill(Qt::transparent);

    QPainter painter(&out);
    painter.drawPixmap(0, 0, src);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);

    const int imageHeight = src.height();
    const int imageWidth = src.width();

    const int minSlices = 15;
    const int maxSlices = 30;

    const int minSliceThickness = 6;
    const int maxSliceThickness = 12;

    const int maxHorizontalShift = 25;

    // --- Random grayscale horizontal slices ---
    int slices = QRandomGenerator::global()->bounded(minSlices, maxSlices + 1);
    for (int i = 0; i < slices; ++i)
    {
        int randomHeight = QRandomGenerator::global()->bounded(0, imageHeight);
        int sliceThickness = QRandomGenerator::global()->bounded(minSliceThickness, maxSliceThickness + 1);
        int horizontalShift = QRandomGenerator::global()->bounded(-maxHorizontalShift, maxHorizontalShift + 1);

        QRect sliceRect(0, randomHeight, imageWidth, qMin(sliceThickness, imageHeight - randomHeight));
        painter.drawPixmap(horizontalShift, randomHeight, src, sliceRect.x(), sliceRect.y(), sliceRect.width(), sliceRect.height());
    }

    // --- Random red/blue horizontal lines ---
    int lines = QRandomGenerator::global()->bounded(3, 8);
    for (int i = 0; i < lines; ++i)
    {
        bool red = (QRandomGenerator::global()->bounded(0, 2) == 0);
        QColor randomColor = red ? QColor(255, 60, 60) : QColor(60, 170, 255);

        int randomHeight = QRandomGenerator::global()->bounded(0, imageHeight);
        int sliceThickness = QRandomGenerator::global()->bounded(1, 4);
        int horizontalOffset = QRandomGenerator::global()->bounded(-30, 31);

        painter.setOpacity(0.35);
        painter.fillRect(horizontalOffset, randomHeight, imageWidth, sliceThickness, randomColor);
    }

    return out;
}

QString glitchify(const QString &target, double progress)
{
    static const QString glyphs = "!@#$%^&*()-_=+[]{};:,.<>/?|\\~`█▓▒░≋≣≢≠∿∆∑√πΩµ¢£¥÷×";

    QString outString = target;
    auto *rng = QRandomGenerator::global();

    // The earlier the progress, the more characters we corrupt.
    // Example: progress 0.2 -> ~80% corrupted, progress 0.8 -> ~20% corrupted.
    double corruptRate = 1.0 - progress;
    for (int i = 0; i < outString.size(); ++i)
    {
        QChar character = outString[i];

        // Keep line breaks and bullet points stable
        if (character == '\n' || character == QChar(0x2022) || character == '\t')
            continue;

        // Don't glitch spaces too aggressively
        if (character.isSpace())
        {
            if (rng->bounded(1000) < int(120 * corruptRate))
                outString[i] = glyphs[rng->bounded(glyphs.size())];
            continue;
        }

        if (rng->generateDouble() < corruptRate)
        {
            // replace with random glyph sometimes, or random letter/number
            if (rng->bounded(100) < 70)
            {
                outString[i] = glyphs[rng->bounded(glyphs.size())];
            }
            // random alnum
            int r = rng->bounded(36);
            outString[i] = (r < 10) ? QChar('0' + r) : QChar('A' + (r - 10));
        }
    }

    return outString;
}

void setGlitchText(QLabel *label, const QString &finalText, int durationMs, int intervalMs)
{
    if (!label)
        return;

    // Keep any existing timer from stacking (optional)
    // If you want multiple labels simultaneously, this is fine as-is.

    auto *timer = new QTimer(label);
    auto *elapsed = new QElapsedTimer();
    elapsed->start();

    const QString startText = label->text();

    // If start is empty, use final length for nicer "boot-up" effect
    QString base = startText.isEmpty() ? finalText : startText;

    QObject::connect(timer, &QTimer::timeout, label,
                     [label, timer, elapsed, finalText, durationMs, base]() mutable
                     {
                         double t = double(elapsed->elapsed()) / double(durationMs);
                         if (t >= 1.0)
                         {
                             label->setText(finalText);
                             timer->stop();
                             timer->deleteLater();
                             delete elapsed;
                             return;
                         }

                         if (base.size() != finalText.size())
                         {
                             base = base.leftJustified(finalText.size(), ' ');
                         }

                         label->setText(glitchify(finalText, t));
                     });

    timer->start(intervalMs);
}