#include "ECommerce.h"

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


// template function to add a User (Admin/Buyer/Seller)
template <typename type> 
void ECommerce :: addUser (const std::string& filePath, type* obj, std::vector<type*>& vec) {
    vec.push_back(obj); 
}

void ECommerce :: addBuyer(Buyer *b) { 
    addUser<Buyer> (buyers_filePath , b, buyers);
    Database :: getInstance()->add_buyer (b->toJson());  // Updating the database 
}

void ECommerce :: addSeller(Seller *s) {
    addUser<Seller>(sellers_filePath, s, sellers);
    Database :: getInstance()->add_seller (s->toJson());  // Updating the database 
}

void ECommerce :: addAdmin(Admin *a) {
    addUser<Admin>(admins_filePath, a, admins);
    Database :: getInstance()->add_admin (a->toJson());  // Updating the database 
}


// template function to remove a User (Admin/Buyer/Seller)
template<typename type>
bool ECommerce :: removeUser (const std::string& filePath, const std::string& userName, std::vector<type*>&vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) {
        if ((*it)->getUserName() == userName) {
            vec.erase(it);
            return true;  // confirmation flag
        }
    }
    return false;
}


bool ECommerce :: removeBuyer(const std::string &userName) { 
    if (removeUser<Buyer>(buyers_filePath, userName, buyers)) {
        Database :: getInstance ()->remove_buyer (userName); // Remove the buyer from "buyers.json"
        return true; 
    }
    return false;
}


bool ECommerce :: removeSeller(const std::string &userName) { // Remove the seller from "sellers.json"
    if (removeUser<Seller>(sellers_filePath, userName, sellers)) { 
        Database :: getInstance ()->remove_seller (userName);
        return true;
    }
    return false;
}


bool ECommerce :: removeAdmin(const std::string &userName) { // Remove admin from "admins.json"
    if (removeUser<Admin>(admins_filePath, userName, admins)) { 
        Database :: getInstance ()->remove_admin (userName);
        return true;
    }
    return false;
}
