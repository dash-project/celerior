#include "Results.h"

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
		std::map<std::string,int> benchVariables;
		std::vector<int> values;
		std::vector<std::string> names;
		fix -> setupFixture();
		fix -> numSamples();
		fix -> numVar();
		fix -> vecSizes();
		fix -> varNamesFill();
		benchVariables = fix -> benchVariables(0);
		for(auto iter = benchVariables.begin();iter != benchVariables.end(); ++iter){
			names.push_back(iter -> first);
		}
		Results r = Results(names);
		int samples = fix -> samples();
		for(int k = 0; k < samples; k++){
			benchVariables = fix -> benchVariables(k);
			for(auto iter = benchVariables.begin(); iter != benchVariables.end(); ++iter){
				values.push_back(iter -> second);	
			}
			fix -> preSample(benchVariables);
			auto t1 = Clock::now();
			fix -> UserBenchmark(benchVariables);
			auto t2 = Clock::now();
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
			r.add_time(values,time);
//			std::cout << time << " microseconds\n";
			values.clear();
		}
		std::cout << r;

	}
		
};
