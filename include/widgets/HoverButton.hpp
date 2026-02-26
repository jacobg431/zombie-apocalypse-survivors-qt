#pragma once

#include <QPushButton>

class QEnterEvent;
class QEvent;
class QString;

class HoverButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HoverButton(const QString &text, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QString normalText;
    QString hoverText;
};