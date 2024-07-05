#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "../Person/Person.h"

class Admin : public Person
{
public:
    Admin();
    Admin(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

        // Admin Functionalities

};

#endif // _ADMIN_H_