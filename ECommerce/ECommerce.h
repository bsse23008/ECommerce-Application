#ifndef _ECOMMERCE_H_
#define _ECOMMERCE_H_

#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"
#include "Categories.h"
// File Paths for convenience
const std::string buyers_filePath = "Database/buyers.json";
const std::string sellers_filePath = "Database/sellers.json";
const std::string admins_filePath = "Database/admins.json";

class ECommerce
{
    std::vector<Categories> categories;

public:
    static ECommerce *getInstance();
    static void releaseInstance();

    template <typename type>
    void retrieveData(const std::string &, std::vector<type *> &); // template function to retrieve data
    void retrieveBuyers();
    void retrieveSellers();
    void retrieveAdmins();

    template <typename type>
    void updateFile(const std::string &, std::vector<type *> &); // template function to update the files

    template <typename type>
    bool isUserNameTaken(const std::string &, const std::vector<type *> &);

    // loading the categories
    void loadCategories();

    // Add/SignUp functions
    template <typename type>
    void addUser(const std::string &, type *, std::vector<type *> &); // template function to add a new user
    void addBuyer(Buyer *b);
    void addSeller(Seller *p);
    void addAdmin(Admin *a);

    // Remove
    template <typename type>
    bool removeUser(const std::string &, const std::string &, std::vector<type *> &); // template function to remove a user
    bool removeSeller(const std::string &userName);
    bool removeBuyer(const std::string &userName);
    bool removeAdmin(const std::string &userName);

    // Login functions
    template <typename type>
    type *isLoggedIn(const std::string &, const std::string &, std::vector<type *>); // template function to login
    Buyer *isBuyerLoggedIn(const std::string &, const std::string &);
    Seller *isSellerLoggedIn(const std::string &, const std::string &);
    Admin *isAdminLoggedIn(const std::string &, const std::string &);

    void signUp();
    Admin *adminSignUp(const std::string &, const std::string &, const std::string &, const std::string &);
    Buyer *buyerSignUp(const std::string &, const std::string &, const std::string &, const std::string &);
    Seller *sellerSignUp(const std::string &, const std::string &, const std::string &, const std::string &);

    template <typename T>
    void inputCredentials(std::string &, std::string &, std::string &, std::string &, const std::vector<T *> &);

private:
    ECommerce() = default;
    ~ECommerce();

    ECommerce(const ECommerce &) = delete;
    std::vector<Buyer *> buyers;
    std::vector<Seller *> sellers;
    std::vector<Admin *> admins;
};

// Global functions
void inputCredentials(std::string &, std::string &);
void login();

#endif // _ECOMMERCE_H_ Singleton class