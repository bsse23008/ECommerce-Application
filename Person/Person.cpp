#include "Person.h"


Person :: Person () : firstName {"None"}, lastName {"None"}, userName {"None"}, password {"None"} {

}

Person :: Person (
        const std::string & first,
        const std::string & last,
        const std::string & user_name,
        const std::string & pass) 
: firstName{first}, lastName{last}, userName{user_name}, password{pass} {

}


// Setters 
void Person :: setFirstName(const std::string & first) {
    this->firstName = first;
}

void Person :: setLastName(const std::string & last) { 
    this->lastName = last;
}

void Person :: setUserName(const std::string & user_name) {
    this->userName = user_name; 
}

void Person :: setPassword(const std::string & pass) {
    this->password = pass;
}


// Getters 
std::string Person :: getFirstName() const {
    return firstName; 
}

std::string Person :: getLastName() const {
    return lastName;
}

std::string Person :: getUserName() const {
    return userName;
}

std::string Person :: getPassword() const {
    return password;
}

// Display method
void Person :: display () const {
    cout << *this << endl;
}

// I/O stream Operators
std::ostream& operator << (std::ostream& os, const Person& p) {
    os << endl;
    os << "First Name: " << p.firstName << endl; 
    os << "Last Name : " << p.lastName << endl; 
    os << "User Name : " << p.userName << endl; 
    os << "Password  : " << p.password << endl; 

    return os; 
}

std::istream& operator >> (std::istream& is, Person& p) {

    cout << "\nEnter first name: "; is >> p.firstName;
    cout << "Enter last name : "; is >> p.lastName;
    cout << "Enter user name : "; is >> p.userName;
    cout << "Enter password  : "; is >> p.password;
    return is;
}