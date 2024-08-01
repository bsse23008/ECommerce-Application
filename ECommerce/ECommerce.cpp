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

    for (User* user : users) {
        delete user;
    }
    /*
        // The pointed-to memory has been released (from heap).
        //  Now clear the addresses stored in the vector as well using clear() method :)
    */

    users.clear();    
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



User* ECommerce :: login (const std::string& user_name,  const std::string& password) { 

    std::vector<User*> :: iterator it = users.begin(); 
    for ( ; it!=users.end(); ++it) { 
        if (user_name == (*it)->getUserName() && password == (*it)->getPassword()) { 
            return *it; 
        }
    }
    return nullptr; 
}



void ECommerce :: loadData () { 
    // Loading Users (buyers, sellers, admins)
    try { 
        Database :: getInstance()->loadData (users, users_file_path);
    }
    catch (std::exception& ex) { 
        std::cout << "Exception: " << ex.what() << std::endl; 
    }

    // Loading Inventory 
    try { 
        Database :: getInstance()->loadInventory (inventory);
    }
    catch (std::exception& ex) { 
        std::cout << "Exception: " << ex.what() << std::endl; 
    }
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
    for (size_t i=0; i<j["productIds"].size(); i++) { 
        Product* p = inventory->getReference (j["productIds"][i]);
        if (p)
            seller->loadProducts (p); // If p is not null, only then add 
    }
}
