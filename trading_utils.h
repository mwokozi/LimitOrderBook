#pragma once
#include <string>
#include <ctime>
#include <unordered_map>
#include <vector>
#ifndef TRADING_UTILS 

#define TRADING_UTILS


namespace trading { 

/*template <typename Ord>
struct  limitOrderQueues {

using productID = long int ; 


	static std::unordered_map<productID, std::vector<Ord > > BuyQueue ;  
	static std::unordered_map<productID, std::vector<Ord > > SellQueue ;
};*/

class Product {

		std::string product_name;

		long int product_id; 

	public:
		using ProductName = ::std::string;
		using ProductID = long int; 
		long int get_product_id  () const;
		
		::std::string get_product_name  () const ;
		void set_product_name( std::string name ) ;
		void set_product_id ( long int id ) ;
	
		Product(ProductName name, ProductID id) ;	
		Product() = default;	
};
class Client {


		std::string client_name; 
		long int client_id;
		int client_risk_score;
	public:
		using ClientName = ::std::string;
		using ClientID = long int;
		using ClientRiskScore = int;
	    
		void set_client_id(ClientID id) ;
		long int get_client_id() const;
		std::string get_client_name() const;
		void set_client_name( ClientName name ) ;
		int get_client_risk_score() const;
		void set_client_risk_score( int risk_score );

		Client(ClientName name, ClientID id , ClientRiskScore risk_score) ;
		Client() = default;
};


enum class BuyOrSellEnum ; // {Buy, Sell};
enum class CurrencyCodeEnum;


class Order :public Product, public  Client {

	using Quantity = long int;
	using OrderID = long int;
	using Price = long double;
	using ExecutionTime = time_t;

	Quantity quantity;
	OrderID order_id;
	BuyOrSellEnum side;
	Price price;
	CurrencyCodeEnum ccy;
	ExecutionTime exec_time;
	struct  limitOrderQueues {

		using productID = long int ;
		static std::unordered_map<productID, std::vector< Order > > BuyQueue ;
		static std::unordered_map<productID, std::vector< Order > > SellQueue ;
};
 
public:
	void place_order();
	void cancel_order();
	void display_queued_volume (   ) const;
	bool operator< ( const Order& other_ord ) const ; 
	void display_order_details() const ;
	void expose_buy_queue(  ) const ;
	void expose_sell_queue(  ) const ;
	
	Order(OrderID order_id, Client client,  Product product, Quantity quantity, Price price, BuyOrSellEnum side, CurrencyCodeEnum ccy, ExecutionTime exec_time) ;
};
};  

//};


#endif /* TRADING_UTILS*/ 
