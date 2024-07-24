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

class Admin;
class Seller;
class Buyer;


class Database
{
private:
    static Database *instance;

    /*
        json json_admins;
        json json_buyers;
        json json_sellers;
        json json_inventory;
    */
   
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
    void loadData(std::vector<T *> &vec, const std::string &file_path);
    void loadAdmins(std::vector<Admin *> &a);
    void loadBuyers(std::vector<Buyer *> &b);
    void loadSellers(std::vector<Seller *> &s);

    // ADD USERS
    template <typename T>
    void add_user(const T &obj, const std::string &file_path); // General function to add a user from the JSON file
    void add_admin(const Admin &a);
    void add_buyer(const Buyer &b);
    void add_seller(const Seller &s);

    // REMOVE USERS
    void remove_user(const std::string &, const std::string &); // General function to remove a user from the JSON file
    void remove_admin(const std::string &user_name);
    void remove_buyer(const std::string &user_name);
    void remove_seller(const std::string &user_name);


    // INVENTORY METHODS 
    void updateMyStore(json &j, const std::string &store_owner);
};

#endif // _DATABASE_H_
