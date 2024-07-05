#ifndef _SELLER_H_
#define _SELLER_H_

#include "../Person/Person.h"

class Seller : public Person
{
public:
    Seller();
    Seller(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        // Seller Functionalities

};

#endif // _SELLER_H_