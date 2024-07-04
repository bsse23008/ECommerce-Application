#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Product.h"

class Inventory
{
private:
   std::vector<Product> products;
public:
    //constructor and destructor
    Inventory(/* args */);
    ~Inventory();
   
};




#endif // _INVENTORY_H_
