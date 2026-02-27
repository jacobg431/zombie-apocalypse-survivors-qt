#include "managers/ItemsManager.hpp"



ItemsManager& ItemsManager::instance()
{
    static ItemsManager instance;
    return instance;
}


ItemsManager::ItemsManager()
{
    // Weapons
    _items.emplace("RustyKnife",
        std::make_unique<Weapon>("Rusty Knife", 1, 10));

    _items.emplace("BaseballBat",
        std::make_unique<Weapon>("Baseball Bat", 3, 18));

    _items.emplace("Revolver",
        std::make_unique<Weapon>("Revolver", 4, 35));

    _items.emplace("HuntingRifle",
        std::make_unique<Weapon>("Hunting Rifle", 6, 55));

    _items.emplace("Machete",
        std::make_unique<Weapon>("Machete", 2, 22));


    // Tools
    _items.emplace("Hammer",
        std::make_unique<Tool>("Hammer", 3, 80));

    _items.emplace("Crowbar",
        std::make_unique<Tool>("Crowbar", 4, 90));

    _items.emplace("LockpickSet",
        std::make_unique<Tool>("Lockpick Set", 1, 60));

    _items.emplace("Wrench",
        std::make_unique<Tool>("Wrench", 2, 75));

    _items.emplace("Shovel",
        std::make_unique<Tool>("Shovel", 5, 85));


    // Consumables
    _items.emplace("Medkit",
        std::make_unique<Consumable>("Medkit", 2, 3));

    _items.emplace("Bandage",
        std::make_unique<Consumable>("Bandage", 1, 2));

    _items.emplace("EnergyDrink",
        std::make_unique<Consumable>("Energy Drink", 1, 1));

    _items.emplace("CannedFood",
        std::make_unique<Consumable>("Canned Food", 2, 1));

    _items.emplace("Painkillers",
        std::make_unique<Consumable>("Painkillers", 1, 2));

    _items.emplace("MolotovCocktail",
        std::make_unique<Consumable>("Molotov Cocktail", 2, 1));
}