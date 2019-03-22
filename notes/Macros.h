
#define BENCHMARK_CLASS_NAME(name) UserBenchmark##_##name

#define BENCHMARK(name, fixture)     \
	class BENCHMARK_CLASS_NAME(name) : public fixture {          \
	public:                                                     \
		BENCHMARK_CLASS_NAME(name)() : fixture() {}	   \
		virtual void UserBenchmark() override;            \
	};                                                         \
	void BENCHMARK_CLASS_NAME(name)::UserBenchmark()
