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
void Product :: set_unique_id (const std::string& id) { 
    this->uniqueId = id; // Unique Identifier for every product 
}
void Product::set_name(const std::string& name)
{
    this->name = name;
}
void Product::set_description(const std::string& description)
{
    this->description = description;
}
void Product::set_category(const std::string& category)
{
    this->category = category;
}
void Product::set_location(const std::string& location)
{
    this->location = location;
}
void Product::set_supplier(const std::string& supplier)
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


void Product::add_review(const Review review) { // rating + comments 
    reviews.push_back(review);
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
double Product::get_stock(){
    return this->stock;
}
// std::vector <std::string> Product:: get_reviews(){
//     return this->reviews;
// }

double Product::get_rating(){
    for (int i=0; i<reviews.size(); i++) {
        this->rating += reviews[i].getRating();
    }
    return this->rating; 
}


//istream operator 
std::istream& operator>>(std::istream& is, Product& product) { 

// Take input of th product
cout << "\nEnter the following details for the product:" << endl; 
    cout << "Enter product Id (should be unique): "; is >> product.uniqueId; 
    
    cout << "Enter name of product: "; is >> product.name; 
    cout << "Enter Description: "; is >> product.description;
    cout << "Enyer category   : "; is >> product.category ;
    cout << "Enter    Location: "; is >> product.location ;
    cout << "Supplier of product: "; is >> product.supplier ;
    cout << "Price of product   : "; is >> product.price ;
    cout << "Stock of product   : "; is >> product.stock ; 
    return is; 
}


//ostream operator
std::ostream& operator<<(std::ostream& os, const Product& product){
    os << "Name: " << product.name << std::endl;
    os << "Description: " << product.description << std::endl;
    os << "Category: " << product.category << std::endl;
    os << "Location: " << product.location << std::endl;
    os << "Supplier: " << product.supplier << std::endl;
    os << "Price: " << product.price << std::endl;
    os << "Stock: " << product.stock << std::endl;
    /*
        We can also see the reviews of this product by using display reviews method. 
        But reviews will be shown on the demand of the customer/buyer.
    */
    return os;
}

// == operator (verify that the two objects are equal or not)
bool Product :: operator == (const Product& p) { 
    return (this->name == p.name && this->description == p.description && this->category == p.category && this->price == p.price); 
}


Product* Product :: fromJson ( json& j, Product* p ) {
    // Product p; 
    p->set_unique_id (j["uniqueId"]);
    p->set_name(j["name"]);
    p->set_description(j["description"]);
    p->set_category(j["category"]);
    p->set_location(j["location"]);
    p->set_supplier(j["supplier"]);
    p->set_price(j["price"]);
    p->set_stock(j["stock"]);

    for (int i=0; i < j["reviews"].size(); i++) {
        Review* temp = new Review (j["review"][i]["rating"], j["review"][i]["comment"]); 
        p->add_review(*temp);
        delete temp; 
    }
    return p; 
}

json* Product :: toJson (json* j) {
    (*j)["uniqueId"] = this->uniqueId; 
    (*j)["name"] = this->name; 
    (*j)["description"] = this->description;
    (*j)["category"] = this->category; 
    (*j)["location"] = this->location; 
    (*j)["supplier"] = this->supplier; 
    (*j)["price"] = this->price; 
    (*j)["stock"] = this->stock; 

    for (int i=0; reviews.size(); i++) { 
        (*j)["reviews"][i] = reviews[i].toJson();
    }
    return j;
}

void Product :: displayReviews () const {
    for (const auto& r : reviews) {
        std::cout << r << std::endl; 
    }
}