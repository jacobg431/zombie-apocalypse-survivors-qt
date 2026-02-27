#pragma once

#include <QFrame>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QVector>
#include <QLabel>

class ItemsPanel : public QFrame
{
public:
    explicit ItemsPanel(const QString& title, QWidget *parent = nullptr);
    explicit ItemsPanel(const QString& title, const QString& buttonText, const QVector<QString>& items = {}, QWidget *parent = nullptr);
    void applyStyling();

private:
    QLabel* createTitleLabel(const QString& title);
    QFrame* createGrid();
    QFrame* createBottomWrapper(const QString& buttonText);
    QFrame* createInnerWrapper(const QString& title);
    QFrame* createInnerWrapper(const QString& title, const QString& buttonText);

    void normalizeItems(); 
    
    QPushButton* m_button = nullptr;
    QVector<QPushButton*> m_itemButtons;
    QLabel* m_selectedItemLabel = nullptr;
    QVector<QString> m_items;
};