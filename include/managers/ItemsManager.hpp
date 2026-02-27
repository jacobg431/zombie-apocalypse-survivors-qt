#pragma once
#include <QObject>
#include <QMap>
#include <QString>
#include <memory>
#include "ZasLib/Equipment.hpp"

class ItemsManager {
public: 
    static ItemsManager& instance();

    ItemsManager(const ItemsManager&) = delete;
    ItemsManager& operator=(const ItemsManager&) = delete;

    const Equipment* getItem(const QString& name) const;
    QVector<QString> availableItems() const;


private: 
    ItemsManager(); 
    std::map<QString, std::unique_ptr<Equipment>> _items;

}; 