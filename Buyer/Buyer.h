#ifndef _BUYER_H_
#define _BUYER_H_

#include "../Person/Person.h"

class Buyer : public Person
{
public:
    Buyer();
    Buyer(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        // Buyer/Customer Functionalities

};

#endif // _BUYER_H_