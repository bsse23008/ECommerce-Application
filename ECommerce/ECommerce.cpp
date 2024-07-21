#include "ECommerce.h"

// Release the dynamically allocated memory
ECommerce :: ~ECommerce () {
    cout << "\nECommerce destructor called!" << endl;
    // Do we need to delete all the dynamically allocated memory here? 
    
    for (Buyer* buyer : buyers) {
        delete buyer;
    }
    for (Seller* seller : sellers) {
        delete seller;
    }
    for (Admin* admin : admins) {
        delete admin;
    }
}

// Singleton get instance function 
ECommerce *ECommerce ::getInstance()
{
    static ECommerce *instance = new ECommerce();
    return instance;
}


// Release the dynamic memory 
void ECommerce :: releaseInstance () {
    delete getInstance(); 
}


// template function to retrieve data from the files
template <typename type>
void ECommerce :: retrieveData (const std::string& filePath, std::vector<type*>& vec) {
    json data;
    std::ifstream read (filePath, std::ios::in);
    if (read.is_open()) {
        read >> data; 
        read.close();

        for (int i=0; i<data["users"].size(); ++i) {
            vec.emplace_back(type :: fromJson (data["users"][i]));
        }
    }
    else {
        throw std::runtime_error{"Unable to retrieve data!\n"};
        // std::cerr << "\nError opening the file!: " << filePath << std::endl; 
    }
}

void ECommerce :: retrieveBuyers() {
    retrieveData<Buyer>(buyers_filePath, buyers);
}

void ECommerce :: retrieveSellers() {
    retrieveData<Seller>(sellers_filePath, sellers);
}

void ECommerce ::retrieveAdmins() {
    retrieveData<Admin>(admins_filePath, admins);
}


// template function to update the files/databases
template<typename type>
void ECommerce :: updateFile (const std::string& filePath, std::vector<type*>& vec) { 
    json data; 
    data["users"]; 
    for(int i=0; i<vec.size(); ++i) {
        data["users"].push_back(vec.at(i)->toJson()); 
    }
    // Writing to the file
    std::ofstream write (filePath, std::ios::trunc);
    if (write.is_open()) {
        write << std::setw(4) << data << endl; // updation of the old data
        write.close();
    }
    else {
        std::cerr << "\nError opening the file\n" << endl;
    }
}


// template function to add a User (Admin/Buyer/Seller)
template <typename type> 
void ECommerce :: addUser (const std::string& filePath, type* obj, std::vector<type*>& vec) {
    vec.push_back(obj);
    updateFile<type>(filePath, vec);
}

void ECommerce :: addBuyer(Buyer *b) { 
    addUser<Buyer> (buyers_filePath , b, buyers);
}

void ECommerce :: addSeller(Seller *s) {
    addUser<Seller>(sellers_filePath, s, sellers);
}

void ECommerce :: addAdmin(Admin *a) {
    addUser<Admin>(admins_filePath, a, admins);
    
}


// template function to remove a User (Admin/Buyer/Seller)
template<typename type>
bool ECommerce :: removeUser (const std::string& filePath, const std::string& userName, std::vector<type*>&vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) {
        if ((*it)->getUserName() == userName) {
            vec.erase(it);
            updateFile<type>(filePath, vec);
            return true;  // confirmation flag
        }
    }
    return false;
}


bool ECommerce :: removeBuyer(const std::string &userName) { // Remove the buyer from "buyers.json"
    if (removeUser<Buyer>(buyers_filePath, userName, buyers)) 
        return true; 
    return false;
}


bool ECommerce :: removeSeller(const std::string &userName) { // Remove the seller from "sellers.json"
    if (removeUser<Seller>(sellers_filePath, userName, sellers))
        return true;
    return false;
}


bool ECommerce :: removeAdmin(const std::string &userName) { // Remove admin from "admins.json"
    if (removeUser<Admin>(admins_filePath, userName, admins))
        return true;
    return false;
}
