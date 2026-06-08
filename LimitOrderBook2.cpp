#include "trading_utils.h"
#include <iostream> 
#include <algorithm>

//intialization of enum class for buy or sell side of order
enum class trading::BuyOrSellEnum  {Buy, Sell};
//intialization of enum class for currency code
enum class trading::CurrencyCodeEnum {
    USD, EUR, GBP, JPY, CHF, CAD, AUD, NZD, CNY,BRL};



// Product class implementation
long int trading::Product::get_product_id  () const {
    return product_id;
};

void trading::Product::set_product_id(long int id) {
    product_id = id;
}; 

std::string trading::Product::get_product_name() const {
    return product_name;
};

void trading::Product::set_product_name(std::string name) {
    product_name = name;
};

trading::Product::Product(ProductName name, ProductID id) : product_name(name), product_id(id) {};

// Client class implementation


long int trading::Client::get_client_id() const {
    return client_id;
};
void trading::Client::set_client_id(ClientID id) {
    client_id = id;
};
std::string trading::Client::get_client_name() const {
    return client_name;
};
void trading::Client::set_client_name(std::string name) {
    client_name = name;
};
int trading::Client::get_client_risk_score() const {
    return client_risk_score;
};
void trading::Client::set_client_risk_score(int risk_score) {
    client_risk_score = risk_score;
};
trading::Client::Client(ClientName name, ClientID id, ClientRiskScore risk_score) : client_name(name), client_id(id), client_risk_score(risk_score) {};

//Initialization of limit order queues
std::unordered_map<trading::Order::limitOrderQueues::productID, std::vector<trading::Order>> trading::Order::limitOrderQueues::BuyQueue{};
std::unordered_map<trading::Order::limitOrderQueues::productID, std::vector<trading::Order>> trading::Order::limitOrderQueues::SellQueue{};

// Order class implementation
void trading::Order::place_order() {
    // Implementation for placing an order
    if (side == BuyOrSellEnum::Buy ) {
        trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()].push_back(*this);
        make_heap(trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()].begin(), trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()].end(), [=](const trading::Order a, const trading::Order b) { return (a < b); }); // Max-heap for buy orders
            // return a < b; // Max-heap for buy orders
         
    } else {
        trading::Order::limitOrderQueues::SellQueue[this->get_product_id()].push_back(*this);
        make_heap(trading::Order::limitOrderQueues::SellQueue[this->get_product_id()].begin(), trading::Order::limitOrderQueues::SellQueue[this->get_product_id()].end(), [&](const trading::Order& a, const trading::Order& b) {
             return !(a < b); // Min-heap for sell orders
        });
    }
};


void trading::Order::cancel_order() {
    // Implementation for canceling an order
    std::vector<trading::Order>& order_queue = (this->side == BuyOrSellEnum::Buy) ? trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()] : trading::Order::limitOrderQueues::SellQueue[this->get_product_id()];
    auto it = std::find_if(order_queue.begin(), order_queue.end(), [&](const trading::Order& o) { return o.order_id == this->order_id; });
    if (it != order_queue.end()) {
        order_queue.erase(it);
    }

};

void trading::Order::display_queued_volume() const {
    long int buy_volume = 0;
    long int sell_volume = 0;

    for (const auto& buy_order : trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()]) {
        buy_volume += buy_order.quantity;
    }

    for (const auto& sell_order : trading::Order::limitOrderQueues::SellQueue[this->get_product_id()]) {
        sell_volume += sell_order.quantity;
    }
    //std::cout<< "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Total Buy Volume for Product " << this->get_product_id() << ": " << buy_volume << std::endl;
    std::cout << "Total Sell Volume for Product " << this->get_product_id() << ": " << sell_volume << std::endl;
    std::cout<< "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    long int net_volume = buy_volume - sell_volume;
    std::cout << "Net Volume for Product " << this->get_product_id() << ": " << net_volume << std::endl;
std::cout<< "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
 
};

bool trading::Order::operator<(const Order& other_ord) const {
    if (this->exec_time == other_ord.exec_time && this->quantity == other_ord.quantity && this->price != other_ord.price    ) {
        return this->price < other_ord.price; // Max-heap for buy orders
    }
    if (this->exec_time == other_ord.exec_time && this->price == other_ord.price && this->quantity != other_ord.quantity) {
           return this->quantity <= other_ord.quantity; // Higher quantity has higher priority when execution time and price are the same
    }
    if (this->exec_time == other_ord.exec_time && this->price == other_ord.price && this->quantity == other_ord.quantity) {
        return this->get_client_risk_score() >= other_ord.get_client_risk_score(); // Lower risk score has higher priority when execution time, price, and quantity are the same
    }
    return this->exec_time <= other_ord.exec_time; // Earlier execution time has higher priority
};

