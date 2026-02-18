#pragma once

#include <QFrame>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QVector>

class ItemsPanel : public QFrame
{
public:
    explicit ItemsPanel(const QString& title, const QString& buttonText, QWidget *parent = nullptr);
    void applyStyling();

private:
    QPushButton* m_button = nullptr;
    QVector<QPushButton*> m_itemButtons;
};