#ifndef _BUYER_H_
#define _BUYER_H_

#include "../User/User.h"

class Buyer : public User
{
public:
    Buyer();
    virtual ~Buyer () {
        cout << "\nBuyer destructor called!" << endl;
    }

    virtual void dashBoard () override { 

    }

    Buyer(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        // Buyer/Customer Functionalities

        static Buyer* fromJson (json& j); 
        virtual json& toJson (json& j) const override;

};

#endif // _BUYER_H_