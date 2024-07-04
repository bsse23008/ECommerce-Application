#if !defined(Inventory_H_)
#define Inventory_H_

#include <iostream>
class Inventory

{
private:
    std::string name;
    std::string description;
    std::string category;
    std::string location;
    std::string supplier;
    double price;
    double stock;
public:
    //setters
    void set_name(std::string name);
    void set_description(std::string description);
    void set_category(std::string category);
    void set_location(std::string location);
    void set_supplier(std::string supplier);
    void set_price(double price);
    void set_stock(double stock);
    //getters
    std::string get_name(); 
    std::string get_description();
    std::string get_category();
    std::string get_location();
    std::string get_supplier();
    double get_price();
    Inventory(/* args */);
    ~Inventory();
    friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory);
};




#endif // Inventory_H_
