#ifndef _SELLER_H_
#define _SELLER_H_

#include "../User/User.h"
#include "../Inventory/Inventory.h"

class ECommerce;
class Database;

class Seller : public User
{
    friend std::ostream& operator << (std::ostream& os, const Seller& seller);
private:
    std::string phoneNo, organization, DOB, CNIC;     // Adding some attributes specific to Seller only
    std::vector<Product*> products; // A Seller has some products to sell
public:
    Seller();
    virtual ~Seller () {
        cout << "\nSeller destructor called!" << endl;
    }
    Seller(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

    std::string getPhoneNo () const; 
    std::string getOrganization () const; 
    std::string getDOB () const; 
    std::string getCNIC () const;   

    void setPhoneNo (const std::string& ); 
    void setOrganization (const std::string&); 
    void setDOB (const std::string&); 
    void setCNIC (const std::string&);  

    // Overriden
    virtual void dashBoard () override;

    // File loading methods
    static Seller* fromJson (json& j); 
    virtual json& toJson (json& j) const override;

    void loadProducts (Product*  p) { 
        products.emplace_back  (p); 
    }

    
    // Seller Functionalities
    void addProduct (Product* p); 
    Product* searchProduct (const std::string& id);
    // void removeProduct (const std::string& p); // remove by unique Id of product
    void removeProduct (Product* p); // remove by address 

    void displayMyProducts () const {
        for (const Product* p : products) { 
            cout << "\n____________________________________" << endl; 
            cout << *p << endl;
        }
    } 

    /*
        virtual void display () const override {
            User :: display();
            cout << *this << endl;  
        } 
    */
};

#endif // _SELLER_H_