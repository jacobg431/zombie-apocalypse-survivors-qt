#include "pages/CharacterCreationPage.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

CharacterCreationPage::CharacterCreationPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QHBoxLayout(this);


    // --- Left panel (pick name & class) ---
    auto *left_panel = new QVBoxLayout();
    left_panel->addWidget(new QLabel("Pick a name:"));
    

    // --- Middle panel (class picture) ---
    auto *middle_panel = new QVBoxLayout();
    middle_panel->addWidget(new QLabel("Placeholder image"));


    // --- Right panel (class descriptions) ---
    auto *right_panel = new QVBoxLayout();
    right_panel->addWidget(new QLabel("Placeholder description"));

    
    layout->addLayout(left_panel);
    layout->addLayout(middle_panel);
    layout->addLayout(right_panel);
}