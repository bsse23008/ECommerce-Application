#include "ECommerce.h"


ECommerce :: ECommerce() : inventory (nullptr) { 
    inventory = new Inventory();
}

// Release the dynamically allocated memory
ECommerce ::~ECommerce()
{
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
void ECommerce ::releaseInstance()
{
    delete getInstance();
}



bool ECommerce :: isUserNameTaken (const std::string& userName)  {
        std::vector<User*> :: const_iterator it; 
        // auto it = users.cbegin();

        for (it = users.begin(); it!=users.end(); ++it) { 
            if ((*it)->getUserName() == userName) { 
                return true; 
            }
        }
        return false; 
    }

        User* ECommerce :: searchUser (const std::string& userName) { // template function to search any user 

            for (auto it = users.begin(); it != users.end(); ++it)  {
                if (userName == (*it)->getUserName()) { 
                    return *it; 
                }
            }
            return nullptr; 
        }
    
        void ECommerce :: addUser (User* user) { 
            Database :: getInstance ()->addUser (user); 
            users.emplace_back (user);
        }

        void ECommerce :: removeUser (User* user) { 
            std::vector<User*> :: iterator it = users.begin();
            
            while (it != users.end()) { 
                if ((*it) == user) { 
                    Database::getInstance()->remove_user(user); // Ye dekhna pare ga 
                    delete *it;
                    users.erase(it);
                }
                ++it; 
            }
        }

    Inventory* ECommerce :: getInventory () const { 
        return inventory; 
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


void ECommerce :: displayUsers () const { 
        std::vector<User*> :: const_iterator it; 
        for (it = users.begin(); it!= users.end(); ++it) { 
            cout << "_________________________________\n";
            (*it)->display(); 
        }
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



const User* ECommerce :: getSellerReference (const std::string& sellerId) const { 
    for (const auto& u : users) { 
        if (u->getUserName() == sellerId) { 
            return u;
        }
    }
    return nullptr;
}

