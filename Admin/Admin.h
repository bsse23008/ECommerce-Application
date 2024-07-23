#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "../User/User.h"
#include "../Database/Database.h"

class Admin : public User
{
public:
    Admin();
    ~Admin () {
        cout << "\nAdmin destructor called!" << endl;
    }
    Admin(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        static Admin* fromJson (json& j); 
        json toJson ();

        void adminControls () { 

        }

        void deleteMyAccount () { 
            // Database :: getInstance ()->remove_admin (this->toJson()); 
            delete this; 
        }
        // Admin Functionalities

};

#endif // _ADMIN_H_