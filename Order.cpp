#include "trading_utils.h"




enum class ccy_code_enum { GBP, USD, JPY, CHF } ;




trading::Order::Order ( unsigned long  id,  const trading::Client& client , const trading::Product& product,
buy_sell_enum side, ccy_code_enum ccy, double price, std::time_t exec_time, unsigned long quantity ) 
	: order_id(id), client(client), product(product), side(side), ccy_code(ccy), price (price), exec_time(exec_time), quantity(quantity), unfilled_quantity (quantity)  {
	if ( this->side == buy_sell_enum::buy && !trading::LimitOrderQueues::BuyQueue.contains(this->product.get_product_id()) ) {
		//Intialize Buy queue for specific product
		trading::LimitOrderQueues::BuyQueue[ this->product.get_product_id() ].push_back(*this) ;
		std::make_heap( trading::LimitOrderQueues::BuyQueue[this->product.get_product_id()].begin(),trading::LimitOrderQueues::BuyQueue[this->product.get_product_id()].end() ) ;
	}
	else if ( this->side == buy_sell_enum::buy  ){ 
		//Add order to existing product buy queue 
		trading::LimitOrderQueues::BuyQueue.at(this->product.get_product_id()).push_back(*this);	
		std::push_heap(trading::LimitOrderQueues::BuyQueue[this->product.get_product_id()].begin(),trading::LimitOrderQueues::BuyQueue[this->product.get_product_id()].end() ) ;
	}
/////
  if ( this->side == buy_sell_enum::sell && !trading::LimitOrderQueues::SellQueue.contains(this->product.get_product_id()) ) {
                //Intialize Sell queue for specific product
                trading::LimitOrderQueues::SellQueue[ this->product.get_product_id() ].push_back(*this) ;
                std::make_heap( trading::LimitOrderQueues::SellQueue[this->product.get_product_id()].begin(),trading::LimitOrderQueues::SellQueue[this->product.get_product_id()].end(), []( Order o1, Order o2) {    
                        return o1 > o2 ;
                } 
 ) ;
        }
	
        else if ( this->side == buy_sell_enum::sell  ){
        	//Add order to existing product sell queue 
	        trading::LimitOrderQueues::SellQueue[this->product.get_product_id()].push_back(*this);
                std::push_heap(trading::LimitOrderQueues::SellQueue[this->product.get_product_id()].begin(),trading::LimitOrderQueues::SellQueue[this->product.get_product_id()].end() ) ;
        }



};

//Getters & Setters
trading::Order::buy_sell_enum  trading::Order::get_side() const {
	return side; 
};
double trading::Order::get_price() const {
	return price;
}; 
unsigned long trading::Order::get_quantity() const { 
	return quantity;
};

unsigned long trading::Order::get_unfilled_quantity () const { 

return unfilled_quantity;
};

void trading::Order::fill() {
	is_filled = true ; 
};


void trading::Order::set_unfilled_quantity ( unsigned long fill ) {
                                //throw exception if fill > initial quantity
                                unfilled_quantity = fill; 
                        };



//Methods







//Comparison operator overloads
bool trading::Order::operator<( const Order& other_order ) const { 

	return ( price != other_order.price )?(price<other_order.price): 
		(exec_time != other_order.exec_time)?(exec_time<other_order.exec_time):
		(quantity != other_order.quantity)?(quantity<other_order.quantity): 
		(order_id < other_order.order_id ); 
};

bool trading::Order::operator==( const trading::Order& other_order ) const { 

	return ( order_id == other_order.order_id);
};

bool trading::Order::operator>( const Order& other_order ) const {

	return !( *this < other_order ); 

};

