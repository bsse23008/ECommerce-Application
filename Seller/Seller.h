#ifndef _SELLER_H_
#define _SELLER_H_

#include "../User/User.h"

class Seller : public User
{
public:
    Seller();
    ~Seller () {
        cout << "\nSeller destructor called!" << endl;
    }
    Seller(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        static Seller* fromJson (json& j); 
        json toJson ();

        // Seller Functionalities
};

#endif // _SELLER_H_