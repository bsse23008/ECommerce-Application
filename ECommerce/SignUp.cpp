#include "ECommerce.h"

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
    Buyer* b = new Buyer (firstName, lastName, userName, password);
    // Take input of additional attributes 
    std::cout <<" Selection of the categories you are interested in: \n";
    int i=0;
    do{
    for (int i=0; i<categories.size(); i++) {
        categories[i].displayCategories();
    }
    }while (true);

    return b;
}

Seller* ECommerce :: sellerSignUp (const std::string& firstName, const std::string&lastName, const std::string&userName, const std::string&password) {
    // Take input of additional attributes below
    return new Seller (firstName, lastName, userName, password);
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
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t CREATE YOUR ACCOUNT " << endl;
        cout << "\nWhat type of account do you want to create? " << endl;
        cout << "\nSignUp as: \n\nA = Admin \nB = Buyer \nS = Seller \nX = Clear screen \nG = Go Back" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (std::toupper(choice)) {
            case 'A': {
                inputCredentials<Admin>(firstName, lastName, userName, pass, admins);
                Admin* a = adminSignUp (firstName, lastName, userName, pass);
                addAdmin(a);
                login();     // Login to your accout after signUp 
                a = nullptr;
                break;
            }
            case 'B': {
                inputCredentials<Buyer>(firstName, lastName, userName, pass, buyers);
                Buyer* b = buyerSignUp (firstName, lastName, userName, pass);
                addBuyer(b);
                login();
                b = nullptr;
                break;
            }
            case 'S': {
                inputCredentials<Seller>(firstName, lastName, userName, pass, sellers);
                Seller* s = sellerSignUp (firstName, lastName, userName, pass);
                addSeller(s);
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
        }
    } while (std::toupper(choice) != 'E');
}
