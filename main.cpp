#include "Modules.h"

int main() {
    // Main menu
    char choice; 
    Module* module = new Module();
    do
    {
        cout << "_____________________________________________________________________________\n";
        cout << "\n\t\t E-COMMERCE PLATFORM APPLICATION \n" << endl;
        cout << "\n\t A = Admin \n\t B = Buyer \n\t S = Seller \n\t C = Customer \n\t X = Clear Screen \n\t Q = Quit" << endl;
        cout << "\nEnter : ";
        cin >> choice;

        switch (toupper(choice)) {
            case 'A':{ 
                module->adminModule();
                break;
            }
            case 'B':{
                module->buyerModule();
                break;
            }
            case 'S':{
                module->sellerModule();
                break;
            }
            case 'C':{
                // Buyer
                break;
            }
            case 'X':{
                system("clear"); // clear the console
                break;
            }
            case 'Q':{
                cout << "\nHave a nice day!" << endl;
                break;
            }
            default:{
                cout << "\nYou made and invalid choice!" << endl;
                continue;
            }
        }
    }while (toupper(choice)!='Q');
    delete module;
    return 0;
}