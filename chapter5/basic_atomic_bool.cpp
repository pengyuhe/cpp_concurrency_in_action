#include <atomic>
#include <iostream>

int main(){

	// Basic value set.
	std::atomic<bool> b(false);
	bool x = b.load(std::memory_order_acquire);
	b.store(true);
	x = b.exchange(false,std::memory_order_acq_rel);
	// x equals b befoer exchange, which is true;
	// b is exchanged to false.
	std::cout<<"x= "<<x<< " b= "<<b.load()<<std::endl;
	std::cout<<std::endl;

	// compare and exchange
	b.store(false);
	bool expected = false;
	while(1){
        // If compare_exchange_weak succeed, function returns
        // Else if expected value changed to true, means it got assigned from b.load()
        // which is already a true.
		bool result = (!b.compare_exchange_weak(expected,true) && !expected);
		std::cout<<"b = "<<b.load()<<" expected= "<<expected<<" result= "<<result<<std::endl;
		if(!result){
			break;
		}
	}

	std::cout<<"After loop b = "<<b.load()<<" expected= "<<expected<<std::endl;

}
