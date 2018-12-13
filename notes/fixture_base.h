class times {
public:
	times(const Numeric mult) 
	: _times(mult)
	{}

	Numeric mult() {
		return _times;
	}

}


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
		_first = from;
		_last  = last;

		if(_stepf == 1) {
			VarType v = first;
			while(v <= last){
				_values.push_back(v);
				v += _stepsize;
			}
		}

		if(steptf == 1) {
			VarType v = first;
			while(v <= last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;
		
	}

	// TODO: also allow add_variable.step(2).range(10,20)
	template <class Numeric>
	self_t & step(Numeric step_size) {
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
		steptf = 1;
		_times = mult.mult;

		if(_rangef == 1){
			VarType v = _first;
			while(v <= _last) {
				_values.push_back(v);
				v *= _times;
			}
		}
		return *this;

	}
private:
	int                  _steptf;
	int                  _rangef;
	int                  _stepf;
	std::vector<VarType> _values;
	VarType              _first;
	VarType              _last;
	Numeric              _stepsize;
	Numeric              _times;
};

class FixtureBase
{
public:
	// Map<Dimensions,Values>
	std::map<std::string,std::vector<int>> variables() const
	{
		return _variables;
	}

	FixtureVariable & add_variable(const std::string & var_name) {
		_variables[var_name]        = FixtureVariable(var_name);
		return _variables[var_name];
	}
	
	FixtureVariable & set_units() {
		FixtureVariable _units = add_variable("units");
		return _units;
	}

	FixtureVariable & set_size() {
		FixtureVariable _size = add_variable("size");
		return _size;
	}
};

