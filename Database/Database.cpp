#include "Database.h"
// Header files location
#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"


void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Initialize the instance
Database *Database::instance{nullptr};

// General functions to read and write
    void Database :: readFile (const std::string& file_path, json& j)  {
        std::ifstream in (file_path, std::ios::in);
        if (!in.is_open()) { 
            throw std::runtime_error {"Could not open the file :("};
        } 
            in >> j;
            in.close();
    }
    // write function
    void Database :: writeToFile (const std::string& file_path, const json& j) { 
        std::ofstream out (file_path ,std::ios::trunc);
        if (!out.is_open()) { 
            throw std::runtime_error {"Could not open the file :("};
        }
            out << std :: setw(4) << j <<endl;
            out.close();
    }


void Database ::add_admin(const Admin &a)
{
    add_user(a, admins_filePath);
}

void Database ::add_buyer(const Buyer &b)
{
    add_user(b, buyers_filePath);
}

void Database ::add_seller(const Seller &s)
{
    add_user(s, sellers_filePath);
    // Now making a file to store products of the seller
    json data;
    data["productIds"] = json ::array();
    try {
        writeToFile("./Database/Inventory/Sellers/" + s.getUserName() + ".json", data);
    }
    catch (std::exception &ex) {
        std::cout << "EXCEPTION:" << ex.what() << endl;
    }
}

// General function to remove a user from the JSON file
void Database ::remove_user(const std::string &user_name, const std::string &file_path)
{
    json j;
    try {
        // Read the data that is already present in the file to prevent data loss 
        readFile (file_path, j);
        // Find and erase the user with the matching username
        for (auto it = j["users"].begin(); it != j["users"].end(); ++it)
        {
            if ((*it)["userName"] == user_name)
            {
                j["users"].erase(it);
                break; // Exit the loop after removing the user
            }
        }

        try {
            // Write the updated JSON back to the file
            writeToFile (file_path, j);
        }
        catch (std::exception& ex) {
            std::cout << "EXCEPTION: " << ex.what() << endl; 
        }
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION: " << ex.what() << endl; 
    }
}

void Database ::remove_admin(const std::string &user_name)
{
    remove_user(user_name, admins_filePath);
}

void Database ::remove_buyer(const std::string &user_name)
{
    remove_user(user_name, buyers_filePath);
}

void Database ::remove_seller(const std::string &user_name)
{
    remove_user(user_name, sellers_filePath);
}

// INVENTORY METHODS
void Database :: loadInventory(Inventory *inventory)
{
    json j; 
    try { 
        readFile (inventory_filePath, j);
        for (ssize_t i = 0; i < j["products"].size(); i++){
            Product* p = new Product ();
            inventory->loadInventory(Product::fromJson (j["products"][i], p));
        }
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl;
    }
}


// Add the product to centralized inventory
void Database :: addProductToAppInventory (Product* p) 
{
    json j;
    try {
        // Read the file first to prevent any data loss
        readFile(inventory_filePath, j);
        
        // Use a smart pointer to manage memory
        auto d = std::make_unique<json>();         
        j["products"].push_back(*(p->toJson(d.get())));
        
        // Write to the file
        writeToFile(inventory_filePath, j);
        
    }
    catch (const std::exception& ex) {
        std::cout << "Read or JSON EXCEPTION: " << ex.what() << std::endl;
    }
}


// Remove the product from Centralized inventory 
void Database :: removeProductFromAppInventory(const std::string& product_id) { 
    json j;
    try { 
        readFile(inventory_filePath, j);
        for (auto it = j["products"].begin(); it != j["products"].end(); ++it) { 
            if ((*it)["uniqueId"] == product_id) { 
                j["products"].erase(it);
                break; // Exit the loop once the product is found and removed
            }
        }
        writeToFile(inventory_filePath, j); 
    }
    catch (const std::exception& ex) { 
        std::cout << "EXCEPTION: " << ex.what() << std::endl; 
    }
}


 
// Add productId to seller,s store 
void Database :: addProductToMyList(const std::string& product_id, const std::string &store_owner)
{
    json data; 
    try { 
        readFile ("./Database/Inventory/Sellers/" + store_owner + ".json", data);
        // Add to my list 
        data["productIds"].push_back (product_id);
        writeToFile ("./Database/Inventory/Sellers/" + store_owner + ".json", data);
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl; 
    }
}

// Remove the productId from seller,s product list 
void Database :: removeProductFromMyList(const std::string& product_id, const std::string& store_owner) { 
    json data; 
    try { 
        readFile("./Database/Inventory/Sellers/" + store_owner + ".json", data);
        // Ensure the productIds field is an array
        if (data.contains("productIds") && data["productIds"].is_array()) {
            for (size_t i = 0; i < data["productIds"].size(); ++i) { 
                if (product_id == data["productIds"][i]) { 
                    // Remove the product from the list using iterator
                    data["productIds"].erase(data["productIds"].begin() + i);
                    break; 
                }
            }
        }
        writeToFile("./Database/Inventory/Sellers/" + store_owner + ".json", data);
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION: " << ex.what() << std::endl; 
    }
}

