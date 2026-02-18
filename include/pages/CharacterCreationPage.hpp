#pragma once
#include <QWidget>
#include <QMap>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include "ZasLib/Roles.hpp"

class CharacterCreationPage : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreationPage(QWidget *parent = nullptr);

private:
    // Example data for populating the page
    Hero hero_{"Example Hero Class"};
    CareGiver caregiver_{"Example CareGiver Class"};
    Outlaw outlaw_{"Example Outlaw Class"};
    Jester jester_{"Example Jester Class"};

    QMap<QString, Survivor *> role_map_;
    QMap<QString, QLabel *> attributesMap_;
    QLabel *skillList_;
    QLabel *descriptionLabel_;

    void initRoleMap();

    auto heroFormComponent();

    auto heroImageComponent();

    QVBoxLayout *HeroDescComponent();

signals:
    void characterCreated();

private slots:
    void classSelectUpdated(const QString &class_name);
};