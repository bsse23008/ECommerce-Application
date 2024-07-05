#include "Buyer.h"

Buyer :: Buyer () : Person () {

}

Buyer :: Buyer (
    const std::string & first,
    const std::string & last,
    const std::string & user_name,
    const std::string & pass) : Person (first, last, user_name, pass) {

}