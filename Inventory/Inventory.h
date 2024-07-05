#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Product.h"

class Inventory
{
private:
    static Inventory* instance;
    std::vector<Product> products;
    // pivate constructor
    Inventory();

public:
    //singleton pattern
    static Inventory* getInstance();
    static void deleteInstance();
    // destructor
    ~Inventory();
    //methods
    void addProduct();
    void removeProduct();
    void updateProduct();
    void displayProducts();
    void searchProduct();
    
};

#endif // _INVENTORY_H_
