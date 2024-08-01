#include "ECommerce.h"


Admin* adminSignUp (const std::string& firstName,
                        const std::string& lastName,
                            const std::string& userName,
                                const std::string& password) { 
    // Take input of additional attributes below
    return new Admin (firstName, lastName, userName, password);
}

Buyer* buyerSignUp (const std::string& firstName,
                        const std::string& lastName,
                            const std::string& userName,
                                const std::string& password) {
    // Take input of additional attributes below
    int age;
    return new Buyer (firstName, lastName, userName, password);
}

Seller* sellerSignUp (const std::string& firstName,
                        const std::string& lastName,
                            const std::string& userName, 
                                const std::string& password) {
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



void inputCredentials (std::string& firstName, std::string& lastName, std::string& userName, std::string& pass) { 
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
        is_user_name_taken = ECommerce::getInstance()->isUserNameTaken(userName);
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


void Login ()  {
    std::string userName, pass; 

    // Clear the buffer 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                              
    std::cout << "\nEnter your username: "; getline (std::cin, userName);
    std::cout << "Enter your password: "; getline (std::cin, pass);

    User* user = ECommerce :: getInstance ()->login (userName, pass); 
    if (user) {
        user->dashBoard (); // calls the appropriate method :)
    } else {
        std::cout << "Wrong credentials :(" << std::endl; // In case: nullptr was returned!
    }
}


void SignUp () {
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
                    inputCredentials (firstName, lastName, userName, pass);
                    Admin* a = adminSignUp(firstName, lastName, userName, pass);

                    ECommerce::getInstance()->addUser /*<Admin>*/ (a);   
                    cout << "\nSigned-up successfully! " << endl;                    
                    cout << "\nNow Login to account below :)" << endl; 
                    Login (); // global

                    a = nullptr;
                } else {
                    cout << "\nVerification failed. Returning to the main menu." << endl;
                }
                break;
            }
            case 'B': {
                // Take input of common credentials first
                inputCredentials (firstName, lastName, userName, pass);

                // Input of additional attributes
                Buyer* b = buyerSignUp (firstName, lastName, userName, pass);
                
                ECommerce::getInstance()->addUser /*<Buyer>*/ (b);
                cout << "\nSigned-up successfully! " << endl;   
                cout << "\nNow Login to account below :)" << endl; 
                Login(); // global
                b = nullptr;

                break;
            }
            case 'S': {
                // Take input of common credentials first
                inputCredentials (firstName, lastName, userName, pass);

                // Input of additional attributes
                Seller* s = sellerSignUp (firstName, lastName, userName, pass);

                ECommerce::getInstance()->addUser /*<Seller>*/(s);

                // Making a separate file for seller! 
                // Where he can store his productIds
                    Database :: getInstance()->createNewFileForSeller (s->getUserName()); 
                    cout << "\nSigned-up successfully! " << endl;                 
                    cout << "Now Login to your account below :)" << endl; 
                    Login(); // global
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
                break;
            }
        }
    } while (std::toupper(choice) != 'G');
}
