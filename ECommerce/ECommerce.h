#ifndef _ECOMMERCE_H_
#define _ECOMMERCE_H_

#include "./../Database/Database.h"

class ECommerce
{
    std::vector<Categories> categories;

public:
    static ECommerce *getInstance();
    static void releaseInstance();

    
    bool isUserNameTaken (const std::string&);
    User* login (const std::string&,  const std::string&);  
    User* searchUser (const std::string&);
    void addUser (User* );
    void removeUser (User* );
    Inventory* getInventory () const;
    void displayUsers () const;
    void loadData ();      
    
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
void inputCredentials ( std::string&,
                            std::string&,
                                std::string&,
                                     std::string&);  // Common credentials among all kind of users

// Template function for user sign-up
template <typename T, typename... Args>
T* userSignUp(const std::string& firstName,
                const std::string& lastName,
                    const std::string& userName,
                        const std::string& password, Args&&... args) {
    return new T(firstName, lastName, userName, password, std::forward<Args>(args)...);
}

#endif // _ECOMMERCE_H_ Singleton class