#ifndef _ECOMMERCE_H_
#define _ECOMMERCE_H_

#include "./../Database/Database.h"

class ECommerce
{
public:
    static ECommerce* getInstance ();
    static void releaseInstance ();

    
    bool isUserNameTaken (const std::string& userName)  {
        std::vector<User*> :: const_iterator it; 
        // auto it = users.cbegin();

        for (it = users.begin(); it!=users.end(); ++it) { 
            if ((*it)->getUserName() == userName) { 
                return true; 
            }
        }
        return false; 
    }

        User* searchUser (const std::string& userName) { // template function to search any user 

            for (auto it = users.begin(); it != users.end(); ++it)  {
                if (userName == (*it)->getUserName()) { 
                    return *it; 
                }
            }
            return nullptr; 
        }
    
        void addUser (User* user) { 
            Database :: getInstance ()->addUser (user); 
            users.emplace_back (user);
        }

        void removeUser (User* user) { 
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

    Inventory* getInventory () const { 
        return inventory; 
    }

    void loadSellerInventory (Seller*);
    void loadData ();        
    User* login (const std::string&,  const std::string&);  


    void displayUsers () const { 
        std::vector<User*> :: const_iterator it; 
        for (it = users.begin(); it!= users.end(); ++it) { 
            cout << "_________________________________\n";
            (*it)->display(); 
        }
    }

private:

    ECommerce();
    ~ECommerce ();
    ECommerce(const ECommerce &) = delete;
    
    Inventory* inventory; 
    std::vector<User*> users;
};

// Global functions
void SignUp();
void Login (); 

void inputCredentials ( std::string&, std::string&, std::string&, std::string&);  // Common credentials among all kind of users
Admin* adminSignUp (const std::string&, const std::string&, const std::string&, const std::string&);
Buyer* buyerSignUp (const std::string&, const std::string&, const std::string&, const std::string&);
Seller* sellerSignUp (const std::string&, const std::string&, const std::string&, const std::string&);

#endif // _ECOMMERCE_H_ Singleton class