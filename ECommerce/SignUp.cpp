#include "ECommerce.h"

template <typename type>
bool ECommerce ::isUserNameTaken(const std::string &user_name, const std::vector<type *> &vec)
{
    for (const auto &i : vec)
    {
        if (i->getUserName() == user_name)
            return true;
    }
    return false;
}

Admin *ECommerce ::adminSignUp(const std::string &firstName, const std::string &lastName, const std::string &userName, const std::string &password)
{
    // Take input of additional attributes below
    return new Admin(firstName, lastName, userName, password);
}

Buyer *ECommerce ::buyerSignUp(const std::string &firstName, const std::string &lastName, const std::string &userName, const std::string &password)
{
    Buyer *b = new Buyer(firstName, lastName, userName, password);
    // Take input of additional attributes
    int choice, choice2;
    b->setCategory(categories);

    std::cout << "Enter [1] if you want to select the categories you are interested \n Enter [0] if you want to skip this stop\n";
    std::cin >> choice;
    switch (choice)
    {
    case 0:
    {
        std::cout << "Congratulations! you have successfully created your account.\n";
    }
    case 1:
    {
        std::cout << "Selection of the categories you are interested in: \n";
        b->selectCategory();

        std::cout << "Enter [1] if you want to select the sub categories of the categories you are interested \n Enter [0] if you want to skip this stop\n";
        std::cin >> choice2;

        switch (choice2)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            std::cout << "Selection of the sub categories you are interested in: \n";
            b->selectSubCategory();
            for (size_t i = 0; i < b->getPreferredSubCategory().size(); i++)
            {
                std::cout<<b->getPreferredSubCategory()[i]<<std::endl;
            }
            
            
            break;
        }
        default:
        {
            std::cout << "Invalid Input. Try Again :( \n";
            break;
        }
        }
        std::cout << "Congratulations! you have successfully created your account.\n";
        break;
    }
    default:
    {
        std::cout << "Invalid Input. Try Again :( \n";
    }
    }

    return b;
}

Seller *ECommerce ::sellerSignUp(const std::string &firstName, const std::string &lastName, const std::string &userName, const std::string &password)
{
    // Take input of additional attributes below
    return new Seller(firstName, lastName, userName, password);
}

template <typename T>
void ECommerce ::inputCredentials(
    std::string &firstName,
    std::string &lastName,
    std::string &userName,
    std::string &pass, const std::vector<T *> &vec) // Parameters
{
    cout << "\n<--INPUT CREDENTIALS-->\n";
    cout << "\nEnter your first name: ";
    cin >> firstName;
    cout << "Enter your last name : ";
    cin >> lastName;

    // Checking if the user name has already been taken
    bool is_user_name_taken = false;
    do
    {
        cout << "Enter your user name : ";
        cin >> userName;
        is_user_name_taken = isUserNameTaken(userName, vec);
        if (is_user_name_taken)
            cout << userName << " has already been taken. Try another one! " << endl;
    } while (is_user_name_taken);

    cin.ignore();
    // Password Input
    do
    {
        cout << "Enter your password (at least 8 characters long): ";
        getline(cin, pass);
        if (pass.length() < 8)
        {
            cout << "Weak password. Must be 8 characters long! " << std::endl;
        }
    } while (pass.length() < 8);

    // Password Confirmation
    std::string retype_pass;
    do
    {
        cout << "Confirm Password: ";
        getline(cin, retype_pass);
    } while (retype_pass != pass);
}

void ECommerce ::signUp()
{
    std::string firstName, lastName, userName, pass;
    char choice;
    do
    {
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t CREATE YOUR ACCOUNT " << endl;
        cout << "\nWhat type of account do you want to create? " << endl;
        cout << "\nSignUp as: \n\nA = Admin \nB = Buyer \nS = Seller \nX = Clear screen \nG = Go Back" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (std::toupper(choice))
        {
        case 'A':
        {
            inputCredentials<Admin>(firstName, lastName, userName, pass, admins);
            Admin *a = adminSignUp(firstName, lastName, userName, pass);
            addAdmin(a);
            login(); // Login to your accout after signUp
            a = nullptr;
            break;
        }
        case 'B':
        {
            inputCredentials<Buyer>(firstName, lastName, userName, pass, buyers);
            Buyer *b = buyerSignUp(firstName, lastName, userName, pass);
            addBuyer(b);
            login();
            b = nullptr;
            break;
        }
        case 'S':
        {
            inputCredentials<Seller>(firstName, lastName, userName, pass, sellers);
            Seller *s = sellerSignUp(firstName, lastName, userName, pass);
            addSeller(s);
            login();
            s = nullptr;
            break;
        }
        case 'X':
        {
            system("clear"); // clear the console
            break;
        }
        case 'G':
        {
            std::cout << "\nGoing back to home page........" << std::endl;
            break;
        }
        }
    } while (std::toupper(choice) != 'E');
}
