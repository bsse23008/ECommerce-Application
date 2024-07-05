#ifndef _MODULES_H_
#define _MODULES_H_

#include "./Admin/Admin.h"
#include "./Buyer/Buyer.h"
#include "./Seller/Seller.h"

class Module
{
public:

    Module () = default; 
    ~Module () { }

    void adminModule();
    void buyerModule();
    void sellerModule();

    bool login (const std::string& , const std::string&);
    void signUp (const std::string&, const std::string&, const std::string&,  const std::string&);
};

#endif // _MODULES_H_