#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <sstream>
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

    void setFirstName(const std::string &);
    void setLastName(const std::string &);
    void setUserName(const std::string &);
    void setPassword(const std::string &);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getUserName() const;
    std::string getPassword() const;

    virtual void display () const; 

protected:
    std::string firstName, lastName, userName, password;

}; // Abstract class User

#endif // _USER_H_