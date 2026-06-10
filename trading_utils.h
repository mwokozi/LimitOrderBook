
#include <ctime>
#include <iostream> 
#include <string>

namespace trading { 

	class Product {
			unsigned long product_id;
			std::string product_name;
		public: 
			using ID = unsigned long ;
			using Name = std::string ; 
			Product( ID id ,Name product );
			Product ( const Product& product );
			 Product ( Product&& product ); 
			Product& operator=( const Product& product ); 
			Product& operator=( Product&& product );  
			~Product() ;
			std::string get_product_name () const  ; 
			unsigned long get_product_id() const;
			void set_product_name(std::string Name ); 
			void set_product_id ( unsigned long ID ) ;
			
	};

	class Client {
			unsigned long client_id;
			std::string client_name;
			int risk_score;
		public: 
			using ID =  unsigned long ;
			using Name = std::string ; 
			
			Client ( ID  id ,Name client ) ;
			Client( const Client& client ); 
			Client ( Client&& client );
			Client& operator=( const Client& client );
			Client& operator=(  Client&& client );	 
			~Client () ;
			ID get_client_id () const ;
			Name get_client_name () const ;
			int get_risk_score() const; 
			void set_client_id (ID id ) ; 
			void set_client_name (  Name name ); 
			void set_risk_score ( int score ) ; 
	};
	class Order  {

			
	        public:
			      enum class  buy_sell_enum { buy, sell};               	
                              enum class ccy_code_enum ; 
		private:
			unsigned long  order_id;
			buy_sell_enum side;
			ccy_code_enum ccy_code;	
			double  price;
			Client client;
			Product product;
			std::time_t exec_time;
			unsigned long quantity; 
		public:
			Order ( unsigned long  id,  const Client& client , const Product& product, buy_sell_enum side, ccy_code_enum ccy, double Price, std::time_t exec_time, unsigned long quantity )  ;
			bool operator<( const Order& other_order ) const  ;
			bool operator==( const Order& other_order ) const;
			bool operator>( const Order& other_order ) const; 
			
	};		

	struct  limitOrderQueues  { 

		static volatile std::vector<Order> BuyQueue;
		static volatile std::vector<Order> SellQueue; 
		static void place_order( const Order& ord ) ;
		static void cancel_order ( const Order& ord ) ; 
		static void fill_matching_orders () ; 
	};
	
} 
