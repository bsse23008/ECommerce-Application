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
    // j["users"];
    std::ifstream read_file(file_path, std::ios::in);
    if (read_file.is_open())
    {
        read_file >> j;
        read_file.close();
        // Parse the data into the vector
        for (auto &user : j["users"])
        {
            vec.emplace_back(T::fromJson(user)); // from json to actual object
        }
    }
    else
    {
        std::cerr << "Error opening the file: " << file_path << std::endl;
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
    data["users"];
    std::ifstream in(file_path, std::ios::in); // Read the data -> already present in the file
    if (in.is_open()){
        in >> data;
        in.close();
        data["users"].push_back(obj.toJson()); // Incorporate the new obj

        // After reading, write the new data to the file :)
        std::ofstream out(file_path, std::ios::trunc);
        out << std::setw(4) << data << std::endl;
        out.close();
    }
    else{
        cerr << "Could not open the file! " << endl;
    }

    // Now making a file to store products of the seller 
    data.clear();
    std::ofstream out ("./Database/Inventory/Sellers/" + obj.getUserName () + ".json", std::ios::out);
    if (!out.is_open()) { 
        cerr << "Could not open the file : (" << endl;
        return;
    }

    data["productIds"] = json :: array();
    out << std::setw(4) << data << std::endl; 
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
}

// General function to remove a user from the JSON file
void Database ::remove_user(const std::string &user_name, const std::string &file_path)
{
    json j;
    std::ifstream IN(file_path, std::ios::in);
    if (IN.is_open())
    {
        IN >> j;
        IN.close();
        // Find and erase the user with the matching username
        for (auto it = j["users"].begin(); it != j["users"].end(); ++it)
        {
            if ((*it)["userName"] == user_name)
            {
                j["users"].erase(it);
                break; // Exit the loop after removing the user
            }
        }
        // Write the updated JSON back to the file
        std::ofstream OUT(file_path, std::ios::trunc);
        if (OUT.is_open())
        {
            OUT << std::setw(4) << j << std::endl;
            OUT.close();
        }
        else
        {
            cerr << "Could not open the file for writing!" << endl;
        }
    }
    else
    {
        cerr << "Could not open the file for reading!" << endl;
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
    std::ifstream IN(inventory_filePath, std::ios::in);
    if (!IN.is_open()) {
        throw std::runtime_error{"Could not open the inventory file :("};
    }
    json j;
        IN >> j;
        IN.close();
    for (int i = 0; i < j["products"].size(); i++){
        Product* p = new Product ();
        inventory->addProduct(Product::fromJson (j["products"][i], p));
    }
}


void Database :: updateInventory (Product* p) 
{ 
    std::ifstream IN(inventory_filePath, std::ios::in); // Read the inventory that is already present -> to prevent any data loss
    if (!IN.is_open()) {
        /*
        json j; 
        j["products"] = json :: array ();
        json* d = new json; 
        j["products"].push_back (*(p->toJson(d))); 
            // Write to the file 
                std::ofstream out(inventory_filePath, std::ios::trunc);
                out << std::setw (4) << j << endl; 
                out.close();
        delete d; 
        */         
        throw std::runtime_error{"Could not open the inventory file :("};
    }
    json j;
        IN >> j;                    /*..........*/
        IN.close();
        json* d = new json; 
        j["products"].push_back (*(p->toJson(d))); 
    
    // Write to the file 
    std::ofstream out(inventory_filePath, std::ios::trunc);
    out << std::setw (4) << j << endl; 
    out.close();
    delete d; 
}
 

// Add productId to seller,s store 
void Database :: updateMyStore(const std::string& productId, const std::string &store_owner)
{
    std::ifstream in ("./Database/Inventory/Sellers/" + store_owner + ".json", std::ios::in); // Read the already present file 
    if (!in.is_open()) { 
        cerr << "Error opening the file!" << endl;
        return; 
    } 
        json data;
        in >> data; 
        in.close();
        data["productIds"].push_back (productId);

    std::ofstream out("./Database/Inventory/Sellers/" + store_owner + ".json", std::ios::trunc);
    out << std::setw (4) << data << endl; 
    out.close();
}
