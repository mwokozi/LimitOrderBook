#include "trading_utils3.h"

//using ID = unsigned long ; using Name= std::string

//Constructors, Assignment operators  and destructor
trading::Product::Product ( trading::Product::ID  id ,trading::Product::Name product ): product_id(id), product_name(product) {} ;
trading::Product::Product( const trading::Product& product ) = default;
trading::Product::Product ( trading::Product&& product ) = default ;
trading::Product& trading::Product::operator=( const trading::Product& product ) =default;
trading::Product& trading::Product::operator=(  trading::Product&& product ) = default ;
trading::Product::~Product ()=  default ;




//Getters and Setters 

trading::Product::ID trading::Product::get_product_id () const { 
	return product_id;
};
                        

trading::Product::Name trading::Product::get_product_name () const{ 
	return product_name;
 };

void trading::Product::set_product_id (ID id ) {

	product_id = id;
};

void trading::Product::set_product_name (  Name name ) { 
	product_name = name;
};



                    
                    
                    
                    
                    
                    

