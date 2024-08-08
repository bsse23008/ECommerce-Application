#include "Inventory.h"
#include "./../Database/Database.h"

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
// setting categories
// void Inventory::setCategorie(std::vector<Categories> &categories)
// {
//     this->categories = categories;
// }
// // adding, removing, updating, displaying and searching products
// void Inventory::addProduct()
// {
//     Product product;
//     product.get_category();
//     for (size_t i = 0; i < categories.size(); i++)
//     {
//         if (product.get_category() == categories[i].getCategory())
//         {
//             product.set_SubCategory(categories[i]);
//         }
//     }
//     std::string name;
//     std::string description;
//     std::string location;
//     double price;
//     int stock;
//     std::cout << "Enter the name of the product : ";
//     std::getline(std::cin, name);
//     product.set_name(name);
//     std::cout << "Enter the description of the product : ";
//     std::getline(std::cin, description);
//     product.set_description(description);
//     std::cout << "Enter the location of the product : ";
//     std::getline(std::cin, location);
//     product.set_location(location);
//     std::cout << "Enter the price of the product : ";
//     do
//     {
//         std::cin >> price;
//         if (price <= 0)
//         {
//             std::cout << "Price cannot be negative or zero. Please try again." << std::endl;
//         }
//     } while (price <= 0);
//     product.set_price(price);
//     std::cout << "Enter the stock of the product : ";
//     do
//     {
//         std::cin >> stock;
//         if (stock <= 0)
//         {
//             std::cout << "Stock cannot be negative or zero. Please try again." << std::endl;
//         }
//     } while (stock <= 0);
//     product.set_stock(stock);
// }

// void Inventory::removeProduct() {}
// void Inventory::updateProduct() {}
// void Inventory::displayProducts() {}
// void Inventory::searchProduct() {}

void Inventory :: loadInventory (Product* p) { 
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
