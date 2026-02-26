#pragma once

#include <QGroupBox>

class QWidget;
class QString;
class QLineEdit;
class QComboBox;

class CreateCharacterFormBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit CreateCharacterFormBox
    (
        QStringList roles,
        QWidget *parent = nullptr
    );
    QString getCurrentSelectorText();

private:
    const int INPUT_WIDTH = 160;

    QLineEdit* createNameInput();
    QComboBox* createClassSelector(QStringList& roles);
    QPushButton* createSubmitButton();

    QLineEdit* _nameInput = nullptr;
    QComboBox* _classSelector = nullptr;
    QPushButton* _submitButton = nullptr;

    void applyStyling();

signals:
    void classSelectUpdated();
    void characterCreated();

private slots:
    void onCharacterCreated();
};
