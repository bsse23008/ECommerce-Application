#include "Seller.h"

Seller :: Seller () : Person () {

}

Seller :: Seller (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : Person (first, last, user_name, pass) {

}