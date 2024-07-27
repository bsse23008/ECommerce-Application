#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Product.h"

class Database;

class Inventory
{
private:
    std::vector<Product *> products;

public:
    // constructor and destructor
    Inventory(/* args */);
    ~Inventory();

    Product *getReference(const std::string &id);

    bool isUniqueId (const std::string& id) { 
        for (int i=0; i<products.size(); i++) { 
            if (id == products.at(i)->get_unique_id()) { 
                return true; 
            }
        }
        return false; 
    }

    void loadInventory (Product* p);
    void addProduct(Product *p);
    void removeProduct(Product *p);
};

#endif // _INVENTORY_H_
