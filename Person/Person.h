#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "./../nlohmann/json.hpp"
using json = nlohmann ::json;
using std::endl;
using std::cout;


class Person
{
    friend std::ostream& operator << (std::ostream& os, const Person& p);
    friend std::istream& operator >> (std::istream& is, Person& p);
public:
    Person();
    Person(
        const std::string &,
        const std::string &,
        const std::string &,
        const std::string &);

    Person(const Person &) = default;

    void setFirstName(const std::string &);
    void setLastName(const std::string &);
    void setUserName(const std::string &);
    void setPassword(const std::string &);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getUserName() const;
    std::string getPassword() const;

    virtual void display () const; 

private:
    std::string firstName, lastName, userName, password;

}; // Abstract class Person

#endif // _PERSON_H_