void main()
{
	run();
}

class DashSortingFixture : public FixtureBase
{
	
public:
	void SetupFixture() {
		set_units()
			.range({ 1,2,4,8 });
		set_size()
			.range(1024, 10240)
			.step(times(2));
		add_variable("density")
			.range(0.0, 1.0)
			.step(0.2);
	}

	//Before each sample
	void setUp(std::map<std::string,int> sample)
	{
		dash::init(sample["units"]);
		
		dash::Array<int> array(sample["size"]);
	}
	
	//Before each iteration
	void eachIt()
	{
		std::fill(array.lbegin(),array.lend(),std::rand());
	}

	//After each sample
	void tearDown()
	{
		dash::finalize();
	}

};

//Time is measured here
Benchmark("Sort", TestFixture, iterations)
{
	dash::sort(array.begin,array.end);
}



}
		
