#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <chrono>

std::atomic<bool> ready;
std::vector<int> data;

void read_data(){
	while(!ready.load()){
		std::cout<<"Waiting for reading"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2));

	}
	std::cout<<"value is "<<data[0]<<std::endl;
}

void write_data(int value){
	data.push_back(value);
	ready=true;
}

int main(){

	std::thread t1(read_data);
	std::thread t2(write_data,42);

	t1.join();
	t2.join();

}
