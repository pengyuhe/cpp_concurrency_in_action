#include <mutex>
#include <atomic>

class SpinlockMutex{
private:
	std::atomic_flag flag;
public:
	SpinlockMutex():flag(ATOMIC_FLAG_INIT){}
	void lock(){
		// If false, indiciating it THIS THREAD set it to true (locked it)
		while(flag.test_and_set(std::memory_order_acquire));
	}
	void unlock(){
		flag.clear(std::memory_order_release);
	}
};

int main(){

	SpinlockMutex spinlock_mutex;
	return 0;
}