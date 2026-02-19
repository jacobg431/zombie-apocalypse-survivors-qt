#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVector>

class ItemsShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsShopPage(QWidget *parent = nullptr);

signals:
    void GoBackClicked();

private:
    QWidget* createGoBackPanel();
    QWidget* createShopPanel();
    QWidget* createInventoryPanel();
    void applyStyling();

    QPushButton* m_backButton = nullptr;
};
