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
json& Admin :: toJson ( json& j ) const { 
    // json j; 
    j["type"] = "Admin"; // flag to differentiate between users
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}


void Admin :: dashBoard () { 
    char choice; 
    do { 
        // system ("clear");
        cout << "___________________________________________________" << endl 
             << "\n\t\t ADMIN DASHBOARD " << endl;    

        cout 
            << "\n Press 'U' to search any User "
            << "\n Press 'L' to Log out "
            << "\n X = Clear Screen "
            << endl;

        cout << "\nEnter your choice: "; 
        cin >> choice; 
        switch (std::toupper(choice)) { 

            case 'U':{
                    std::string userName; 
                    cout << "Enter userName: "; getline (cin, userName);
                    User* user = ECommerce :: getInstance ()->searchUser (userName);
                    user->display(); 
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