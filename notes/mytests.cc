#include "fixture_base.h"


int timesTest(int a){
	times tim = times(a);
	int t = tim.mult();
	std::cout << "Testing class times\n\n";
	std::cout << "t(" << a <<").mult() = " << t << "\n";
	return 0;
}
template <class VarType>
void printVec(std::vector<VarType> vec){
	for(auto iter = vec.begin(); iter!=vec.end(); iter++){
		std::cout << *iter << "\n";
		}
}
int fixtureVariableTest(){
	FixtureVariable<int> units = FixtureVariable<int>("units");
	FixtureVariable<int> size = FixtureVariable<int>("size");
	FixtureVariable<double> density = FixtureVariable<double>("density");
	FixtureVariable<int> size3 = FixtureVariable<int>("size3");
	units.range({2,4,8,16,32,64});
	size.range(1000,10000).step(1000);
	density.step(0.1).range(0.1,1.0);
	size3.range(1000,64000).step(times(2));
	std::vector<int> listVec = units.values();
	std::vector<int> rangeStepVec = size.values();
	std::vector<double> stepRangeVec = density.values();
	std::vector<int> rangeStepTimesVec = size3.values();
	std::cout << "\n\nTesting class FixtureVariable\n\n";
	std::cout << "FixtureVariable<int>.range(list):\n" << units.name() << ":\n";
	printVec(listVec);
	std::cout << "FixtureVariable<int>.range().step():\n" << size.name() << ":\n";
	printVec(rangeStepVec);
	std::cout << "FixtureVariable<double>.step().range():\n" << density.name() << ":\n";
	printVec(stepRangeVec);
	std::cout << "FixtureVariable<int>.range().step(times()):\n" << size3.name() << ":\n";
	printVec(rangeStepTimesVec);

	return 0;
}
int main(){
	timesTest(5);
	fixtureVariableTest();
	return 0;
}

