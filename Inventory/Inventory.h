#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Product.h"
#include "./../ECommerce/Categories.h"

class Inventory
{
private:
    static Inventory* instance;
    std::vector<Product> products;
    std::vector<Categories>categories;
    // pivate constructor
    Inventory();

public:
    //singleton pattern
    static Inventory* getInstance();
    static void deleteInstance();
    // destructor
    ~Inventory();
    //setter
    void setCategorie(std::vector<Categories> &categories);
    //adding, removing, updating, displaying and searching products
    void addProduct();
    void removeProduct();
    void updateProduct();
    void displayProducts();
    void searchProduct();
    
};

#endif // _INVENTORY_H_
