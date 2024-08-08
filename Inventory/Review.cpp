#include "Review.h"

Review :: Review(double _rating, const std::string& _comment) : rating(_rating), comment(_comment) {
    
}

Review :: ~Review() {
    
}

// Getters 
double Review :: getRating () const {
    return rating;
}

std::string Review :: getComment () const {
    return comment; 
}

// retrieving data from files
Review Review :: fromJson (json& j) {
    return Review (j["rating"], j["comment"]);
}

json Review :: toJson () {
    json j;
    j["rating"] = this->rating; 
    j["comment"] = this->comment; 
    return j; 
}

// stream I/O operators 
std::ostream& operator << (std::ostream& os, const Review& review) {
    os << "\nRating  : " << review.rating; 
    os << "Comment  : " << review.comment; 
    return os; 
}

std::istream& operator >> (std::istream& is, Review& review) {
    std::cout << "\nEnter your FEEDBACK about this product " << std::endl; 
    do {
        std::cout << "\n Rate this product (1-5): "; 
        is >> review.rating; 
        if (review.rating < 0.0 && review.rating > 6.0)
            std::cout << review.rating  << " is not a valid rating!" << std::endl; 
    } while (review.rating < 0.0 && review.rating > 6.0);

    std::cout << " Any reviews/comments   : ";
    is >> review.comment; 
    return is; 
}