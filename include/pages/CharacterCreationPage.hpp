#pragma once
#include "ZasLib/Roles.hpp"

#include <QWidget>
#include <QMap>

// Forward declare to reduce compile time
class QVBoxLayout;
class QFormLayout;
class QLineEdit;
class QComboBox;
class QString;
class QLabel;
class QPixmap;

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
    QLabel *classImageLabel_;

    void initRoleMap();

    QFormLayout *heroFormComponent();
    QLineEdit *nameEdit_ = nullptr;
    QComboBox *classSelect_ = nullptr;

    QVBoxLayout *heroImageComponent();

    QVBoxLayout *HeroDescComponent();

signals:
    void characterCreated();

private slots:
    void classSelectUpdated(const QString &class_name);
};