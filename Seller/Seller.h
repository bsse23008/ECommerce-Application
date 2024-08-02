#ifndef _SELLER_H_
#define _SELLER_H_

#include "../User/User.h"

class ECommerce;
class Database;

class  Seller : public User
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
                                    const std::string &);    // Parameterized Constructor   

    std::string getPhoneNo () const; 
    std::string getOrganization () const; 
    std::string getDOB () const; 
    std::string getCNIC () const;   

    void setPhoneNo (const std::string& ); 
    void setOrganization (const std::string&); 
    void setDOB (const std::string&); 
    void setCNIC (const std::string&);  


    // File loading methods
    static Seller* fromJson (json&); 
    virtual json& toJson (json&) const override;


    // Seller Functionalities
    virtual void dashBoard () override; // Seller DashBoard :)
    void storeManagement ();
    void loadMyProducts ();
    Product* searchProduct (const std::string& );
    void addProduct (Product* ); 
    void removeProduct (Product* );
    void displayMyProducts () const;

};

#endif // _SELLER_H_