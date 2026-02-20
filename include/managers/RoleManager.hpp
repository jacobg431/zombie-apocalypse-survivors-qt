#pragma once

#include <memory>
#include <QMap>
#include <QString>

#include "ZasLib/Roles.hpp"

class RoleManager
{
public:
    static RoleManager& instance();

    RoleManager(const RoleManager&) = delete;
    RoleManager& operator=(const RoleManager&) = delete;

    const Survivor* getRole(const QString& name) const;
    QStringList availableRoles() const;

private:
    RoleManager();
    QMap<QString, std::unique_ptr<Survivor>> _roles;
};