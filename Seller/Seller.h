#ifndef _SELLER_H_
#define _SELLER_H_

#include "../User/User.h"
#include "../Inventory/Inventory.h"

class ECommerce;

class Seller : public User
{
    friend std::ostream& operator << (std::ostream& os, const Seller& seller);
private:
    std::string phoneNo, organization, DOB, CNIC;     // Adding some attributes specific to Seller only
    std::vector<Product*> products; // A Seller has some products to sell
public:
    Seller();
    ~Seller () {
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

    // File loading methods
    static Seller* fromJson (json& j); 
    json toJson () const;

    void loadMyInventory () { 
        
    }

    // Seller Functionalities
    void addProduct (Product* p); 
    void removeProduct (const std::string& p);
    void updateMyStore (const std::string& user_name);

    void removeProduct (Product* p) {
        for (int i=0; i<products.size(); i++) { 
            if (p == products[i]) { 
                products.erase (products.begin() + i);
                break; 
            }
        }
    }

    Product* searchProduct (const std::string& id) { 
        for (int i=0; i<products.size(); i++) { 
            if (id == products[i]->get_unique_id()) { 
                return products[i];
            }
        }
        return nullptr;
    }

    bool isUniqueId (const std::string& id) { 
        for (int i=0; i<products.size(); i++) { 
            if (id == products.at(i)->get_unique_id()) { 
                return true; 
            }
        }
        return false; 
    }

    void displayMyProducts () const {
        for (const Product* p : products) { 
            cout << *p << endl;
        }
    }  
};

void sellerControls (Seller* s);

#endif // _SELLER_H_