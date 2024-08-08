#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <sstream>
#include <array>
#include <typeinfo> // User-defined types Identification
#include "./../nlohmann/json.hpp"
using json = nlohmann ::json;
using std::endl;
using std::cout;
using std::cin;

class User
{
    friend std::ostream& operator << (std::ostream& os, const User& p);
    friend std::istream& operator >> (std::istream& is, User& p);
public:
    User();
    User(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

    User(const User &) = default;
    virtual ~User() = default; 

    void setFirstName(const std::string &);
    void setLastName(const std::string &);
    void setUserName(const std::string &);
    void setPassword(const std::string &);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getUserName() const;
    std::string getPassword() const;

    virtual void display () const; 
    virtual void dashBoard () = 0; // Every derived class must implement this method :)
    virtual json& toJson (json& j) const = 0; 
    // virtual static User* fromJson (json& j) const = 0;  

protected:
    std::string firstName, lastName, userName, password;

}; // Abstract class User

#endif // _USER_H_