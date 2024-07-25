#include "ECommerce.h"
// Header files location
#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"
#include "./../Inventory/Inventory.h"


ECommerce :: ECommerce() : inventory (nullptr) { 
    inventory = new Inventory();
}

// Release the dynamically allocated memory
ECommerce :: ~ECommerce () {
    cout << "\nECommerce destructor called!" << endl;

    // Do we need to delete all the dynamically allocated memory here? 
    // Aggregation is not that easy :(
    
    for (Buyer* buyer : buyers) {
        delete buyer;
    }
    for (Seller* seller : sellers) {
        delete seller;
    }
    for (Admin* admin : admins) {
        delete admin;
    }
    // The pointed-to memory has been released (from heap). Now clear the addresses of the vectors as well.
    buyers.clear();
    sellers.clear();
    admins.clear();
    delete inventory; 
}

// Singleton get instance function 
ECommerce *ECommerce ::getInstance()
{
    static ECommerce *instance = new ECommerce();
    return instance;
}


// Release the dynamic memory 
void ECommerce :: releaseInstance () {
    delete getInstance(); 
}




// Loading seller inventory just after he logins 
void ECommerce :: loadSellerInventory (Seller* seller) { 
    std::ifstream in  ("./Database/Inventory/Sellers/" + seller->getUserName() + ".json", std::ios::in);
    if (!in.is_open()) { 
        cout << "\nCould not open the file :(" << endl; 
        return;
    }
    json j; 
    in >> j; 
    in.close();
    for (int i=0; i<j["productIds"].size(); i++) { 
        Product* p = inventory->getReference (j["productIds"][i]);
        if (p)
            seller->addProduct (p); // If p is not null, only then add 
    }
}


// Searching functions 
template <typename T> 
void ECommerce :: searchUser (const std::vector<T*>& vec, const std::string& u) // template function to search any user 
{
    for (int i=0; i<vec.size(); i++) { 
        if (vec[i]->getUserName() == u) { 
            cout << "\nUSER INFO"<<endl; 
            std::cout << *vec[i] << std::endl; 
            return; 
        }
    }
    cout << u << " was not found in the list :(" << std::endl; 
}
void ECommerce :: searchBuyer (const std::string& u) { 
    searchUser <Buyer> (buyers, u);
}

void ECommerce :: searchSeller (const std::string& u) { 
    searchUser <Seller> (sellers, u);
}


// template function to add a User (Admin/Buyer/Seller)
template <typename type> 
void ECommerce :: addUser (const std::string& filePath, type* obj, std::vector<type*>& vec) {
    vec.push_back(obj); 
}

void ECommerce :: addBuyer(Buyer *b) { 
    addUser<Buyer> (buyers_filePath , b, buyers);
    Database :: getInstance()->add_buyer (*b);  // Updating the database 
}

void ECommerce :: addSeller(Seller *s) {
    addUser<Seller>(sellers_filePath, s, sellers);
    Database :: getInstance()->add_seller (*s);  // Updating the database 
}

void ECommerce :: addAdmin(Admin *a) {
    addUser<Admin>(admins_filePath, a, admins);
    Database :: getInstance()->add_admin (*a);  // Updating the database 
}


// template function to remove a User (Admin/Buyer/Seller)
template<typename type>
bool ECommerce :: removeUser (const std::string& userName, std::vector<type*>&vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) {
        if ((*it)->getUserName() == userName) {
            delete *it;     // Delete the dynamically allocated memory
            vec.erase(it);  // Erase the pointer from the vector
            return true;    // Return confirmation flag
        }
    }
    return false;
}


bool ECommerce :: removeBuyer(const std::string &userName) { 
    if (removeUser<Buyer>(userName, buyers)) {
        Database :: getInstance ()->remove_buyer (userName); // Remove the buyer from "buyers.json"
        return true; 
    }
    return false;
}


bool ECommerce :: removeSeller(const std::string &userName) { // Remove the seller from "sellers.json"
    if (removeUser<Seller>(userName, sellers)) { 
        Database :: getInstance ()->remove_seller (userName);
        return true;
    }
    return false;
}


bool ECommerce :: removeAdmin(const std::string &userName) { // Remove admin from "admins.json"
    if (removeUser<Admin>(userName, admins)) { 
        Database :: getInstance ()->remove_admin (userName);
        return true;
    }
    return false;
}
