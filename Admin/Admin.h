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
        virtual void dashBoard () override;
};

#endif // _ADMIN_H_