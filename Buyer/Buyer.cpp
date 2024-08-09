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
void Buyer::setCategory(const std::vector<Categories> &categories)
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
// selecting the categories and subcategories
void Buyer::selectCategory()
{
    int count = 0, exit = 0, inputCheck = 0;
    std::vector<int> cat;
    do
    {
        std::cout << "Categories:-\n";
        // displaying only unselected categories
        for (int i = 0; i < categories.size(); i++)
        {
            if (isCategoryPresent(categories[i].getCategory()))
            {
                continue;
            }
            inputCheck++;
            std::cout << i + 1 << ". " << categories[i].getCategory() << std::endl;
            cat.push_back(i);
        }
        // checking if all categories are selected or not
        if (inputCheck != 0)
        {
            int choice;
            bool flag = false;
            do
            {
                // taking input of desired category
                std::cout << "Enter the category number you are interested in: ";
                std::cin >> choice;
                for (int h = 0; h < cat.size(); h++)
                {
                    // checking if selected category is valid or not
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
            std::cin >> exit;
            count++;
        }
        else
        {
            std::cout << " You have already selected all of the categories.\n";
            break;
        }
    } while (exit > 0);
}

// void Buyer::selectSubCategory()
// {

//     for (size_t i = 0; i < preferredCategory.size(); i++)

//     {

//         Categories category("");
//         int count = 0, exit = 0;
//         do
//         {
//             std ::cout << " Category : " << preferredCategory[i]<<std::endl;
//             std::cout << " Sub Categories :-\n";
//             bool check;
//             std::vector<int> subCat;
//             int inputCheck = 0;
//             // displaying only unselected subcategories
//             for (size_t j = 0; j < 4; j++)
//             {
//                 for (int h = 0; h < subCat.size(); h++)
//                 {
//                     if (j == subCat[h])
//                     {
//                         check = false;
//                         break;
//                     }
//                     check = true;
//                 }
//                 if (!check)
//                 {
//                     continue;
//                 }
//                 inputCheck++;
//                 Categories category();
//                 category = findCategory(preferredCategory[i]);
//                 std::cout << j + 1 << ". " << category.getSubCategory()[j] << std::endl;
//             }
//             // checking if all subcategories are selected or not
//             if (inputCheck != 0)
//             {
//                 int choice;
//                 bool flag = false;
//                 do
//                 {
//                     // taking input of desired  sub category
//                     std::cout << "Enter the sub-category you want to select :";
//                     std::cin >> choice;
//                     int v = 0;
//                     for (int k = 0; k < subCat.size(); k++)
//                     {
//                         std::cout << " in the check loop\n";
//                         // checking if selected sub category is valid or not
//                         if ((choice - 1) == subCat[k])
//                         {
//                             v = 1;
//                             flag = false;
//                             break;
//                         }
//                     }

//                     if (v == 0)
//                     {
//                         flag = true;
//                         subCat.push_back((choice - 1));
//                         setPreferredSubCategory(category.getSubCategory()[(choice - 1)]);
//                     }
//                     else if (subCat.size() == 0)
//                     {
//                         flag = true;
//                     }
//                     else if (!flag)
//                     {
//                         std::cout << "Invalid choice. Please try again!" << std::endl;
//                     }

//                 } while (!flag);
//                 count++;
//                 std::cout << "Enter a positive integer to continue selecting subcategories of this category and negative integer to stop : ";
//                 std::cin >> exit;
//             }
//             else
//             {
//                 std::cout << "You have already selected all of the subcategories of this category.";
//                 break;
//             }
//         } while (exit > 0);
//         std::cout << "===============================================\n";
//     }
// }

// Categories Buyer::findCategory(std::string category)
// {
//     Categories cat("");
//     for (size_t i = 0; i < categories.size(); i++)
//     {
//         if (categories[i].getCategory() == category)
//         {
//             cat = categories[i];
//         }
//     }
//     return cat;
// }
// checking if cattegory is already present
bool Buyer::isCategoryPresent(std::string category)
{
    for (int i = 0; i < preferredCategory.size(); i++)
    {
        if (preferredCategory[i] == category)
            return true;
    }
    return false;
}


json& Buyer :: toJson ( json& j ) const { 
    // json j; 
    j["type"] = "Buyer"; // flag to differentiate between users
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}


void Buyer :: dashBoard () { 

    cout << "\nBuyer :: dashBoard\n";

}