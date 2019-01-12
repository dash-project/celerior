#include "fixture_base.h"

template<class VarType>
void timesTest(VarType a){
	auto tim = times<VarType>(a);
	auto t = tim.mult();
	std::cout << "Testing class times\n\n";
	std::cout << "t(" << a <<").mult() = " << t << "\n";
}
template <class VarType>
void printVec(std::vector<VarType> vec){
	for(auto iter = vec.begin(); iter!=vec.end(); iter++){
		std::cout << *iter << "\n";
		}
}
void fixtureVariableTest(){
	FixtureVariable<int> units = FixtureVariable<int>("units");
	FixtureVariable<int> size = FixtureVariable<int>("size");
	FixtureVariable<double> density = FixtureVariable<double>("density");
	FixtureVariable<int> size3 = FixtureVariable<int>("size3");
	units.range({2,4,8,16,32,64});
	size.range(1000,10000).step(1000);
	density.step(0.1).range(0.1,1.0);
	size3.range(1000,64000).step(times<int>(2));
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
}

void fixtureBaseTest(){
	std::cout << "\n\n Testing class FixtureBase\n\n Adding FixtureVariables:\n";
	FixtureBase<int> fb          = FixtureBase<int>();
	FixtureVariable<int> units   = fb.add_variable("units").range(2,64).step(times<int>(2));
	printVec(units.values());
	FixtureVariable<int> size    = fb.set_size().step(1000).range(1000,10000);
	printVec(size.values());
	FixtureVariable<int> x   = fb.add_variable("x").range({1,2});
	printVec(x.values());

	fb.numVar();
	int var = fb.get_numVar();
	std::cout << "\n" << var << "\n";
	fb.numSamples();
	int samples = fb.get_samples();
	std::cout << "\n" << samples << "\n";
	fb.vecSizes();
	std::vector<int> Sizes = fb.get_vecSizes();
	std::cout << "\n Sizes of variable vectors:";
	for(auto iter = Sizes.begin(); iter != Sizes.end(); iter++){
		std::cout << " " << *iter;
	}

	for(int count = 0; count < samples; count++){
		std::map<std::string,int> expValues = fb.benchVariables(count);
	        std::cout << "\nRun "  << count << ":\t";
		for (auto iter = expValues.begin(); iter!=expValues.end();++iter){
			std::cout << iter -> first << ": " << iter -> second << "\t";
		}
	}


}
int main(){
	timesTest(5.0);
	//fixtureVariableTest();
	fixtureBaseTest();
	return 0;
}

