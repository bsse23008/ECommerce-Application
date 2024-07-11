#include "Product.h"

Product :: Product () 
:   name{"None"}, 
    description{"None"}, 
    category{"None"}, 
    location{"None"}, 
    supplier{"None"},
    price{0.0},
    stock{0.0},
    rating{0.0} {
}

// Hey Samer also Implement the parameterized constructor!

Product :: ~Product() {

}


// setters
void Product::set_name(std::string name)
{
    this->name = name;
}
void Product::set_description(std::string description)
{
    this->description = description;
}
void Product::set_category(std::string category)
{
    this->category = category;
}
void Product::set_location(std::string location)
{
    this->location = location;
}
void Product::set_supplier(std::string supplier)
{
    this->supplier = supplier;
}
void Product::set_price(double price)
{
    this->price = price;
}
void Product::set_stock(double stock)
{
    this->stock = stock;
}
void Product::set_SubCategory(std::string category)
{
    subCategory = category;
}

// void Product::add_review(std::string review)
// {
//     this->reviews.push_back(review);
// }
void Product::set_rating(double rating)
{
    this->rating = rating;
}
// getters
std::string Product::get_name()
{
    return this->name;
}
std::string Product::get_description()
{
    return this->description;
}
std::string Product::get_category()
{
    return this->category;
}
std::string Product::get_location()
{
    return this->location;
}
std::string Product::get_supplier()
{
    return this->supplier;
}
double Product::get_price()
{
    return this->price;
}
double Product::get_stock()
{
    return this->stock;
}
std::string Product::get_subCategory()
{
    return this->subCategory;
}

// std::vector <std::string> Product:: get_reviews(){
//     return this->reviews;
// }
double Product::get_rating()
{
    return this->rating;
}
// ostream operator

std::ostream &operator<<(std::ostream &os, const Product &product)
{
    os << "Name: " << product.name << std::endl;
    os << "Description: " << product.description << std::endl;
    os << "Category: " << product.category << std::endl;
    os << "Sub Category: " << product.subCategory << std::endl;
    os << "Location: " << product.location << std::endl;
    os << "Supplier: " << product.supplier << std::endl;
    os << "Price: " << product.price << std::endl;
    os << "Stock: " << product.stock << std::endl;
    return os;
}