#pragma once

class QPixmap;
class QLabel;
class QString;

QPixmap makeGlitchFrame(const QPixmap &src);

QString glitchify(const QString &target, double progress);

void setGlitchText(QLabel *label, const QString &finalText, int durationMs = 200, int intervalMs = 20);
