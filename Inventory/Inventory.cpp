#include "Inventory.h"
#include "./../Database/Database.h"
#include "./../ECommerce/ECommerce.h"

// constructor and destructor
Inventory::Inventory(/* args */) {
    
}

Inventory::~Inventory() {

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
    // const User* user = ECommerce :: getInstance ()->getSellerReference (p->get_supplier_id()); 
    // const Seller* s = dynamic_cast<const Seller*> (user);
    // p->setSupplier (s);
    products.push_back (p);
}



bool Inventory :: isUniqueId (const std::string& id) { 
    for (size_t i=0; i<products.size(); i++) { 
        if (id == products.at(i)->get_unique_id()) { 
            return true; 
        }
    }
    return false; 
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
    for (auto it = products.begin(); it !=products.end(); ++it) { 
        if ((*it) == p) { 
            Database :: getInstance()-> removeProductFromAppInventory ((*it)->get_unique_id()); // Remove product from centralized inventory (Main Database for products)
            products.erase (it);
            break; 
        }
    }
}


void Inventory :: displayProducts () const { 
    std::vector<Product*> :: const_iterator it = products.begin();
    while (it != products.end()) { 
        std::cout << **it << std::endl; 
        std::cout <<  "___________________________________" << std::endl; 
        ++it; 
    }
}
