#include "trading_utils3.h"




enum class ccy_code_enum { GBP, USD, JPY, CHF } ;




trading::Order::Order ( unsigned long  id,  const trading::Client& client , const trading::Product& product, buy_sell_enum side, ccy_code_enum ccy, double price, std::time_t exec_time, unsigned long quantity ) 
	: order_id(id), client(client), product(product), side(side), ccy_code(ccy), price (price), exec_time(exec_time), quantity(quantity) {};
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

