#include "inventory.h"
Inventory *Inventory::instance = nullptr;

// constructor and destructor
Inventory::Inventory(/* args */)
{
}

Inventory::~Inventory()
{
}
// setting categories
void Inventory::setCategorie(std::vector<Categories> &categories)
{
    this->categories = categories;
}
// adding, removing, updating, displaying and searching products
void Inventory::addProduct()
{
    Product product;
    product.get_category();
    for (size_t i = 0; i < categories.size(); i++)
    {
        if (product.get_category() == categories[i].getCategory())
        {
            product.set_SubCategory(categories[i]);
        }
    }
    std::string name;
    std::string description;
    std::string location;
    double price;
    int stock;
    std::cout << "Enter the name of the product : ";
    std::getline(std::cin, name);
    product.set_name(name);
    std::cout << "Enter the description of the product : ";
    std::getline(std::cin, description);
    product.set_description(description);
    std::cout << "Enter the location of the product : ";
    std::getline(std::cin, location);
    product.set_location(location);
    std::cout << "Enter the price of the product : ";
    do
    {
        std::cin >> price;
        if (price <= 0)
        {
            std::cout << "Price cannot be negative or zero. Please try again." << std::endl;
        }
    } while (price <= 0);
    product.set_price(price);
    std::cout << "Enter the stock of the product : ";
    do
    {
        std::cin >> stock;
        if (stock <= 0)
        {
            std::cout << "Stock cannot be negative or zero. Please try again." << std::endl;
        }
    } while (stock <= 0);
    product.set_stock(stock);
}

void Inventory::removeProduct() {}
void Inventory::updateProduct() {}
void Inventory::displayProducts() {}
void Inventory::searchProduct() {}

// singleton pattern
Inventory *Inventory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Inventory();
    }
    return instance;
}

void Inventory::deleteInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
