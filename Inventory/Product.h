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
    std::string subCategory;
    std::string location;
    std::string supplier;
    double price;
    double stock;
    double rating;
    std::vector<Review> reviews;

public:
    // setters
    void set_name(std::string name);
    void set_description(std::string description);
    void set_category(std::string category);
    void set_SubCategory(std::string category);
    void set_location(std::string location);
    void set_supplier(std::string supplier);
    void set_price(double price);
    void set_stock(double stock);
    void add_review(std::string review);
    void set_rating(double rating);
    // getters
    std::string get_name();
    std::string get_description();
    std::string get_category();
    std::string get_location();
    std::string get_supplier();
    double get_price();
    double get_stock();
    double get_rating();
    std::string get_subCategory();
    std::vector<std::string> get_reviews();
    // constructor and destructor
    Product(/* args */);
    ~Product();
     //ostream operator
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
};


#endif // PRODUCT_H_
