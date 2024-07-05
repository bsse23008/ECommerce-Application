#include "Admin.h"

Admin :: Admin () : Person () {

}

Admin :: Admin (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : Person (first, last, user_name, pass) {

}