#include "./ECommerce/ECommerce.h"
#include "./Database/Database.h"

int main() {

    ECommerce :: getInstance()->loadData();
    ECommerce :: getInstance()->displayUsers ();
    ECommerce :: getInstance()->getInventory ()->displayProducts();

    // Application Menu
    char choice; 
    do
    {
        cout << "____________________________________________________________" << endl;
        cout << "\n\t\t E-COMMERCE APPLICATION " << endl;
        cout << "\n L = Login \n\n S = Sign-Up \n\n G = Guest User \n\n X = Clear Screen \n\n E = Exit " << endl;
        cout << "\nEnter choice: ";
        cin >> choice; 
        switch (toupper(choice)) {
            case 'L':{                
                Login ();                
                break;
            }
            case 'S':{
                SignUp();
                break;
            }
            case 'G':{
                break;
            }
            case 'X':{
                system("clear"); // clear the console
                break;
            }
            case 'E':{
                Database::releaseInstance(); 
                ECommerce::releaseInstance(); // release all the dynamically allocated memory
                cout << "\nExiting........." << endl;
                break;
            }
            default: {
                cout << "Wrong Input!" << endl; 
                continue; 
            }
        }
    }while (toupper(choice)!='E');    
    return 0;
}