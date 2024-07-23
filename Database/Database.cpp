#include "Database.h"

// Initialize the instance
Database *Database::instance{nullptr};


// RETRIEVE DATA FROM DATABASE
template <typename T>
void Database::loadData(std::vector<T *> &vec, json &j, const std::string &file_path)
{
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
    loadData<Admin>(a, json_admins, admins_filePath);
}

void Database::loadBuyers(std::vector<Buyer *> &b)
{
    loadData<Buyer>(b, json_buyers, buyers_filePath); 
}

void Database::loadSellers(std::vector<Seller *> &s)
{
    loadData<Seller>(s, json_sellers, sellers_filePath);
}

// UPDATE FILES
void Database::update_users_file(const json &j, const std::string &file_path)
{
    std::ofstream out(file_path, std::ios::trunc);
    if (!out.is_open())
    {
        cerr << "Error opening the file: " << file_path << std::endl;
        return;
    }
    out << std::setw(4) << j << std::endl;
    out.close();
}


// ADD NEW USERS TO DATABASE 
void Database::add_admin(const json &j)
{
    json_admins["users"].emplace_back(j);
    update_users_file(json_admins, admins_filePath);
}

void Database::add_buyer(const json &j)
{
    json_buyers["users"].emplace_back(j);
    update_users_file(json_buyers, buyers_filePath);
}

void Database::add_seller(const json &j)
{
    json_sellers["users"].emplace_back(j);
    update_users_file(json_sellers, sellers_filePath);
}


// REMOVE USERS FROM DATABASE
void Database::remove_user(json &j, const std::string &username)
{
    auto &users = j["users"];
    auto it = std::find_if(users.begin(), users.end(), [&username](const json &user)
                           { return user["userName"] == username; });
    if (it != users.end())
    {
        users.erase(it);
    }
}

void Database::remove_admin(const std::string &username)
{
    remove_user(json_admins, username);
    update_users_file(json_admins, admins_filePath);
}

void Database::remove_buyer(const std::string &username)
{
    remove_user(json_buyers, username);
    update_users_file(json_buyers, buyers_filePath);
}

void Database::remove_seller(const std::string &username)
{
    remove_user(json_sellers, username);
    update_users_file(json_sellers, sellers_filePath);
}


// INVENTORY METHODS
void Database::updateMyStore(json &j, const std::string &store_owner)
{
    j["inventory"].push_back(j);
    std::ofstream out("Inventory/" + store_owner + ".json", std::ios::trunc);
    if (out.is_open())
    {
        out << std::setw(4) << json_inventory << std::endl;
    }
    else
    {
        std::cerr << "Could not open: Inventory/" << store_owner << ".json" << std::endl;
    }
}
