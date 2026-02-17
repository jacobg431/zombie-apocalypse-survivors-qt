#include "pages/CharacterCreationPage.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QHBoxLayout(this);


    // --- Left panel (pick name & class) ---

    auto *name_input = new QLineEdit(this);
    name_input->setMaximumWidth(250);

    auto *class_select = new QComboBox(this);
    class_select->addItems({"Option 1", "Option 2", "Option 3"});
    class_select->setMaximumWidth(250);


    auto *hero_form = new QFormLayout();
    hero_form->setLabelAlignment(Qt::AlignLeft);
    hero_form->setFormAlignment(Qt::AlignTop);
    hero_form->addRow("Hero Name:", name_input);
    hero_form->addRow("Hero Class:", class_select);


    // --- Middle panel (class picture) ---
    auto *middle_panel = new QVBoxLayout();
    middle_panel->addWidget(new QLabel("Placeholder image"));


    // --- Right panel (class descriptions) ---
    auto *right_panel = new QVBoxLayout();
    right_panel->addWidget(new QLabel("Placeholder description"));


    
    layout->addLayout(hero_form);
    layout->addLayout(middle_panel);
    layout->addLayout(right_panel);
}