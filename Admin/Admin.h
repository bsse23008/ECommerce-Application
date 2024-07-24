#ifndef _ADMIN_H_
#define _ADMIN_H_
#include "../User/User.h"

class ECommerce;

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
        json toJson () const;

        void deleteMyAccount () { 
            
        }

        // Admin Functionalities
};

void adminControls (Admin* a);

#endif // _ADMIN_H_