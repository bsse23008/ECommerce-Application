#include "../ECommerce/ECommerce.h"
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

json Seller :: toJson ( ) const { 
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


std::ostream& operator << (std::ostream& os, const Seller& seller) { 
    os << static_cast<const User&>(seller); // Call the parent class operator<<
    os << "Phone No    : " << seller.phoneNo << endl; 
    os << "Organization: " << seller.organization << endl; 
    os << "DOB         : " << seller.DOB << endl; 
    os << "CNIC        : " << seller.CNIC << endl; 
    os << "Products    : " << seller.products.size() << " products listed" << std::endl;
    // Optionally, we can loop through and print each product if needed < ' ' > 
    return os;
}


void Seller :: updateMyStore (const std::string& user_name) {
    // json j; 
    // j["products"]; 

    // for (int i=0; i<products.size(); i++) {
    //     json* temp = new json; 
    //     j["products"].push_back (*(products.at(i)->toJson(temp))); 
    //     delete temp;
    // }

    // // Time to write the updated information to file
    // const std::string file_path = "Database/Inventory/" + this->userName + ".json";
    // std::ofstream writeToFile (file_path, std::ios::trunc);
    // try { 
    //     if (writeToFile.is_open()) { 
    //         writeToFile << std::setw(4) << j << std::endl; 
    //         writeToFile.close ();
    //     }
    // }
    // catch (std::exception& ex) {
    //     std::cerr << "Error: " << ex.what() << endl; 
    // }
}

void Seller :: addProduct (Product* p) {
    ECommerce::getInstance()->getInventory()->addProduct (p); // Add the product to the centralized inventory first :)
    // Then add it seller,s products list
    products.push_back (p); // copy 
    // updateMyStore (this->userName); 
    json* j = new json ();
    Database :: getInstance()->updateMyStore (p->get_unique_id(), this->userName); 
}

void Seller :: removeProduct (const std::string& id) {
    for (int i=0; i<products.size(); i++) {
        if (id == products[i]->get_unique_id()) 
        {
            products.erase (products.begin() + i); 
            break; 
        }
    }
}


void sellerControls (Seller* s) { 
    char outerSwitch; 
    char innerSwitch;

    do { 
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t SELLER INTERFACE " << endl; 
        cout << "\n\n S = Store Management"
             << "\n\n L = Log out " 
             << "\n\n X = Clear screen " << endl;  

        cout << "\nEnter choice: "; 
        cin >> outerSwitch; 
        // Outer-switch case :)
        switch (std::toupper (outerSwitch)) { 
            
            // Store Management 
            case 'S':{
                do {
                    cout << "____________________________________________________________" << endl;
                    cout << "\n\t\t STORE MANAGEMENT" << endl; 
                    cout << "\n A = Add a Product to my store." 
                        << "\n R = Remove a Product from my store."  
                        << "\n V = View all products"
                        << "\n X = Clear screen" 
                        << "\n G = Go Back" << endl; 
                    cout << "\nEnter choice: ";
                    cin >> innerSwitch; 
                    // Inner-switch case :)
                    switch (std::toupper(innerSwitch)) {
                        case 'A': {
                            std::string id, name, description, category, location, supplier;
                            double price, stock;
                            
                            bool is_unique = true; 
                            do {
                                cout << "Enter product Id (should be unique): "; cin >> id; 
                                is_unique = s->isUniqueId (id);
                                if (is_unique) 
                                    cout << id << " has already benn taken :( " << endl;
                            }while (is_unique); 

                            cin.ignore();
                                cout << "Enter name of product: ";  getline (cin, name); 
                                cout << "Enter Description: "; getline (cin, description) ;
                                cout << "Enyer category   : "; getline (cin, category);
                                cout << "Enter location   : "; cin >> location ;
                                cout << "Supplier of product: "; cin >> supplier ;
                                cout << "Price of product   : "; cin >> price ;
                                cout << "Stock of product   : "; cin >> stock ; 

                                Product* p = new Product (id, name, description, category, location, supplier, price, stock);
                                s->addProduct(p);
                            break; 
                        }
                        case 'R': {
                            std::string id; 
                            cout << "Enter unique Id of product: ";
                            cin >> id; 

                            Product* p = s->searchProduct (id); 

                            if (p) {  // If product was found in the list 
 
                                std::cout << *p << endl;
                                bool confirm = 0; 
                                cout << "Do you really want ot delete this product ? " << endl 
                                    << "\n If Yes -> press 1 \n If No -> press 0 " << endl; 
                                cin >> confirm; 

                                if (confirm) { 
                                    s->removeProduct (id);
                                    s->removeProduct (p);
                                    p = nullptr; 
                                }                                
                            }
                            else // In case : If nullptr was returned.
                            {
                                cout << "\nProduct with id " << id << " was not found in your store :(" << endl; 
                            }                           
                            break; 
                        }
                        case 'V': {
                            s->displayMyProducts ();
                            break; 
                        }
                        case 'X': {
                            system ("clear"); 
                            break; 
                        }
                        default: {
                            cout << "Invalid Choice! " << endl; 
                            continue; 
                        }
                    }
                }while (std::toupper(innerSwitch) != 'G'); 
            }
            // Log out
            case 'L':{
                cout << "Come Back soon :)" << endl;
                break; 
            }
            // Clear screen
            case 'X':{
                system("clear");
                break;
            }
            // Default case
            default:{
                cout << "Invlaid choice!" << endl; 
                continue; 
            }
        }
    } while (std::toupper (outerSwitch) != 'L'); 
}