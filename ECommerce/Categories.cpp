#include "Categories.h"

// constructor and destructor
Categories::Categories(std::string category)
{
    this->category = category;
    subCategory.resize(4);

    // sectction of subcategories according to the category being passed in the constructor
    if (category == "Electronics")
    {
        subCategory[0] = "Mobiles and Tablets";
        subCategory[1] = "Laptops and Computers";
        subCategory[2] = "Smart Watches and Cameras";
        subCategory[3] = "Accessories";
    }
    else if (category == "Fashion and Apparel")
    {
        subCategory[0] = "Clothing";
        subCategory[1] = "Footwear";
        subCategory[2] = "Accessories";
        subCategory[3] = "Jewellery and Watches";
    }
    else if (category == "Food and Groceries")
    {
        subCategory[0] = "Fruits and Vegetables";
        subCategory[1] = "Dairy and Bakery";
        subCategory[2] = "Beverages";
        subCategory[3] = "Snacks and Packaged Foods";
    }
    else if (category == "Home and Furniture")
    {
        subCategory[0] = "Furniture";
        subCategory[1] = "Home Decor";
        subCategory[2] = "Kitchen and Dining";
        subCategory[3] = "Appliances";
    }
    else if (category == "Books, Music, Games, Movies")
    {
        subCategory[0] = "Books";
        subCategory[1] = "Music";
        subCategory[2] = "Games";
        subCategory[3] = "Movies and TV Shows";
    }
    else if (category == "Sports")
    {
        subCategory[0] = "Fitness";
        subCategory[1] = "Outdoor";
        subCategory[2] = "Indoor";
        subCategory[3] = "Sports Accessories";
    }
}

Categories::~Categories()
{
}

// getters
std::string Categories ::getCategory(){}
std::vector<std::string> Categories ::getSubCategory(){}
// display categories and subcategories
void Categories ::displayCategories(){
    static int i = 1;
    std::cout<< i << ". " << category << std::endl;
    i++;
    if (i==7)
    {
        i=1;
    }
    
}
void Categories ::displaySubCategories(){
    std::cout << "Subcategories of " << category << " are: " << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << i+1 << ". " << subCategory[i] << std::endl;
    }
}

//assignment operator

Categories Categories:: operator = (Categories cat){
    category = cat.category;
    subCategory = cat.subCategory;
    return *this;
}