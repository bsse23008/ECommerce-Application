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

    void addProduct(Product *p);
    void removeProduct(const std::string &id);
    void removeProduct(Product *p);
};

#endif // _INVENTORY_H_
