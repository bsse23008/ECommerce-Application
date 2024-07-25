#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "../nlohmann/json.hpp"
using json = nlohmann ::json;
#include <fstream>
#include <string>
#include <iostream>

using std::cerr;
using std::cout;
using std::cin; 
using std::endl;

// File Paths for convenience
const std::string buyers_filePath = "./Database/Users/buyers.json";
const std::string sellers_filePath = "./Database/Users/sellers.json";
const std::string admins_filePath = "./Database/Users/admins.json";
const std::string inventory_filePath = "./Database/Inventory/inventory.json";

class Admin;         
class Seller;
class Buyer;
class Inventory; 
class Product; 

class Database  
{
private:
    static Database *instance;   
    Database() = default;
    Database(const Database &d) = delete;
    ~Database() = default;

public:
    static Database *getInstance() {
        if (!instance) {
            instance = new Database();
        }
        return instance;
    }

    static void releaseInstance() {
        delete instance;
        instance = nullptr;
    }

    // LOAD DATA
    template <typename T>
    void loadData(std::vector<T *> &, const std::string &);
    void loadAdmins(std::vector<Admin *> &a);
    void loadBuyers(std::vector<Buyer *> &b);
    void loadSellers(std::vector<Seller *> &s);

    // ADD USERS
    template <typename T>
    void add_user(const T &, const std::string &); // General function to add a user from the JSON file
    void add_admin(const Admin &a);
    void add_buyer(const Buyer &b);
    void add_seller(const Seller &s);

    // REMOVE USERS
    void remove_user(const std::string &, const std::string &); // General function to remove a user from the JSON file
    void remove_admin(const std::string &);
    void remove_buyer(const std::string &);
    void remove_seller(const std::string &);


    // INVENTORY METHODS 
    // void loadSellerInventory (Inventory*);
    void loadInventory (Inventory*);
    void updateInventory (Product*);
    void updateMyStore(const std::string&, const std::string&);

};

#endif // _DATABASE_H_
