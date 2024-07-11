#include "Buyer.h"

Buyer ::Buyer() : User()
{
}

Buyer ::Buyer(
    const std::string &first,
    const std::string &last,
    const std::string &user_name,
    const std::string &pass) : User(first, last, user_name, pass)
{
}

/// setters
void Buyer::setCategoty(const std::vector<Categories> &)
{
    this->categories = categories;
}
void Buyer::setPreferredCategory(std::string &preferredCategory)
{
    this->preferredCategory.push_back(preferredCategory);
}
void Buyer::setPreferredSubCategory(std::string &preferredSubCategory)
{
    this->preferredSubCategory.push_back(preferredSubCategory);
}
// getters
std::vector<std::string> Buyer::getPreferredCategory()
{
    return this->preferredCategory;
}
std::vector<std::string> Buyer::getPreferredSubCategory()
{
    return this->preferredSubCategory;
}

Buyer *Buyer ::fromJson(json &j)
{
    return new Buyer(j["firstName"], j["lastName"], j["userName"], j["password"]);
}
// setter
void Buyer ::setCategoty(const std::vector<Categories> &categories)
{
    this->categories = categories;
}

json Buyer ::toJson()
{
    json j;
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j;
}