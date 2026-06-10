#include <iostream>
#include <algorithm>
#include "trading_utils3.h"

//Product implementation


using ID = unsigned long ;
using Name = std::string ; 
trading::Product::Product( ID id ,Name product ): product_id(id), product_name (product){};
trading::Product::Product ( const trading::Product& product ) { 
	product_id = product.product_id;
	product_name = product.product_name;
} ;
                       





trading::Product::Product ( trading::Product&& product ){ 
	product_id = product.product_id;
	product_name = product.product_name;
	product.product_id = 0;
	product.product_name = ""; //??
};

trading::Product& trading::Product::operator=( const Product& product ) { 

	product_id = product.product_id;
        product_name = product.product_name;
	return *this;
};




trading::Product& trading::Product::operator=( trading::Product&& product ){
	
	product_id = product.product_id;
        product_name = product.product_name;
	product.product_id = 0;
	product.product_name= ""; 
        return *this;
}	


;  
   
trading::Product::~Product() { 
	product_id = 0;
	product_name = "";
};	
std::string trading::Product::get_product_name () const {

	return product_name;
}; 
 unsigned long trading::Product::get_product_id() const{
	return product_id;
};

void trading::Product::set_product_name(std::string Name ){ 
	product_name= Name;
} 
 
void trading::Product::set_product_id ( unsigned long id ) {
	product_id= id ;
}





