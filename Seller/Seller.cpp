#include "../ECommerce/ECommerce.h"
#include "../Database/Database.h"
#include "../Inventory/Inventory.h"
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

json& Seller :: toJson ( json& j ) const { 
    j["type"] = "Seller"; // flag to differentiate between users
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


void Seller :: loadMyProducts (Product*  p) { 
    products.emplace_back  (p); 
}


Product* Seller :: searchProduct (const std::string& id) { 
    for (int i=0; i < products.size(); i++) { 
        if (id == products[i]->get_unique_id()) { 
            return products[i];
        }
    }
    return nullptr;
}


void Seller :: addProduct (Product* p) {
    // p->addSeller (this);
    ECommerce::getInstance()->getInventory()->addProduct (p); // Add the product to the centralized inventory first :)
    // Then add it in seller,s products list
    products.push_back (p); // address copy 
    Database :: getInstance()->addProductToMyList (p->get_unique_id(), this->userName); 
}



// Used mostly 
void Seller :: removeProduct (Product* p) {
    for (int i=0; i < products.size(); i++) { 
        if (p == products[i]) { 
				// Remove from database
			Database :: getInstance()->removeProductFromMyList (p->get_unique_id(), this->userName); 
            products.erase (products.begin() + i); // Erase the memory address as well :)
            p = nullptr;
            break; 
        }
    }
}



void Seller :: displayMyProducts () const {
    if (products.size() == 0) { 
        cout << "You don,t have any products in your Store :( " << endl; 
        return; 
    }
    for (const Product* p : products) { 
        cout << "\n____________________________________" << endl; 
        cout << *p << endl;
    }
} 


void Seller :: storeManagement () { 
    char choice; 
    do {
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t STORE MANAGEMENT" << endl; 
        cout << "\n A = Add a Product to my store." 
            << "\n R = Remove a Product from my store."  
            << "\n V = View all products"
            << "\n X = Clear screen" 
            << "\n G = Go Back" << endl; 
        cout << "\nEnter choice: ";
        cin >> choice; 
// Switch 
        switch (std::toupper(choice)) {
            case 'A': {
                std::string id, name, description, category, location, supplier;
                double price, stock;
                
                bool is_unique = true; 
                do {
                    cout << "Enter product Id       : "; cin >> id; 
                    is_unique = ECommerce::getInstance()->getInventory()->isUniqueId (id); // Check if the product Id has already been taken or not ?
                    if (is_unique) 
                        cout << id << " has already been taken :( " << endl;
                }while (is_unique); 
                cin.ignore();
                // cout << endl; 
                    cout << "Enter name of product  : ";  getline (cin, name); 
                    cout << "Enter Description      : "; getline (cin, description) ;
                    cout << "Enyer category         : "; getline (cin, category);
                    cout << "Enter location         : "; cin >> location ;
                    // cout << "Supplier of product    : "; cin >> supplier ;
                    supplier = this->userName; 
                    cout << "Price of product       : "; cin >> price ;
                    cout << "Stock of product       : "; cin >> stock; 
                    Product* p = new Product (id, name, description, category, location, supplier, price, stock);
                    addProduct(p);
                break; 
            }
            case 'R': {
                std::string id; 
                cout << "Enter unique Id of product: ";
                cin >> id; 
                Product* p = searchProduct (id);
                if (p) {  // If product was found in the list 
                    std::cout << endl << *p << endl;
                    bool confirm = false; 
                    cout << "Do you really want ot delete this product ? " << endl 
                        << "\n If Yes -> press 1 \n If No -> press 0 " << endl 
                        << " Enter: ";
                    cin >> confirm; 
                    if (confirm) { 
						//	1. Remove from centralized Inventory
                     	ECommerce :: getInstance ()->getInventory()->removeProduct (p); 
						//	2. Remove from my product list in database
                     	removeProduct (p);   
						// std::cout << *p << endl; // The object still exists because we still have not deleted it :)
                     	delete p;					// Delete the content :)  
						//  3. Null the pointer     
                     	p = nullptr;       
                        std::cout << "\nThe product was removed successfully!" << std::endl;      
                    }                                
                }
                else // In case : If nullptr was returned.
                {
                    cout << "\nProduct with id " << id << " was not found in your store :(" << endl; 
                }                           
                break; 
            }
            case 'V': {
                displayMyProducts ();
                break; 
            }
            case 'X': {
                system ("clear"); 
                break; 
            }
            case 'G': {
                cout << "\nBye :)" << endl;
                break; 
            }
            default: {
                cout << "Invalid Choice! " << endl; 
                continue; 
            }
        }
    }while (std::toupper(choice) != 'G'); 
}


// SELLER DASHBOARD 
void Seller :: dashBoard () { 
    // std::cout << *this << std::endl; 

    char outerSwitch; 

    do { 
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t SELLER INTERFACE " << endl; 
        cout << "\nHi! " << getFirstName () << ". Welcome on the Board!" << endl;
        cout << "\n\n S = Store Management"
             << "\n\n L = Log out " 
             << "\n\n X = Clear screen " << endl;  

        cout << "\nEnter choice: "; 
        cin >> outerSwitch; 
        // Outer-switch case :)
        switch (std::toupper (outerSwitch)) { 
            
            // Store Management
            case 'S':{

                json j; // Read the file in json object 
                Database :: getInstance()->loadSellerProductList (j, getUserName());

                    const size_t size = j["productIds"].size();
                    std::string* productIds = new std::string[size];
                    // Store the Ids in an array
                    for (size_t k=0; k<size; ++k) { 
                        productIds[k] = j["productIds"][k];
                    }

                    // Get your products
                    for (size_t i=0; i<size; ++i) { 
                        Product* p = ECommerce :: getInstance()->getInventory()->getReference (productIds[i]);
                        if (p) { 
                            loadMyProducts (p);
                        }
                    }
                    delete [] productIds; 
                storeManagement (); 
                break; 
            }             
            // Log out
            case 'L':{
                products.clear();
                cout << "Come Back soon :)" << endl;
                break; 
            }
            // Clear screen
            case 'X':{
                system ("clear"); 
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