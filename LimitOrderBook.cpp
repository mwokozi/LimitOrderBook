#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <algorithm> 
#include <unordered_map>
class Client {
	std::string client_name; 
public:
	Client(std::string name) : client_name(name) {};
};

	

//template <typename T>
class Product { 
	long  ProductID;
	std::string Ticker;
	
	public:
	long  getID() { return this->ProductID; } ;
bool operator ==(const Product& other_prod ) const {
		return (this->ProductID == other_prod.ProductID );};
	Product (long  id, std::string tick ): ProductID(id), Ticker(tick) {};

//		std::vector<T> buyLimitOrderQueue;
//		std::vector<T> sellLimitOrderQueue;
};






/*
template <typename  T, typename P > 
class limitOrderQueues { 
	public:
		static std::vector<T> buyLimitOrderQueue;
		static std::vector<T> sellLimitOrderQueue;
};
*/

enum class  BuyOrSellEnum {Buy,Sell};
                                                              
enum class  CurrencyCodeEnum { GBP,EUR, USD,JPY,AUD,CNY,CHF};

//template <typename T>
/*class limitOrderQueues {
        public:

template <typename T>
                static std::unordered_map<long int,std::vector<T> > buyLimitOrderQueue  ;
template <typename K>
                static std::unordered_map<long int,std::vector<K> > sellLimitOrderQueue ;
};*/



class Order { 

	int Quantity; 

//	enum class  BuyOrSellEnum {Buy,Sell};

//	enum class  CurrencyCodeEnum { GBP,EUR, USD,JPY,AUD,CNY,CHF};

	BuyOrSellEnum Side; 

	double Price; 

	time_t date_time_stamp;

	CurrencyCodeEnum CCY ; 

	Product product ; 

	Client counterparty;
//	 long int InstrumentID ; 

//	std::string ticker; 

class limitOrderQueues { 
	public:
		static std::unordered_map<long int,std::vector<Order>> buyLimitOrderQueue ;
		static std::unordered_map<long int,std::vector<Order>> sellLimitOrderQueue ;
//	buyLimitOrderQueue = {};
//	sellLimitOrderQueue = {};

};
public :





	bool operator < ( const Order& other_ord ) const  {
		if (this->Price != other_ord.Price  ) return this->Price < other_ord.Price ; 
		return this->date_time_stamp < other_ord.date_time_stamp;
	}

	Order (Product p, int  q,double price, CurrencyCodeEnum ccy ,BuyOrSellEnum side, Client cpty , time_t exc_time )  : Quantity(q), product(p), Price( price) ,CCY( ccy) ,Side( side), counterparty( cpty) , date_time_stamp(  exc_time ) {}

	void PlaceOrder () {
	 //Add to order book
	



	if ( this->Side == BuyOrSellEnum::Buy ) 
		{//(this->product.getID()).buyLimitOrderQueue.push_back(*this) ;
		Order::limitOrderQueues::buyLimitOrderQueue.insert({(this->product).getID(), {*this}});
			make_heap(Order::limitOrderQueues::buyLimitOrderQueue[this->product.getID()].begin(),Order::limitOrderQueues::buyLimitOrderQueue[this->product.getID()].end() ) ;	 
	}

		if ( this->Side == BuyOrSellEnum::Sell ) 	 
		{//(this->product.getID()).sellLimitOrderQueue.push_back(*this) ; 

			Order::limitOrderQueues::sellLimitOrderQueue.insert({(this->product).getID(), {*this}});
                        make_heap(Order::limitOrderQueues::sellLimitOrderQueue[this->product.getID()].begin(),Order::limitOrderQueues::sellLimitOrderQueue[this->product.getID()].end() ) ;

	} 
};
	void CancelOrder (){
		//Cancel order if not already filled
	}; 


	int TotalVolume(  ) {

	long int TotalVol; 
	
	for ( auto  order  : limitOrderQueues::buyLimitOrderQueue[this->product.getID()] )  {TotalVol+=order.Price; }; 
	

	return TotalVol;  

} ;
};/*
class limitOrderQueues { 
	public:
		static std::unordered_map<long int,std::vector<Order>> buyLimitOrderQueue ;
		static std::unordered_map<long int,std::vector<Order>> sellLimitOrderQueue ;
};*/

std::unordered_map<long int, std::vector<Order>>
Order::limitOrderQueues::buyLimitOrderQueue{};

std::unordered_map<long int, std::vector<Order>>
Order::limitOrderQueues::sellLimitOrderQueue{};




int main ( int argc, char* argv[] ) {






//	Order::limitOrderQueues::buyLimitOrderQueue = {};
//	Order::limitOrderQueues::sellLimitOrderQueue =  {};
	time_t exc_time =/* ctime::*/time(NULL);
	Client* bank = new Client ("JP Morgan") ;
	Product* stock = new Product( 12345L , "AAPL" );
	Order* order = new    Order (*stock,100, 294.24L , CurrencyCodeEnum::USD  ,BuyOrSellEnum::Buy , *bank  ,exc_time ); 	


	order->PlaceOrder(); 
	std::cout << order->TotalVolume() << std::endl;






return 0;
}
