#include "./Person/Person.h"

int main() {
    // Main menu
    char choice; 
    cout << "\n\t\t E-COMMERCE PLATFORM APPLICATION \n" << endl;

    do
    {
        cout << "\n\t A = Admin \n\t B = Buyer \n\t S = Seller \n\t C = Customer \n\t Q = Quit" << endl;
        cin >> choice;

        switch (toupper(choice)) {
            case 'A':{ 
                break;
            }
            case 'B':{
                break;
            }
            case 'S':{
                break;
            }
            case 'C':{
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

    return 0;
}