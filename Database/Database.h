#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "../nlohmann/json.hpp"
using json = nlohmann :: json; 
#include <fstream>
#include <string> 
#include <iostream>
// Header files location
#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"
using std::cout; 
using std::endl; 
using std::cerr; 

// File Paths for convenience 
const std::string buyers_filePath = "./Database/Users/buyers.json";
const std::string sellers_filePath = "./Database/Users/sellers.json";
const std::string admins_filePath = "./Database/Users/admins.json";


class Database {
private: 
    static Database* instance; 
    json json_admins; 
    json json_buyers; 
    json json_sellers; 
    json json_inventory;  

    Database() = default;
    Database(const Database& d) = delete; 
    ~Database() = default;

public: 
    static Database* getInstance() {
        if (!instance) { 
            instance = new Database();
        }
        return instance;
    }

    static void releaseInstance() { 
        delete instance;
        instance = nullptr; // Make sure the instance pointer is set to nullptr after deleting
    }

    template <typename T>
    void loadData(std::vector<T*>& vec, json& j, const std::string& file_path);
    void loadAdmins(std::vector<Admin*>& a);
    void loadBuyers(std::vector<Buyer*>& b);
    void loadSellers(std::vector<Seller*>& s);

    void update_users_file(const json& j, const std::string& file_path); 
    void add_admin(const json& j);
    void add_buyer(const json& j);
    void add_seller(const json& j);

    void remove_user(json& j, const std::string& username); // General function
    void remove_admin(const std::string& username);
    void remove_buyer(const std::string& username);
    void remove_seller(const std::string& username);

    void updateMyStore(json& j, const std::string& store_owner);
};

#endif // _DATABASE_H_
