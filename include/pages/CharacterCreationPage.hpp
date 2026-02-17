#pragma once
#include <QWidget>

class CharacterCreationPage : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreationPage(QWidget *parent = nullptr);

signals:
    void CharacterCreated();
};