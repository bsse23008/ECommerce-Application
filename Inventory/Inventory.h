#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Product.h"
#include "./../ECommerce/Categories.h"


class Inventory
{
private:
    std::vector<Product *> products;

public:
    // constructor and destructor
    Inventory(/* args */);
    ~Inventory();

    Product *getReference(const std::string &id);
    void loadInventory(Product *p);
    bool isUniqueId(const std::string &id);
    void addProduct(Product *p);
    void removeProduct(Product *p);
    void displayProducts() const;
};

#endif // _INVENTORY_H_
