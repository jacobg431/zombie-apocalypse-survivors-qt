#include "utils.hpp"
#include <QTimer>
#include <QRandomGenerator>
#include <QPainter>

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
