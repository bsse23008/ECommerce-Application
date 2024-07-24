#include "ECommerce.h"
#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"


template <typename type> 
bool ECommerce :: isUserNameTaken (const std::string& user_name, const std::vector<type*>&vec) {
    for (const auto& i: vec) {
        if (i->getUserName() == user_name)
            return true;
    }
    return false;
}


Admin* ECommerce :: adminSignUp (const std::string& firstName, const std::string&lastName, const std::string&userName, const std::string&password) { 
    // Take input of additional attributes below
    return new Admin (firstName, lastName, userName, password);
}

Buyer* ECommerce :: buyerSignUp (const std::string& firstName, const std::string&lastName, const std::string&userName, const std::string&password)  {
    // Take input of additional attributes below
    int age;
    return new Buyer (firstName, lastName, userName, password);
}

Seller* ECommerce :: sellerSignUp (const std::string& firstName, const std::string&lastName, const std::string&userName, const std::string&password) {
    // Take input of additional attributes below
    std::string phone_number, org, dob, cnic; 
    cout << "Enter your phone no: "; 
    getline (cin, phone_number);
    cout << "Enter your organization name: "; 
    getline (cin, org);
    cout << "Enter your date of birth: ";
    getline (cin, dob);
    cout << "Enter your CNIC: ";
    getline (cin, cnic);

    /*Address Info*/
    /*

    */
    return new Seller (firstName, lastName, userName, password, phone_number, org, dob, cnic);
}



template <typename T>
void ECommerce :: inputCredentials(
    std::string& firstName,
    std::string& lastName,
    std::string& userName,
    std::string& pass, const std::vector<T*>&vec)  // Parameters
{ 
    cout << "\n<--INPUT CREDENTIALS-->\n";
    cout << "\nEnter your first name: ";
    cin >> firstName;
    cout << "Enter your last name : ";
    cin >> lastName;

    // Checking if the user name has already been taken 
    bool is_user_name_taken = false;
    do {
        cout << "Enter your user name : ";
        cin >> userName;
        is_user_name_taken = isUserNameTaken(userName, vec);
        if (is_user_name_taken) 
            cout << userName << " has already been taken. Try another one! " << endl;
    }while (is_user_name_taken);

    cin.ignore();
    // Password Input 
    do {
        cout << "Enter your password (at least 8 characters long): ";
        getline (cin, pass);
        if (pass.length() < 8) {
            cout << "Weak password. Must be 8 characters long! " << std::endl;
        }
    } while (pass.length() < 8);

    // Password Confirmation
    std::string retype_pass; 
    do {
        cout << "Confirm Password: "; getline (cin, retype_pass);
    }while (retype_pass != pass);
}


void ECommerce :: signUp () {
    std::string firstName, lastName, userName, pass;
    char choice;
    do {
        system ("clear");
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t CREATE YOUR ACCOUNT " << endl;
        cout << "\nWhat type of account do you want to create? " << endl;
        cout << "\nSignUp as: \n\nA = Admin \n\nB = Buyer \n\nS = Seller \n\nX = Clear screen \n\nG = Go Back" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (std::toupper(choice)) {
            case 'A': {
                const std::string code("adminCode");  // Corrected typo from "amdinCode"
                int count = 0;
                bool verified = false;

                cout << "____________________________________________________________" << endl;
                cout << "\n\t\t\tVERIFICATION \n\nYou have to verify that you are eligible to create an admin account.\n" << endl;
                
                cin.ignore();
                do {
                    cout << "Enter admin code: ";
                    getline (cin, firstName);
                    count++;
                    if (firstName == code) {
                        verified = true;
                        break;
                    }
                    else {
                        cout << "Wrong code.Try again! " << endl;
                    }
                    if (count == 3) {
                        cout << "\nTotal attempts reached." << endl;
                        break;
                    }
                } while (count < 3);

                if (verified) {
                    firstName.clear();
                    inputCredentials<Admin>(firstName, lastName, userName, pass, admins);
                    Admin* a = adminSignUp(firstName, lastName, userName, pass);
                    addAdmin(a);
                    
                    // Login to your account after signUp
                    cout << "\nNow Login to account below :)" << endl; 
                    login();  
                    a = nullptr;
                } else {
                    cout << "\nVerification failed. Returning to the main menu." << endl;
                }
                break;
            }
            case 'B': {
                inputCredentials<Buyer>(firstName, lastName, userName, pass, buyers);
                Buyer* b = buyerSignUp (firstName, lastName, userName, pass);
                addBuyer(b);
                cout << "\nNow Login to account below :)" << endl; 
                login();
                b = nullptr;
                break;
            }
            case 'S': {
                inputCredentials<Seller>(firstName, lastName, userName, pass, sellers);
                Seller* s = sellerSignUp (firstName, lastName, userName, pass);
                addSeller(s);
                
                cout << "\nNow Login to account below :)" << endl; 
                login();
                s = nullptr; 
                break;
            }
            case 'X': {
                system("clear"); // clear the console
                break;
            }
            case 'G': {
                std::cout << "\nGoing back to home page........" << std::endl;
                break;
            }
            default: {
                cout << "\nInvalid command! " << endl;
            }
        }
    } while (std::toupper(choice) != 'G');
}
