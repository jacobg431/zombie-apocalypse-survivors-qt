#pragma once
#include <QWidget>
#include <QMap>
#include <QString>
#include <QLabel>
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

    void initRoleMap();

signals:
    void CharacterCreated();

};