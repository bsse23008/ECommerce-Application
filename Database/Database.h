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
#include <iterator>

#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using json = nlohmann ::json;


// Global variables for file-paths :)
const std::string inventory_filePath = "./Database/Inventory/inventory.json";
const std::string users_file_path = "./Database/Users/users.json";

class Database {
private:
    static Database *instance;
    Database() = default;
    Database(const Database &d) = delete;
    ~Database() = default;

public:
    static Database *getInstance();
    static void releaseInstance(); 


    // General functions to read and write :)
    void readFile(const std::string &, json &);
    void writeToFile(const std::string &, const json &);
    
    // LOAD USERS
    void loadData(std::vector<User *>&, const std::string&);
    // ADD USERS
    void addUser (const User* newUser);
    // REMOVE USERS
    void remove_user (const User*);

    // INVENTORY METHODS
    void loadInventory(Inventory *);
    void addProductToAppInventory (Product *);
    void removeProductFromAppInventory (const std::string& );
    // Seller inventory methods
    void createNewFileForSeller (const std::string&);
    void loadSellerProductList (json&, const std::string&);
    void addProductToMyList(const std::string &, const std::string &);
    void removeProductFromMyList (const std::string&, const std::string&);
};

#endif // _DATABASE_H_
