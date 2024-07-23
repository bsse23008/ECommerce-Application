#if !defined(PRODUCT_H_)
#define PRODUCT_H_

#include <iostream>
#include <vector>
#include "Review.h"

class Product
{
private:
    std::string name;
    std::string description;
    std::string category;
    std::string location;
    std::string supplier;
    double price;
    double stock;
    double rating;
    std::vector<Review> reviews;

public:
    // constructor and destructor
    Product(/* args */);
    ~Product();

    // setters
    void set_name(std::string name);
    void set_description(std::string description);
    void set_category(std::string category);
    void set_location(std::string location);
    void set_supplier(std::string supplier);
    void set_price(double price);
    void set_stock(double stock);
    void add_review(const Review);
    // void set_rating(double rating); // We don,t need to set the rating :(

    // getters
    std::string get_name();
    std::string get_description();
    std::string get_category();
    std::string get_location();
    std::string get_supplier();
    double get_price();
    double get_stock();
    double get_rating();
    std::vector<std::string> get_reviews();

    // Loading data from files
    static Product* fromJson (json& j, Product* p); 
    json* toJson (json* j); 

    void displayReviews () const;

    //ostream operator
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
};


#endif // PRODUCT_H_
