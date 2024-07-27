#include "Inventory.h"
#include "./../Database/Database.h"

// constructor and destructor
Inventory::Inventory(/* args */)
{
}

Inventory::~Inventory()
{
}

// Every selller will have reference to his own products
Product *Inventory ::getReference(const std::string &id)
{
    for (auto &p : products) {
        if (p->get_unique_id() == id) {
            return p;
        }
    }
    return nullptr;
}


void Inventory :: loadInventory (Product* p) { 
    products.push_back (p);
}

void Inventory :: addProduct(Product *p)
{
    products.push_back(p);
    try {
        Database :: getInstance()->addProductToAppInventory(p);
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl;
    }
}

void Inventory :: removeProduct(Product *p)
{
    // Which loop is better between the following : 

    /*
        for (size_t i=0; i < products.size(); ++i) { 
            if (products[i] == p) {    
                products.erase (products.begin() + i); // Erase the memory adderss from the centralized inventory as well
                break;
            }
        }
    */

    for (auto it = products.begin(); it !=products.end(); ++it) { 
        if ((*it) == p) { 
            Database :: getInstance()-> removeProductFromAppInventory ((*it)->get_unique_id()); // Remove product from centralized inventory (Main Database for products)
            products.erase (it);
            break; 
        }
    }
}