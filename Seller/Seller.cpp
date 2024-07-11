#include "Seller.h"

Seller :: Seller () : User () {

}

Seller :: Seller (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : User (first, last, user_name, pass) {

}

Seller* Seller :: fromJson (json& j) {
    return new Seller (j["firstName"], j["lastName"], j["userName"], j["password"]);
}


json Seller :: toJson ( ) { 
    json j; 
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}