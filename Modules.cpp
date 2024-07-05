#include "Modules.h"


bool Module :: login (const std::string& userName, const std::string& pass) {
    return 0;
}


/*

std::vector <Buyer*> buyers;
std::vector <Seller*> sellers;
std::vector <Admin*> admins; 

    std::vector <User*> users; 

    users.push_back(&buyers);
    users.push_back(&sellers);
    users.push_back(&admins);

    users[0] = &buyers;
    users[1] = &sellers; 
    users[2] = &admins;
*/




// All the functionalities that an Admin can perform
void Module :: adminModule () {
    std::string userName, pass; 

    cout << "\n\t\t LOGIN " << endl;
    cout << "\nEnter your user name : "; cin >> userName;
    cout << "Enter your password  : "; getline (cin, pass);

}

// Buyer functionalities
void Module :: buyerModule() {
    int choice; 
    do
    {
        cout << "\n\t L = Login \n\t S = Sign-up \n\t X = Clear screen Q = Quit " << endl;
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 'L':{    
                break;
            }
            case 'S':{
                break;
            }
            case 'X':{
                system("clear");
                break;
            }
            case 'Q':{
                cout << "\nExiting......" << endl;
                break;
            }
            default:{
                cout << "\nInvalid choice!" << endl;
            }
        }
    }while (toupper(choice) != 'Q');
}

// Seller functionalities
void Module :: sellerModule() {
    
}