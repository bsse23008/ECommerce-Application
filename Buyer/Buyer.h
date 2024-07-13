#ifndef _BUYER_H_
#define _BUYER_H_

#include "../User/User.h"
#include <vector>
#include "../Summer-Project/ECommerce/Categories.h";
class Buyer : public User
{
    std::vector<Categories> categories;
    std::vector<std::string> preferredCategory;
    std::vector<std::string> preferredSubCategory;

public:
    Buyer();
    ~Buyer()
    {
        cout << "\nBuyer destructor called!" << endl;
    }
    Buyer(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

    /// setters
    void setCategoty(const std::vector<Categories> &);
    void setPreferredCategory(std::string );
    void setPreferredSubCategory(std::string &);
    // getters
    std::vector<std::string> getPreferredCategory();
    std::vector<std::string> getPreferredSubCategory();
    //checking if cattegory is already present
    bool isCategoryPresent(std::string);
    //selecting the categories and subcategories
    void selectCategory();
    void selectSubCategory();
    Categories findCategory(std::string);
    // json functions
    static Buyer *fromJson(json &j);
    json toJson();
};

#endif // _BUYER_H_