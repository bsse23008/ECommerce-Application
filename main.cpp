#include "./ECommerce/ECommerce.h"


void retrieveData(void (ECommerce::*retrieveFunction)(), const std::string& functionName) {
    try {
        (ECommerce::getInstance()->*retrieveFunction)();
    }
    catch (std::exception& ex) {
        std::cerr << "Unable to retrieve data from Database in " << functionName << ": " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown Exception caught in " << functionName << "!" << std::endl;
    }
}

 int main() {
    
    // Retrieving data from Database folder
    retrieveData(&ECommerce::retrieveAdmins, "retrieveAdmins");
    retrieveData(&ECommerce::retrieveBuyers, "retrieveBuyers");
    retrieveData(&ECommerce::retrieveSellers, "retrieveSellers");

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
                login();                
                break;
            }
            case 'S':{
                ECommerce :: getInstance ()->signUp ();
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
                ECommerce::releaseInstance(); // release all the dynamically allocated memory
                cout << "\nExiting........." << endl;
                break;
            }
        }
    }while (toupper(choice)!='E');    

    return 0;
}