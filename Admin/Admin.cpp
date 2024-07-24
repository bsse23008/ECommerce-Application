#include "Admin.h"
#include "./../ECommerce/ECommerce.h" 

Admin :: Admin () : User () {

}

Admin :: Admin (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : User (first, last, user_name, pass) {

}

// Json to object conversion 
Admin* Admin :: fromJson (json& j) {
    return new Admin (j["firstName"], j["lastName"], j["userName"], j["password"]);
}


// Object to Json conversion
json Admin :: toJson ( ) const { 
    json j; 
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}

// Admin Menu
void adminControls (Admin * a) { 
    char choice; 

    do { 
        // system ("clear");
        cout << "___________________________________________________" << endl 
             << "\n\t\t ADMIN CONTROLS " << endl;    

        cout<< "\n Press 'B' to search any buyer "
            << "\n Press 'S' to search any seller "
            << "\n Press 'L' to log out "
            << "\n X = Clear Screen "
            << endl;

        cin >> choice; 
        switch (std::toupper(choice)) { 

            case 'B':{
                std::string* userName = new std::string; 
                cout << "Enter userName: ";   std::cin >> *userName; 
                ECommerce :: getInstance()->searchBuyer (*userName);
                delete userName;
                break; 
            }

            case 'S':{

                std::string* userName = new std::string; 
                cout << "Enter userName: ";   std::cin >> *userName; 
                ECommerce :: getInstance()->searchSeller (*userName);
                delete userName;
                break; 
            }

            case 'X':{
                system ("clear"); 
                break;
            }
            case 'L':{
                cout << "Logging out. Come back soon." << endl; 
                break; 
            }
            default: {
                cout << "Wrong Input ! " << endl; 
                continue;  
            }
        }
    } while (std::toupper(choice) != 'L'); 
}