void trading::Order::display_order_details() const {

    std::cout << "Order ID: " << this->order_id << ", Client ID: " << this->get_client_id() << ", Product ID: " << this->get_product_id() << ", Quantity: " << this->quantity << ", Price: " << this->price << ", Side: " << (this->side == BuyOrSellEnum::Buy ? "Buy" : "Sell") << std::endl;
        std::cout<< "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
};

void trading::Order::expose_buy_queue() const {
    std::cout << "Current Buy Orders for Product " << this->get_product_id() << ":" << std::endl;
    for (const auto& buy_order : trading::Order::limitOrderQueues::BuyQueue[this->get_product_id()]) {
        buy_order.display_order_details();
    }
};

void trading::Order::expose_sell_queue() const {
    std::cout << "Current Sell Orders for Product " << this->get_product_id() << ":" << std::endl;
    for (const auto& sell_order : trading::Order::limitOrderQueues::SellQueue[this->get_product_id()]) {
        sell_order.display_order_details();
    }
};



trading::Order::Order(OrderID order_id, trading::Client client,  trading::Product product, Quantity quantity, Price price, BuyOrSellEnum side, CurrencyCodeEnum ccy, ExecutionTime exec_time) : order_id(order_id), exec_time(exec_time), quantity(quantity), price(price), side(side), ccy(ccy) {


    this->set_client_id(client.get_client_id());
    this->set_client_name(client.get_client_name());
    this->set_client_risk_score(client.get_client_risk_score());
    this->set_product_id(product.get_product_id());
    this->set_product_name(product.get_product_name());
    //this->exec_time = time(0); // Set execution time to current time
};    


int main() {

    //sample/test products
    trading::Product product("Apple Inc.", 1);
    trading::Product product2("Microsoft Corp.", 2);
    trading::Product product3("Amazon.com Inc.", 3);
    trading::Product product4("Alphabet Inc.", 4);
    trading::Product product5("Facebook Inc.", 5);     
    trading::Product product6("Tesla Inc.", 6);
    
    //sample/test clients
    trading::Client client("John Doe", 12345, 5);
    trading::Client client2("Jane Smith", 67890, 3);
    trading::Client client3("Alice Johnson", 54321, 4);
    trading::Client client4("Bob Brown", 98765, 2);
    trading::Client client5("Charlie Davis", 13579, 1);
    

    //sample buy orders
    trading::Order order( 10233L , client, product, 100, 150.50, trading::BuyOrSellEnum::Buy, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order2( 10234L , client2, product, 200, 150.50, trading::BuyOrSellEnum::Buy, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order3( 10235L , client3, product5, 150, 250.75, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order4( 10236L , client4, product3, 50, 350.25, trading::BuyOrSellEnum::Buy, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order5( 10237L , client5, product2, 300, 450.00, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order6( 10238L , client, product, 75, 850.50, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    
    //sample sell orders
    trading::Order order7( 10239L , client2, product3, 120, 350.00, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order8( 10240L , client3, product4, 80, 450.50, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order9( 10241L , client4, product5, 200, 550.75, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order10( 10242L , client5, product, 100, 650.25, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order11( 10243L , client, product, 150, 750.00, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));
    trading::Order order12( 10244L , client2, product3, 250, 850.50, trading::BuyOrSellEnum::Sell, trading::CurrencyCodeEnum::USD, time(0));

    //place orders and print confirmation
    order.place_order();
     std::printf( "Order placed with ID: %li\n", order.get_client_id() );
    order2.place_order();
     std::printf( "Order placed with ID: %li\n", order2.get_client_id() );
    order3.place_order();
     std::printf( "Order placed with ID: %li\n", order3.get_client_id() );
    order4.place_order();
     std::printf( "Order placed with ID: %li\n", order4.get_client_id() );
    order5.place_order();
     std::printf( "Order placed with ID: %li\n", order5.get_client_id() );
    order6.place_order();
     std::printf( "Order placed with ID: %li\n", order6.get_client_id() );  
    order11.place_order();  
        std::printf( "Order placed with ID: %li\n", order11.get_client_id() );

 
//Expose the current state of the limit order book for product 1    
order.expose_buy_queue();
order.expose_sell_queue();


//Display the total queued volume for product 1,2,3,4,5,6
/*order.display_queued_volume();
order2.display_queued_volume();
order3.display_queued_volume();
order4.display_queued_volume();
order5.display_queued_volume();
order6.display_queued_volume();
*/
    return 0;
}