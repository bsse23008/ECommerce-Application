#ifndef _REVIEW_H_
#define _REVIEW_H_

#include <iostream>
#include <sstream>
#include <fstream> 
#include "../nlohmann/json.hpp"
using json = nlohmann :: json;

class Review
{
    // Friend functions for stream I/O operators.
    friend std::ostream& operator << (std::ostream& os, const Review& review); 
    friend std::istream& operator >> (std::istream& is, Review& review); 
private:
    double rating;
    std::string comment;
public:
    Review(double, const std::string&);
    ~Review();

    // Getters 
    double getRating () const;
    std::string getComment () const;

    // Methods to load data from files
    static Review fromJson (json& j); 
    json toJson ();
};


#endif // _REVIEW_H_
