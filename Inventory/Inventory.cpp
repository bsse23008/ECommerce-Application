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

void Inventory :: addProduct(Product *p)
{
    products.push_back(p);
    try {
        Database :: getInstance()-> updateInventory(p);
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl;
    }
}

// Kal Inshallah
void Inventory :: removeProduct(const std::string &id)
{

}

void Inventory :: removeProduct(Product *p)
{

}
