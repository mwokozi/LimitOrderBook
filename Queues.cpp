#include "trading_utils.h"
#include <unordered_map>
#include <vector>


 
                





void  trading::LimitOrderQueues::fill_matching_orders ( trading::Product& prod  ){ 
	
	using trading::LimitOrderQueues;
	unsigned int prod_id = prod.get_product_id();
	trading::Order& topBuyOrder = BuyQueue.at(prod_id).front();
	trading::Order& topSellOrder = SellQueue.at(prod_id).front(); 	
	

	while  ( topBuyOrder.get_price()  >= topSellOrder.get_price() ) {
		if ( topBuyOrder.get_unfilled_quantity()  == topSellOrder.get_unfilled_quantity() )  {
				//update order fill time
			topBuyOrder.set_unfilled_quantity(0);
			topBuyOrder.fill(); 
			pop_heap( BuyQueue.at(prod_id).begin(), BuyQueue.at(prod_id).end() ) ; 
			BuyQueue.at(prod_id).pop_back();  
		//Make record of fill 	
			//update sell order fill time
			topSellOrder.set_unfilled_quantity(0);
                        topSellOrder.fill(); 
                        pop_heap( BuyQueue.at(prod_id).begin(), BuyQueue.at(prod_id).end() ) ; 
                        BuyQueue.at(prod_id).pop_back();
		//Make record of fill
	}
	









 		else if ( topBuyOrder.get_unfilled_quantity()  < topSellOrder.get_unfilled_quantity() ) { 
			
                        
			//Update order fill time
			topBuyOrder.set_unfilled_quantity(0);
                        topBuyOrder.fill(); 
                        pop_heap( BuyQueue.at(prod_id).begin(), BuyQueue.at(prod_id).end() ) ; 
                        BuyQueue.at(prod_id).pop_back();
			//Make record of buy fill in record class 
		                 //update sell order fill time
                        unsigned long int new_unfilled_quantity = topSellOrder.get_unfilled_quantity() - topBuyOrder.get_unfilled_quantity();
			topSellOrder.set_unfilled_quantity( new_unfilled_quantity );
                        topSellOrder.fill(); 
                        pop_heap( BuyQueue.at(prod_id).begin(), BuyQueue.at(prod_id).end() ) ; 
                        BuyQueue.at(prod_id).pop_back();
                //Make record of fill
		}

                else if ( topBuyOrder.get_unfilled_quantity()  >  topSellOrder.get_unfilled_quantity() ) { 
                        
                        
                        //Update order fill time
                        topSellOrder.set_unfilled_quantity(0);
                        topSellOrder.fill();
                        pop_heap( SellQueue.at(prod_id).begin(), SellQueue.at(prod_id).end() ) ;
                        SellQueue.at(prod_id).pop_back();
                        //Make record of buy fill in record class 
                                 //update sell order fill time
                        unsigned long int new_unfilled_quantity = topBuyOrder.get_unfilled_quantity() - topBuyOrder.get_unfilled_quantity();
                        topBuyOrder.set_unfilled_quantity( new_unfilled_quantity );
                        topBuyOrder.fill(); 
                        pop_heap( BuyQueue.at(prod_id).begin(), BuyQueue.at(prod_id).end() ) ; 
                        BuyQueue.at(prod_id).pop_back();
                //Make record of fill
                }








}
}; 
	

