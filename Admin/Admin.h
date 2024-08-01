#ifndef _ADMIN_H_
#define _ADMIN_H_
#include "../User/User.h"

class ECommerce;

class Admin : public User
{
public:
    Admin();
    virtual ~Admin () {
        cout << "\nAdmin destructor called!" << endl;
    }

    virtual void dashBoard () override { 

    }

    Admin(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        static Admin* fromJson (json& j); 
        virtual json& toJson (json& j) const override;
        void deleteMyAccount () { 
            
        }

        // Admin Functionalities
};

void adminControls (Admin* a);

#endif // _ADMIN_H_