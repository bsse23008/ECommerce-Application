#include "Admin.h"

Admin :: Admin () : User () {

}

Admin :: Admin (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : User (first, last, user_name, pass) {

}

// Json to object conversion 
Admin* Admin :: fromJson (json& j) {
    return new Admin (j["firstName"], j["lastName"], j["userName"], j["password"]);
}


// Object to Json conversion
json Admin :: toJson ( ) { 
    json j; 
    j["firstName"] = this->firstName;
    j["lastName"] = this->lastName;
    j["userName"] = this->userName;
    j["password"] = this->password;
    return j; 
}