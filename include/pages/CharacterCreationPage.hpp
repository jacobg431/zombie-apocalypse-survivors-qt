#pragma once

#include <QWidget>
#include <QMap>

#include "managers/RoleManager.hpp"

// Forward declare to reduce compile time
class QFormLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QString;
class QPixmap;
class QLabel;
class QFrame;
class InfoBox;
class CreateCharacterFormBox;

class CharacterCreationPage : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreationPage(QWidget *parent = nullptr);

private:
    inline static const QStringList ATTRIBUTES = {
        "Strength", "Agility", "Endurance", "Intelligence",
        "Leadership", "Trustworthiness", "Courage"
    };
    inline static const QStringList ATTRIBUTES_DEFAULT_VALUES = {
        "0", "0", "0", "0", "0", "0", "0"
    };

    QMap<QString, Survivor *> _role_map;
    
    QWidget* createTitleLabel();
    QWidget* createLeftPanel();
    QWidget* createSurvivorForm();
    QWidget* createSurvivorImage();
    QWidget* createSurvivorDesc();
    QFrame* createInnerWrapper();
    QFrame* createWrapper();

    InfoBox* _descriptionInfoBox = nullptr;
    InfoBox* _attributesInfoBox = nullptr;
    InfoBox* _skillsInfoBox = nullptr;

    CreateCharacterFormBox* _formBox = nullptr;
    QLabel* _classImageLabel;

    void initRoleMap();
    void wireConnections();
    void glitchSwapPixmap(const QPixmap& finalPm);
    void applyStyling();

signals:
    void characterCreated();

private slots:
    void updateSelectedClass();
};