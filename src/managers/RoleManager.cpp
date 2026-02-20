#include "managers/RoleManager.hpp"

RoleManager& RoleManager::instance()
{
    static RoleManager instance;
    return instance;
}

RoleManager::RoleManager()
{
    _roles.insert("Hero",
        std::make_unique<Hero>("Hero Class"));
    _roles.insert("CareGiver",
        std::make_unique<CareGiver>("CareGiver Class"));
    _roles.insert("Outlaw",
        std::make_unique<Outlaw>("Outlaw Class"));
    _roles.insert("Jester",
        std::make_unique<Jester>("Jester Class"));
}

const Survivor* RoleManager::getRole(const QString& name) const
{
    auto it = _roles.find(name);
    if (it != _roles.end())
        return it.value().get();

    return nullptr;
}

QStringList RoleManager::availableRoles() const
{
    return _roles.keys();
}