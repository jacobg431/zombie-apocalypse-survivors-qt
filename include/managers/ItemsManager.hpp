#pragma once
#include <QObject>
#include <QMap>
#include <QString>
#include <memory>
#include "ZasLib/Items.hpp"

class ItemsManager : public QObject{
    Q_OBJECT
public: 
    static ItemsManager& instance();

    ItemsManager(const ItemsManager&) = delete;
    ItemsManager& operator=(const ItemsManager&) = delete;


private: 
    ItemsManager(); 
    std::map<QString, std::unique_ptr<Survivor>> _items;

}; 