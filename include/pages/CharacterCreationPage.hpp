#pragma once

#include <QWidget>
#include <QMap>

#include "managers/RoleManager.hpp"

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
    QMap<QString, Survivor *> _role_map;
    QMap<QString, QLabel *> _attributesMap;
    
    // UI component builders
    QWidget *createSurvivorForm();
    QWidget *createSurvivorImage();
    QWidget *createSurvivorDesc();

    QLineEdit *_nameEdit = nullptr;
    QComboBox *_classSelect = nullptr;
    QPushButton *_submitButton = nullptr;

    QLabel *_skillList;
    QLabel *_descriptionLabel;
    QLabel *_classImageLabel;

    // Helper functions
    void initRoleMap();
    void glitchSwapPixmap(const QPixmap &finalPm);
    void applyStyling();

signals:
    void characterCreated();

private slots:
    void classSelectUpdated(const QString &class_name);
};