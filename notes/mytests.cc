#include "celerior.h"

	class MyFixture : public FixtureBase{
	void setupFixture(){
		add_variable("units").range(0,5).step(1);
		set_size().range({10,20,30,40});
	}
	};
BENCHMARK(Test,MyFixture) {
	std::cout << variables["size"] << " ";
	for(int i = 0; i <= variables["units"]; i++){
		std::cout << "test ";
	}	
	std::cout << "\n";
}
int main(){
	/*MyFixture fix;
	results_test();
	for(auto & iter : range){
		std::cout << iter << " ";
	}
	for(auto & iter : range2){
		std::cout << iter << " ";
	}
	for(auto & iter : liste){
		std::cout << iter << " ";
	}
	for(auto & iter : _variableNames){
		std::cout << iter << " ";
	}*/
	Celerior c;
	UserBenchmark_Test test;
	c.run(&test);
	return 0;
}

