
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
		_first = from;
		_last  = last;
		return *this;
	}

	// TODO: also allow add_variable.step(2).range(10,20)
	template <class Numeric>
	self_t & step(Numeric step_size) {
		VarType v = _first;
		while(v <= _last) {
			_values.push_back(v);
			v += step_size;
		}
		return *this;
	}

private:
	std::vector<VarType> _values;
	VarType              _first;
	VarType              _last;
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

};

