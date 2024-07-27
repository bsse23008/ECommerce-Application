#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "../nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include <sstream>
#include <iostream>
#include <cstdlib>  // Needed for system() function

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using json = nlohmann ::json;

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
    static Database *getInstance()
    {
        if (!instance)
        {
            instance = new Database();
        }
        return instance;
    }

    static void releaseInstance()
    {
        delete instance;
        instance = nullptr;
    }

    // RETRIEVE DATA FROM DATABASE
    template <typename T>
    void loadData(std::vector<T *> &vec, const std::string &file_path)
    {
        json j;
        try
        {
            readFile(file_path, j);
            // Parse the data into the vector
            for (auto &user : j["users"])
            {
                vec.emplace_back(T::fromJson(user)); // from json to actual object
            }
        }
        catch (std::exception &ex)
        {
            std::cout << "EXCEPTION:" << ex.what() << endl;
        }
    }

    // General functions to read and write :)
    void readFile(const std::string &, json &);
    void writeToFile(const std::string &, const json &);

    // ADD USERS
    template <typename T>
    void add_user(const T &obj, const std::string &file_path)
    {
        json data;
        try {
            readFile(file_path, data);
            data["users"].push_back(obj.toJson()); // Incorporate the new object

            // After reading, write the new data to the file :)
            writeToFile (file_path, data);
        }
        catch (std::exception &ex) {
            std::cout << "EXCEPTION:" << ex.what() << endl;
        }
    }

    void add_admin(const Admin &a);
    void add_buyer(const Buyer &b);
    void add_seller(const Seller &s);

    // REMOVE USERS
    void remove_user(const std::string &, const std::string &); // General function to remove a user from the JSON file
    void remove_admin(const std::string &);
    void remove_buyer(const std::string &);
    void remove_seller(const std::string &);

    // INVENTORY METHODS
    void loadInventory(Inventory *);
    void addProductToAppInventory (Product *);
    void removeProductFromAppInventory (const std::string& );
    // Seller inventory methods
    void addProductToMyList(const std::string &, const std::string &);
    void removeProductFromMyList (const std::string&, const std::string&);
};

void clear_screen();

#endif // _DATABASE_H_
