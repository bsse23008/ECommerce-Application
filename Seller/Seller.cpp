#include "Seller.h"

Seller :: Seller () : User () {

}

Seller :: Seller (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass, 
    /*seller-specific attributes*/
    const std::string & phone_number,
    const std::string & org,
    const std::string & dob,
    const std::string & cnic
    ) : User (first, last, user_name, pass), phoneNo(phone_number), organization(org), DOB(dob), CNIC(cnic) {

}


// Getters
std::string Seller :: getPhoneNo () const {
    return phoneNo;
}

std::string Seller :: getOrganization () const {
    return organization; 
}

std::string Seller :: getDOB () const {
    return DOB; 
}

std::string Seller :: getCNIC () const {
    return CNIC; 
} 

// Setters 
void Seller :: setPhoneNo (const std::string& phone_number) {
    this->phoneNo = phone_number; 
}

void Seller :: setOrganization (const std::string& org) {
    this->organization = org; 
}

void Seller :: setDOB (const std::string& dob) {
    this->DOB = dob; 
}

void Seller :: setCNIC (const std::string& cnic) {
    this->CNIC = cnic; 
} 


Seller* Seller :: fromJson (json& j) {
    return new Seller (j["firstName"], j["lastName"], j["userName"], j["password"],
    /*seller attributes*/ j["phoneNo"], j["organization"], j["DOB"], j["CNIC"]);
}

json Seller :: toJson ( ) { 
    json j; 
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    // attributes specific to seller only
    j["phoneNo"] = this->phoneNo; 
    j["organization"] = this->organization; 
    j["DOB"] = this->DOB; 
    j["CNIC"] = this->CNIC; 
    return j; 
}


void Seller :: updateMyStore () {
    json j; 
    j["products"]; 

    for (int i=0; i<products.size(); i++) {
        json* temp = new json; 
        j["products"].push_back (*(products.at(i).toJson(temp))); 
        delete temp;
    }

    // Time to write the updated information to file
    const std::string file_path = "Database/Inventory/" + this->userName + ".json";
    std::ofstream writeToFile (file_path, std::ios::trunc);
    try { 
        if (writeToFile.is_open()) { 
            writeToFile << std::setw(4) << j << std::endl; 
            writeToFile.close ();
        }
    }
    catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << endl; 
    }
}

void Seller :: addProduct (Product p) {
    products.push_back (p);
    updateMyStore ();
    // updateMyStore (Database :: getInstance()->updateMyStore (p.tojson()) );
}

void Seller :: removeProduct (Product p) {
    for (int i=0; i<products.size(); i++) {
        // if (p == products[i]) 
        {
            products.erase (products.begin() + i); 
            break; 
        }
    }
    updateMyStore (); // update the file as well 
}