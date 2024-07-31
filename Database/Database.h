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

const std::string inventory_filePath = "./Database/Inventory/inventory.json";
const std::string users_file_path = "./Database/Users/users.json";

// class User;

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

    // General functions to read and write :)
    void readFile(const std::string &, json &);
    void writeToFile(const std::string &, const json &);


    void loadData(std::vector<User *>&, const std::string&);


    // ADD USERS
        /* addUser <Seller> (seller)*/
        /* addUser <Buyer> (buyer)*/
        /* addUser <Admin> (admin)*/

    /*
    void addUser (const std::vector<User*>& users) { 
        json j; 
        j["users"] = json::array();
        for (auto it=users.begin(); it!=users.end(); ++it) { 
            json* temp = nullptr; 
            *temp = (*it)->toJson(*temp);
            j["users"].emplace_back (*temp);
        }

        // Write to file :)
        try { 
            writeToFile(users_file_path, j);
        } catch (std::exception& ex) { 
            cerr << "Exception: " << ex.what() << endl; 
        }
    }
    */

    // template <typename T> 
    void addUser (User* newUser) { 
        try {
            json data; 
            readFile (users_file_path, data);
            json temp; 
            temp = newUser->toJson(temp);
            data["users"].push_back(temp); // Add the user to json array 
            writeToFile (users_file_path, data);
        }
        catch (std::exception& ex) { 
            std::cerr << "EXCEPTION: " << ex.what() << std::endl; 
        }
    }


    void remove_user (const User*);

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
