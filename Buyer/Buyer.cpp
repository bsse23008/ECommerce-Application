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
void Buyer::setPreferredCategory(std::string preferredCategory)
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
// selecting the categories
void Buyer::selectCategory()
{
    int k = 0, j = 0;
    std::vector<int> cat;
    do
    {
        for (int i = 0; i < categories.size(); i++)
        {
            if (isCategoryPresent(categories[i].getCategory()))
            {
                continue;
            }
            categories[i].displayCategories();
            cat.push_back(i);
        }

        int choice;
        bool flag = false;
        do
        {
            std::cout << "Enter the category number you are interested in: ";
            std::cin >> choice;
            for (int h = 0; h < cat.size(); h++)
            {
                if (cat[h] == (choice - 1))
                {
                    flag = true;
                    setPreferredCategory(categories[choice - 1].getCategory());
                    cat.erase(cat.begin() + h);
                    break;
                }
            }
            if (!flag)
            {
                std::cout << "Invalid choice. Please try again!" << std::endl;
            }
        } while (!flag);
        std::cout << "Enter positive integer to continue selecting the categories and negative integer to stop : ";
        std::cin >> j;
        k++;
    } while (k != 7 || j > 0);
}

// checking if cattegory is already present
bool Buyer::isCategoryPresent(std::string category)
{
    for (int i = 0; i < categories.size(); i++)
    {
        if (preferredCategory[i] == category)
            return true;
    }
    return false;
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