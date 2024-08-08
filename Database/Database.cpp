#include "Database.h"


// One instance in the whole APP
Database* Database :: getInstance() {
    if (!instance) {
        instance = new Database();
    }
    return instance;
}


// Delete the instance
void Database :: releaseInstance() {
    delete instance;
    instance = nullptr;
}



    void Database :: loadData(std::vector<User *> &vec, const std::string &file_path) {
        json j;
        try
        { 
            // Reading function could potentially throw an exception :)
            readFile(file_path, j);

            // Parse the data into the vector
            for (auto &user : j["users"]) {
                if (user["type"] == "Admin") { 
                    vec.emplace_back(Admin :: fromJson(user)); // from json to actual object
                }
                else if (user["type"] == "Seller") { 
                    vec.emplace_back(Seller :: fromJson(user)); 
                }
                else if (user["type"] == "Buyer") { 
                    vec.emplace_back(Buyer :: fromJson(user)); 
                }
                else { 
                    cerr << "type not matched :)" << endl; 
                }
            }
        }
        catch (std::exception &ex) {
            std::cout << "EXCEPTION:" << ex.what() << endl;
        }
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



// ADD USERS
        /*  Admins  */
        /*  Buyers  */
        /*  Sellers */
    void Database :: addUser (const User* newUser) { 
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




//  Function to remove a user from the JSON file
void Database :: remove_user (const User* user) {
    json j;
    try {
        readFile (users_file_path, j);
        
        // Find and erase the user with the matching username
        for (auto it = j["users"].begin(); it != j["users"].end(); ++it) {
            if ((*it)["userName"] == user->getUserName()) {
                j["users"].erase(it);
                break; 
            }
        }

        // Write the updated JSON back to the file
        writeToFile (users_file_path, j);
    } catch (std::exception& ex) { 
        std::cout << "EXCEPTION: " << ex.what() << endl; 
    }
}


// INVENTORY METHODS

// This function is called at the start of execution of the program to load all
// the products in the inventory!
void Database :: loadInventory(Inventory *inventory) {
    json j; 
    try { 
        readFile (inventory_filePath, j);
        for (size_t i = 0; i < j["products"].size(); ++i){
            Product* p = new Product ();
            inventory->loadInventory(Product::fromJson (j["products"][i], p));
        }
    }
    catch (std::exception& ex) { 
        cout << "EXCEPTION: " << ex.what() << endl;
    }
}


// Add the product to centralized inventory
void Database :: addProductToAppInventory (Product* p) {
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



/*
When a new Seller creates his account by sign-up :)
This function creates a new file based on his username (which is unique)
This file will store an array of his product-Ids
*/
void Database :: createNewFileForSeller (const std::string& store_owner) { 
    json j;
    j["productIds"] = json :: array();
    try { 
        writeToFile ("./Database/Inventory/Sellers/" + store_owner + ".json", j);
    }catch (std::exception& ex) { 
        std::cerr << "Exception: " << ex.what() << std::endl; 
    }
}


// This function retrieves the productIds from file, just after a seller logs-in :)
void Database :: loadSellerProductList (json& data, const std::string& store_owner) { 
    try {
        readFile ("./Database/Inventory/Sellers/" + store_owner + ".json", data);
    }
    catch (std::exception& ex) { 
        std::cerr << "Exception: " << ex.what() << std::endl; 
    }
}

 
// Add productId to Seller store 
void Database :: addProductToMyList(const std::string& product_id, const std::string &store_owner) {
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

            auto it = data["productIds"].begin();
            while (it != data["productIds"].end())  {
                if (product_id == (*it)) { 
                    data["productIds"].erase (it); // Remove the product-id
                    break; 
                }
                ++it; 
            }
        }
        writeToFile("./Database/Inventory/Sellers/" + store_owner + ".json", data);
    } catch (std::exception& ex) { 
        std::cout << "EXCEPTION: " << ex.what() << std::endl; 
    }
}

