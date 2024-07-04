#include "inventory.h"

Inventory::Inventory(/* args */)
{
}

Inventory::~Inventory()
{
}

// setters
void Inventory::set_name(std::string name)
{
    this->name = name;
}
void Inventory::set_description(std::string description)
{
    this->description = description;
}
void Inventory::set_category(std::string category)
{
    this->category = category;
}
void Inventory::set_location(std::string location)
{
    this->location = location;
}
void Inventory::set_supplier(std::string supplier)
{
    this->supplier = supplier;
}
void Inventory::set_price(double price)
{
    this->price = price;
}
void Inventory::set_stock(double stock)
{
    this->stock = stock;
}
// getters
std::string Inventory::get_name()
{
    return this->name;
}
std::string Inventory::get_description()
{
    return this->description;
}
std::string Inventory::get_category()
{
    return this->category;
}
std::string Inventory::get_location()
{
    return this->location;
}
std::string Inventory::get_supplier()
{
    return this->supplier;
}
double Inventory::get_price()
{
    return this->price;
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory){
    os << "Name: " << inventory.name << std::endl;
    os << "Description: " << inventory.description << std::endl;
    os << "Category: " << inventory.category << std::endl;
    os << "Location: " << inventory.location << std::endl;
    os << "Supplier: " << inventory.supplier << std::endl;
    os << "Price: " << inventory.price << std::endl;
    os << "Stock: " << inventory.stock << std::endl;
    return os;
}
