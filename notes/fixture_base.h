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
	int         _times;

};


template <class VarType>
class FixtureVariable {
	typedef FixtureVariable<VarType> self_t;
public:
	FixtureVariable(const std::string & var_name)
	: _name (var_name)
	{ }

	self_t & range(std::initializer_list<VarType> values) {
		_values = values;
		return *this;
	}

	self_t & range(VarType first, VarType last) {
		_rangef = 1;
		_first = first;
		_last  = last;

		if(_stepf == 1) {
			VarType v = first;
			while(v <= last){
				_values.push_back(v);
				v += _stepsize;
			}
		}

		if(_steptf == 1) {
			VarType v = first;
			while(v <= last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;
		
	}

	self_t & step(VarType step_size) {
		_stepf = 1;
		_stepsize = step_size;

		if(_rangef == 1) {
			VarType v = _first;
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
			VarType v = _first;
			while(v <= _last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;

	}

	std::vector<VarType> values() const {
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
	std::vector<VarType> _values;
	VarType              _first;
	VarType              _last;
	VarType              _stepsize;
	int                  _times;
};
template<class VarType>
class FixtureBase
{
public:
	// Map<Dimensions,Values>

	std::map<std::string,FixtureVariable<VarType>> variables() const
	{
		return _variables;
	}

	FixtureVariable<VarType> & add_variable(const std::string & var_name) {
		_variables[var_name]        = FixtureVariable<VarType>(var_name);
		return _variables[var_name];
	}
	//
	FixtureVariable<VarType> & set_units() {
		FixtureVariable<VarType> _units = add_variable("units");
		return _variables["units"];
	}

	FixtureVariable<VarType> & set_size() {
		FixtureVariable<VarType> _size = add_variable("size");
		return _variables["size"];
	}

	//Executed before every sample
	void preSample(const std::map<std::string,int>) {
	}

	//Executed before every iteration
	void preIteration(const std::map<std::string,int>){
	}

	//Executed after every iteration
	void postIteration(const std::map<std::string,int>){
	}

	//Executed after every sample
	void postSample(const std::map<std::string,int>){
	}

	//Number of FixtureVariables
	void numVar() {
		_numVar = _variables.size();
	}

	//Array with sizes of the vectors in the FixtureVariables
	void vecSizes() {
		int vecSize;
		int i = 0;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter) {
			vecSize = iter -> second.values().size();
			_vecSizes[i] = vecSize;
			i++;
		}
	}

	//Number of samples
	void numSamples() {
		int samples = 1;
		int size;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter){
			size = iter -> second.values().size();
			samples *= size;
		}

		_samples = samples;
	}

	//Map with values for a specific run of the benchmark
	std::map<std::string,int> benchVariables(int count){
		std::map<std::string,int> _benchVariables;
		std::string name;
		int value;
		int now = 1;
		int rest;
		int position;
		for(auto iter = _variables.begin(); iter != _variables.end(); ++iter){
			name = iter -> second.name();
			if(now != _numVar){
				rest = 1;
				for(int i = now; i < _numVar; i++){
					rest *= _vecSizes[i];
				}
				position = count/rest;
				value = iter -> second.value()[position];
			}
			else{
				position = count % _vecSizes[_numVar - 1];
				value = iter -> second.value()[position];
			}
			_benchVariables[name] = value;

		}

		return _benchVariables;
	}


private:
	std::map<std::string,FixtureVariable<VarType>>        _variables;
	int                                                   _numVar;
	int                                                   _samples;
	std::vector<int>                                      _vecSizes;
};

