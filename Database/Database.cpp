#include "Database.h"
// Header files location
#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"

// Initialize the instance
Database *Database::instance{nullptr};

// RETRIEVE DATA FROM DATABASE
template <typename T>
void Database ::loadData(std::vector<T *> &vec, const std::string &file_path)
{
    json j;
    try { 
        readFile  (file_path, j);
        // Parse the data into the vector
        for (auto &user : j["users"])
        {
            vec.emplace_back(T::fromJson(user)); // from json to actual object
        }
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION:" << ex.what() << endl;
    }
}

void Database::loadAdmins(std::vector<Admin *> &a)
{
    loadData<Admin>(a, admins_filePath);
}

void Database::loadBuyers(std::vector<Buyer *> &b)
{
    loadData<Buyer>(b, buyers_filePath);
}

void Database::loadSellers(std::vector<Seller *> &s)
{
    loadData<Seller>(s, sellers_filePath);
}

// UPDATE FILES
template <typename T>
void Database :: add_user(const T &obj, const std::string &file_path)
{
    json data;
    try { 
        readFile (file_path, data);
        data["users"].push_back(obj.toJson()); // Incorporate the new object 
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION:" << ex.what() << endl;
    }

    // After reading, write the new data to the file :)
    try { 
        writeToFile (file_path, data);
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION:" << ex.what() << endl;
    }

    // Now making a file to store products of the seller 
    data.clear();
    data["productIds"] = json :: array();
    try { 
        writeToFile ("./Database/Inventory/Sellers/" + obj.getUserName () + ".json", data);
    }
    catch (std::exception& ex) { 
        std::cout << "EXCEPTION:" << ex.what() << endl;
    }
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
    readFile (inventory_filePath, j);
    for (int i = 0; i < j["products"].size(); i++){
        Product* p = new Product ();
        inventory->addProduct(Product::fromJson (j["products"][i], p));
    }
}


void Database::updateInventory(Product* p) 
{
    json j;
    try {
        // Read the file first to prevent any data loss
        readFile(inventory_filePath, j);
        
        // Use a smart pointer to manage memory
        auto d = std::make_unique<json>();
        j["products"].push_back(*(p->toJson(d.get())));
        
        try {
            // Write to the file
            writeToFile(inventory_filePath, j);
        }
        catch (const std::exception& ex) {
            std::cout << "Write EXCEPTION: " << ex.what() << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Read or JSON EXCEPTION: " << ex.what() << std::endl;
    }
}

 

// Add productId to seller,s store 
void Database :: updateMyStore(const std::string& productId, const std::string &store_owner)
{
    json data; 
    try { 
        readFile ("./Database/Inventory/Sellers/" + store_owner + ".json", data);
        data["productIds"].push_back (productId);
        writeToFile ("./Database/Inventory/Sellers/" + store_owner + ".json", data);
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl; 
    }
}
