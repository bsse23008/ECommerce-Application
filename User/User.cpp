#include "User.h"


User :: User () : firstName {"None"}, lastName {"None"}, userName {"None"}, password {"None"} {

}

User :: User (
        const std::string & first,
        const std::string & last,
        const std::string & user_name,
        const std::string & pass) 
: firstName{first}, lastName{last}, userName{user_name}, password{pass} {

}


// Setters 
void User :: setFirstName(const std::string & first) {
    this->firstName = first;
}

void User :: setLastName(const std::string & last) { 
    this->lastName = last;
}

void User :: setUserName(const std::string & user_name) {
    this->userName = user_name; 
}

void User :: setPassword(const std::string & pass) {
    this->password = pass;
}


// Getters 
std::string User :: getFirstName() const {
    return firstName; 
}

std::string User :: getLastName() const {
    return lastName;
}

std::string User :: getUserName() const {
    return userName;
}

std::string User :: getPassword() const {
    return password;
}

// Display method
void User :: display () const {
    cout << *this << endl;
}



// I/O stream Operators
std::ostream& operator << (std::ostream& os, const User& p) {
    os << endl;
    os << "First Name: " << p.firstName << endl; 
    os << "Last Name : " << p.lastName << endl; 
    os << "User Name : " << p.userName << endl; 
    os << "Password  : " << p.password << endl; 

    return os; 
}

std::istream& operator >> (std::istream& is, User& p) {

    cout << "\nEnter first name: "; is >> p.firstName;
    cout << "Enter last name : "; is >> p.lastName;
    cout << "Enter user name : "; is >> p.userName; 
    // cout << "Enter password  : "; is >> p.password; // I don,t know if it is good to show password or not ?
    return is;
}