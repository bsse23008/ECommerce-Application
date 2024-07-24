#ifndef _SELLER_H_
#define _SELLER_H_

#include "../User/User.h"
#include "../Inventory/Product.h"

class Seller : public User
{
private:
    std::string phoneNo, organization, DOB, CNIC;     // Adding some attributes specific to Seller only
    std::vector<Product> products; // A Seller has some products to sell
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

    // Seller Functionalities
    void addProduct (Product p); 
    void removeProduct (Product p);
    void updateMyStore ();
    
};

#endif // _SELLER_H_