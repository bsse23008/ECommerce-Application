#include "ECommerce.h"

#include "./../Inventory/Inventory.h"
#include "./../Admin/Admin.h"
#include "./../Seller/Seller.h"
#include "./../Buyer/Buyer.h"

// template function to login in
template <typename type>
type* ECommerce ::isLoggedIn(const std::string &user_name, const std::string &pass, std::vector<type *> vec) {
    for (const auto &u : vec) {
        if (u->getUserName() == user_name && u->getPassword() == pass)
            return u;
    }
    return nullptr;
}

Buyer* ECommerce :: isBuyerLoggedIn(const std::string &user_name, const std::string &pass) {
    Buyer* buyer = isLoggedIn<Buyer>(user_name, pass, buyers);
    if (buyer)
        return buyer; 
    return nullptr;
}

Seller* ECommerce :: isSellerLoggedIn(const std::string &user_name, const std::string &pass) {
    Seller* seller = isLoggedIn<Seller>(user_name, pass, sellers);
    if (seller)
        return seller; 
    return nullptr;
}

Admin* ECommerce :: isAdminLoggedIn(const std::string &user_name, const std::string &pass) {
    Admin* admin = isLoggedIn<Admin>(user_name, pass, admins);
    if (admin)
        return admin; 
    return nullptr;
}


// Global function to input credentials
void inputCredentials (std::string& user_name, std::string& pass) {
    cout << "\nEnter your user name: "; cin >> user_name;
    cout << "\nEnter your password : "; cin >> pass;
}


// Global function to login()
void login() {
    char choice; 
    int count = 0;
    std::string userName, pass;
    
    // Keep taking input until the total attempts are reached :)
    do {
        if (count == 3) {
            cout << "\nTotal attempts reached. Try again later!" << endl;
            break;
        } 
        // system("clear");
        cout << "\n____________________________________________________________" << endl;
        cout << "\n\t\t USER AUTHENTICATION " << endl;
        cout << "\nPress any key to login or 'X' to clear screen, 'G' to go back: " << endl;
        cin >> choice;

        if (std::toupper(choice) == 'X') {
            system("clear");
            continue;
        }
        else if (std::toupper(choice) == 'G') {
            cout << "\nGoing to home page........" << endl;
            break;
        }

        inputCredentials(userName, pass);

        // Attempt to log in as Admin
        if (Admin* admin = ECommerce::getInstance()->isAdminLoggedIn(userName, pass)) {
            cout << "\nAdmin logged in successfully!" << endl;
            // Additional admin-specific code
            adminControls (admin);
            admin = nullptr; 
            break;
        }

        // Attempt to log in as Buyer
        else if (Buyer* buyer = ECommerce::getInstance()->isBuyerLoggedIn(userName, pass)) {
            cout << "\nBuyer logged in successfully!" << endl;
            // Additional buyer-specific code
            break;
        }

        // Attempt to log in as Seller
        else if (Seller* seller = ECommerce::getInstance()->isSellerLoggedIn(userName, pass)) {
            cout << "\nSeller logged in successfully!" << endl; 
            ECommerce :: getInstance()->loadSellerInventory (seller); // loading the seller inventory from Database
            // Additional seller-specific code
            sellerControls (seller);
            break;
        }

        // If no successful login, print an error message
        else {
            cout << "\nWrong Credentials!" << endl;
            userName.clear();
            pass.clear();
            count++; 
        }
    } while (true);
}
