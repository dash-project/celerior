#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

class times {
public:
	times(const int mult)
	: _times(mult)
	{}

	int mult() const {
		return _times;
	}

private:
	int              _times;

};
class FixtureVariable {
	typedef FixtureVariable self_t;
public:
	FixtureVariable(const std::string & var_name)
	: _name (var_name)
	{ }

	self_t & range(std::initializer_list<int> values) {
		_values = values;
		return *this;
	}

	self_t & range(int first, int last) {
		_rangef = 1;
		_first = first;
		_last  = last;

		if(_stepf == 1) {
			int v = first;
			while(v <= last){
				_values.push_back(v);
				v += _stepsize;
			}
		}

		if(_steptf == 1) {
			int v = first;
			while(v <= last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;
	}

	self_t & step(int step_size) {
		_stepf = 1;
		_stepsize = step_size;

		if(_rangef == 1) {
			int v = _first;
			while(v <= _last) {
				_values.push_back(v);
				v += step_size;
			}
		}
		return *this;
	}

	self_t & step(times mult) {
		_steptf = 1;
		_times = mult.mult();

		if(_rangef == 1){
			int v = _first;
			while(v <= _last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;

	}

	std::vector<int> values() const{
		return _values;
	}

	std::string name() const {
		return _name;
	}
private:
	std::string          _name;
	int                  _steptf;
	int                  _rangef;
	int                  _stepf;
	std::vector<int>     _values;
	int                  _first;
	int                  _last;
	int                  _stepsize;
	int                  _times;
};
class FixtureBase
{
public:


	// Map<Dimensions,Values>
	std::vector<FixtureVariable> variables() const
	{
		return _variables;
	}

	FixtureVariable & add_variable(const std::string & var_name) {
		FixtureVariable fix = FixtureVariable(var_name);
		_variables.push_back(fix);
		return _variables.back();
	}
	FixtureVariable & set_units() {
		FixtureVariable units = add_variable("units");
		return _variables.back();
	}
	
	FixtureVariable & set_size() {
		FixtureVariable size = add_variable("size");
		return _variables.back();
	}

	//Setup the FixtureVariables here
	virtual void setupFixture(){
	}

	//Executed before every sample
	virtual void preSample(std::map<std::string,int> m) {
	}

	//Executed before every iteration
	virtual void preIteration(std::map<std::string,int> m){
	}

	//Executed after every iteration
	virtual void postIteration(std::map<std::string,int> m){
	}

	//Executed after every sample
	virtual void postSample(std::map<std::string,int> m){
	}


	//Number of FixtureVariables
	void numVar() {
		_numVar = _variables.size();
	}

	//Array with sizes of the vectors in the FixtureVariables
	void vecSizes() {
		int vecSize;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter) {
			vecSize = iter -> values().size();
			_vecSizes.push_back(vecSize);
		}
	}

	//Number of samples
	void numSamples() {
		int samples = 1;
		int size;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter){
			size = iter -> values().size();
			samples *= size;
		}

		_samples = samples;
	}

	void varNamesFill() {
		for(auto iter = _variables.begin(); iter != _variables.end(); iter++){
			_varNames.push_back(iter -> name());
		}
	}

	//Map with values for a specific run(count) of the benchmark
	std::map<std::string,int> benchVariables(int count){
		std::map<std::string,int> _benchVariables;
		std::string name;
		int value;
		int now = 1;
		int rest;
		int position;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter){
			name = iter -> name();
			if(now != _numVar){
				rest = 1;
				for(int i = now; i < _numVar; i++){
					rest *= _vecSizes[i];
				}
				position = (count/rest) % (_vecSizes[now-1]);
				value = iter -> values()[position];
				now++;
			}
			else{
				position = count % _vecSizes[_numVar - 1];
				value = iter -> values()[position];
			}
			_benchVariables[name] = value;

		}

		return _benchVariables;
	}

	int numVar() const {
		return _numVar;
	}

	int samples() const {
		return _samples;
	}

	std::vector<int> vecSizes() const {
		return _vecSizes;
	}

	std::vector<std::string> varNames() const {
		return _varNames;
	}


	virtual void UserBenchmark(std::map<std::string,int> variables){}

protected:
	std::vector<FixtureVariable>                          _variables;
	int                                                   _numVar;
	int                                                   _samples;
	std::vector<int>                                      _vecSizes;
	std::vector<std::string>                              _varNames;
};

