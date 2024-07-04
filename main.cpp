#include "./Person/Person.h"

int main() {
    // Main menu
    char choice; 

    do
    {
        cout << "_____________________________________________________________________________\n";
        cout << "\n\t\t E-COMMERCE PLATFORM APPLICATION \n" << endl;
        cout << "\n\t A = Admin \n\t B = Buyer \n\t S = Seller \n\t C = Customer \n\t X = Clear Screen \n\t Q = Quit" << endl;
        cout << "\nEnter : ";
        cin >> choice;

        switch (toupper(choice)) {
            case 'A':{ 
                Person* p = new Person ("Ahmad", "Khan", "bsse23008", "*****");
                p->display();
                delete p;
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
    return 0;
}