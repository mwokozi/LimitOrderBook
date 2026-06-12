#include "trading_utils.h"

//using ID = unsigned long ; using Name= std::string

//Constructors, Assignment operators  and destructor
trading::Client::Client ( trading::Client::ID  id ,trading::Client::Name client ): client_id(id), client_name(client) {} ;
trading::Client::Client( const trading::Client& client ) = default;
trading::Client::Client ( trading::Client&& client ) = default ;
trading::Client& trading::Client::operator=( const trading::Client& client ) =default;
trading::Client& trading::Client::operator=(  trading::Client&& client ) = default ;
trading::Client::~Client ()=  default ;




//Getters and Setters 

trading::Client::ID trading::Client::get_client_id () const { 
	return client_id;
};
                        

trading::Client::Name trading::Client::get_client_name () const{ 
	return client_name;
 };

int trading::Client::get_risk_score() const { 
	return risk_score;
};

void trading::Client::set_client_id (ID id ) {

	client_id = id;
};

void trading::Client::set_client_name (  Name name ) { 
	client_name = name;
};

void trading::Client::set_risk_score ( int score ) {
	risk_score = score;; 
};

                    
                    
                    
                    
                    
                    

