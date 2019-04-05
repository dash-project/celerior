#include "fixture_base2.h"

#define CONTAINER(name,type) public: type name;

#define BENCHMARK_CLASS_NAME(name) UserBenchmark##_##name

#define PRE_SAMPLE \
	void preSample(std::map<std::string, int> variables)

#define POST_SAMPLE \
	void postSample(std::map<std::string,int> variables)

#define PRE_ITERATION \
	void preIteration(std::map<std::string,int>variables)

#define POST_ITERATION \
	void postIteration(std::map<std::string,int> variables)

#define BENCHMARK(name, fixture)     \
	class BENCHMARK_CLASS_NAME(name) : public fixture {          \
	public:                                                     \
		BENCHMARK_CLASS_NAME(name)() : fixture() {}	   \
		virtual void UserBenchmark(std::map<std::string,int> variables) override;            \
	};                                                         \
	void BENCHMARK_CLASS_NAME(name)::UserBenchmark(std::map<std::string,int>variables)

