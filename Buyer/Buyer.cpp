#include "Buyer.h"

Buyer :: Buyer () : User () {

}

Buyer :: Buyer (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : User (first, last, user_name, pass) {

}


Buyer* Buyer :: fromJson (json& j) {
    return new Buyer (j["firstName"], j["lastName"], j["userName"], j["password"]);
}


json Buyer :: toJson ( ) { 
    json j; 
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}