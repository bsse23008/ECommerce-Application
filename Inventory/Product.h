#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>
#include <vector>
#include "Review.h"

using std::cout; 
using std::cin; 
using std::cerr; 
using std::endl; 

class Seller; 

class Product
{
    // friend void Seller :: addProduct (Product* p);
private:
    std::string uniqueId, name, description, category, location, supplier;
    double price, stock;
    // Seller* seller; // Every product has a seller :)
    std::vector<Review> reviews;


public:
    // void addSeller (Seller* s); 
    // constructor and destructor
    Product();
    Product
    (const std::string& id,
     const std::string& name,
      const std::string& description,
       const std::string& category,
        const std::string& location,
         const std::string& supplier,
          double price,
           double stock ) : uniqueId(id), name(name), description(description), category(category), location(location), supplier(supplier), price(price), stock(stock) {}
    ~Product();

    // setters
    void set_unique_id (const std::string&);
    void set_name(const std::string&);
    void set_description(const std::string&);
    void set_category(const std::string&);
    void set_location(const std::string&);
    void set_supplier(const std::string&);
    void set_price(double price);
    void set_stock(double stock);
    void add_review(const Review);
    // void set_rating(double rating); // We don,t need to set the rating :(

    // getters
    std::string get_unique_id () const { return uniqueId; }
    std::string get_name();
    std::string get_description();
    std::string get_category();
    std::string get_location();
    std::string get_supplier();
    double get_price();
    double get_stock();
    double get_rating() const;
    std::vector<std::string> get_reviews();

    // Loading data from files
    static Product* fromJson (json& j, Product* p); 
    json* toJson (json* j); 

    void displayReviews () const;

    //ostream operator
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
    bool operator == (const Product& p);

    // void operator ++ (Product& p) { 
    //     this->stock++; 
    // }
};


#endif // _PRODUCT_H_
