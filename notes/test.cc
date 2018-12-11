void main()
{
	run();
}

class SortFixture : public TestFixture
{
public:
	SortFixture()
	{
	}

	//Map<Dimensions,Values>
	std::map<std::string,std::vector<int>> getVariables()
	{
		std::map<std::string, std::vector<int>> varMap;

		std::vector<int> units;
		units.push_back(1);
		units.push_back(2);
		units.push_back(4);
		units.push_back(8);
		varMap[std::string("units")] = units;

		std::vector<int> size;
		size.push_back(1024);
		size.push_back(2048);
		size.push_back(4096);
		varMap[std::string("size")] = size;

		return varMap;
	}

	//Before each sample
	void preSamp(std::map<std::string,int> sample)
	{
		dash::init(sample["units"]);

		dash::Array<int> array(sample["size"]);
	}

	//Before each iteration
	void preIter()
	{
		std::fill(array.lbegin(),array.lend(),std::rand());
	}


	void postIter()
	{
	}
	//After each sample
	void postSamp()
	{
		dash::finalize();
	}

}

//Time is measured here
Benchmark("Sort", TestFixture, iterations)
{
	dash::sort(array.begin,array.end);
}

}
