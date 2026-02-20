#pragma once
#include "ZasLib/Roles.hpp"

#include <QWidget>
#include <QMap>

// Forward declare to reduce compile time
class QVBoxLayout;
class QFormLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QString;
class QPixmap;
class QLabel;

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

    // UI component builders
    QFormLayout *heroFormComponent();
    QVBoxLayout *heroImageComponent();
    QVBoxLayout *HeroDescComponent();

    QLineEdit *nameEdit_ = nullptr;
    QComboBox *classSelect_ = nullptr;
    QPushButton *submitButton_ = nullptr;

    // Helper functions
    void initRoleMap();
    void glitchSwapPixmap(const QPixmap &finalPm);
    void applyStyling();

signals:
    void characterCreated();

private slots:
    void classSelectUpdated(const QString &class_name);
};