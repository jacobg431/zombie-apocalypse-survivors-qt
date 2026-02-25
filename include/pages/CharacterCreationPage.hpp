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
class CharacterStatsPanel;

class CharacterCreationPage : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterCreationPage(QWidget *parent = nullptr);

private:
    QMap<QString, Survivor *> _role_map;
    
    QWidget* createTitleLabel();
    QWidget* createLeftPanel();
    QWidget* createSurvivorForm();
    QWidget* createSurvivorImage();
    QWidget* createCharacterStatsPanel();
    QFrame* createInnerWrapper();
    QFrame* createWrapper();

    CreateCharacterFormBox* _formBox = nullptr;
    CharacterStatsPanel* _characterStatsPanel = nullptr;
    QLabel* _classImageLabel;

    void initRoleMap();
    void glitchSwapPixmap(const QPixmap& finalPm);
    void applyStyling();

signals:
    void characterCreated();

private slots:
    void updateSelectedClass();
};