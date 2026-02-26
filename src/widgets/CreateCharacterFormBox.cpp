#include <QGroupBox>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>

#include "widgets/CreateCharacterFormBox.hpp"

CreateCharacterFormBox::CreateCharacterFormBox(
    QStringList roles,
    QWidget *parent
)
    : QGroupBox("Name and Class", parent)
{
    auto *layout = new QFormLayout(this);
    layout->setContentsMargins(16, 16, 32, 16);
    layout->setLabelAlignment(Qt::AlignHCenter);
    layout->setFormAlignment(Qt::AlignHCenter);
    layout->addRow(createNameInput());
    layout->addRow(createClassSelector(roles));
    layout->addRow(createSubmitButton());

    applyStyling();
}

QString CreateCharacterFormBox::getCurrentSelectorText()
{
    return _classSelector ? _classSelector->currentText() : QString{};
}

QLineEdit* CreateCharacterFormBox::createNameInput()
{
    auto *nameInput = new QLineEdit(this);
    nameInput->setObjectName("survivorNameEdit");
    nameInput->setFixedWidth(INPUT_WIDTH);

    return nameInput;
}

QComboBox* CreateCharacterFormBox::createClassSelector(QStringList& roles)
{
    _classSelector = new QComboBox(this);
    _classSelector->setObjectName("survivorClassSelect");
    _classSelector->addItems(roles);
    _classSelector->setFixedWidth(INPUT_WIDTH);

    connect(_classSelector, &QComboBox::currentTextChanged,
        this, &CreateCharacterFormBox::classSelectUpdated);

    return _classSelector;
}

QPushButton* CreateCharacterFormBox::createSubmitButton()
{
    _submitButton = new QPushButton("Create Character", this);
    _submitButton->setCursor(Qt::PointingHandCursor);
    _submitButton->setFixedWidth(INPUT_WIDTH);
    _submitButton->setMinimumHeight(65);

    connect(_submitButton, &QPushButton::clicked, 
        this, &CreateCharacterFormBox::characterCreated);
    
    return _submitButton;
}

void CreateCharacterFormBox::applyStyling()
{
    setStyleSheet(R"(
        QLineEdit#survivorNameEdit {
            background-color: #c91e1e1e;
            color: white;
            padding-left: 12px;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;
            height: 30px; 
        }

        QLineEdit#survivorNameEdit:focus {
            border-color: #c9ff5733;
        }

        QComboBox#survivorClassSelect {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;

            height: 30px; 
            padding-left: 12px;
            
        }

        QComboBox#survivorClassSelect:drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 28px;
            border-left: 2px solid #c91e1e1e;
            border-top-right-radius: 6px;
            border-bottom-right-radius: 6px;
            background: #c91e1e1e;
            padding: 6px 6px;
        }

        QComboBox#survivorClassSelect:down-arrow {
            image: url(:/resources/images/chevron-down.png);
        }

        QComboBox#survivorClassSelect QAbstractItemView {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c9ff5733;
            selection-background-color: #c91e1e1e;
            selection-color: white;
            background-clip: border;
        }

        QComboBox#survivorClassSelect QAbstractItemView:item {
            background: #c91e1e1e;
            padding: 6px 12px;
            margin: 2px;
        }

        QComboBox#survivorClassSelect QAbstractItemView:item:selected {
            background: #c91e1e1e;
        }

        QComboBox#survivorClassSelect QAbstractItemView:item:hover {
            background: #c91e1e1e;
        }

        QPushButton {
            background-color: #c91e1e1e;
            color: white;
            border: 2px solid #c91e1e1e;
            border-radius: 6px;
            padding: 6px 12px;
            text-align: center;
            margin-top: 24px;
            margin-bottom: 12px;
            }

        QPushButton:hover {
            background-color: #c91e1e1e;
            border-color: #5bff5733;
        }

        QPushButton:pressed {
            background-color: #c9ff5733;
            padding: 4px 10px;
        }
            
        QGroupBox {
            background-color: transparent;
            border-image: url(:/resources/images/wooden-sign-square-fried.png);
            border: none;

            margin: -8px;

            margin-top: -4px;
            margin-bottom: -8px;
            margin-left: -16px;
            margin-right: -16px;

            padding-left: 32px;
            padding-top: 32px;
        }

        QGroupBox:title {
            border-image: url(:/resources/images/slash.png) 0 0 0 0 stretch stretch;
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 0px;
            right: 0px;
            width: 100%;

            color: #FF5733;
        }
    )");
}