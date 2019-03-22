#include "Results.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
class Celerior
{
	
public:
	void runAll(std::vector<FixtureBase*> fix_vec){
		for(auto & i : fix_vec){
			run(i);
		}
	}

	void run(FixtureBase * fix){
		auto t1 = Clock::now();
		fix -> UserBenchmark();
		auto t2 = Clock::now();
		auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		std::cout << time << " microseconds\n";

	}
		
};
