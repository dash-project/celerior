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
		std::vector<std::chrono::microseconds> times;
		fix -> setupFixture();
		fix -> numSamples();
		fix -> numVar();
		fix -> vecSizes();
		fix -> varNamesFill();
		fix -> setIterations();
		int iterations = fix -> iterations();
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
				for(int j = 0; j < iterations; j++){
					fix -> preIteration(benchVariables);
					auto t1 = Clock::now();
					fix -> UserBenchmark(benchVariables);
					auto t2 = Clock::now();
					auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
					times.push_back(time);
					fix -> postIteration(benchVariables);
				}
				r.add_time(values, fix -> minDuration(times));
				values.clear();
			times.clear();
			fix -> postSample(benchVariables);
		}
		std::cout << r;

	}
		
};
