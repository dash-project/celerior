#include "celerior.h"

	class MyFixture : public FixtureBase{
	void setupFixture(){
		add_variable("units").range(0,5).step(1);
		set_size().range({10,20,30,40});
		add_variable("other").range(1,16).step(times(2));
	}
	CONTAINER(test_vector,std::vector<int>);
	PRE_SAMPLE {
		test_vector.push_back(variables["size"]);
	}
	PRE_ITERATION {
		test_vector.push_back(variables["units"]);
	}
	};
BENCHMARK(Test,MyFixture,1) {
	std::cout << test_vector.size() << " ";
}
int main(){
	Celerior c;
	UserBenchmark_Test test;
	c.run(&test);
	return 0;
}

