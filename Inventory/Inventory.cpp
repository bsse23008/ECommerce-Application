#include "inventory.h"
Inventory* Inventory::instance = nullptr;

//constructor and destructor
Inventory::Inventory(/* args */)
{
}

Inventory::~Inventory()
{
}

//singleton pattern
Inventory* Inventory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Inventory();
    }
    return instance;
}

void Inventory::deleteInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
