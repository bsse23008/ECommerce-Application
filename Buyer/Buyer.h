#ifndef _BUYER_H_
#define _BUYER_H_

#include "../User/User.h"

class Buyer : public User
{
public:
    Buyer();
    ~Buyer () {
        cout << "\nBuyer destructor called!" << endl;
    }
    Buyer(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        // Buyer/Customer Functionalities

        static Buyer* fromJson (json& j); 
        json toJson () const ;
};

#endif // _BUYER_H_