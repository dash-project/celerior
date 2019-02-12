#include "gtest/gtest.h"
#include "fixture_base.h"

#include <iostream>
#include <iomanip>
#include <sstream>


TEST(FixtureVariableInt,ListInit){
	FixtureVariable<int> fv = FixtureVariable<int>("IntTest");
	fv.range({1,2,4,8,16});
	std::vector<int> testVec = {1,2,4,8,16};

	EXPECT_EQ(testVec,fv.values());
}

TEST(FixtureVariableInt,RangeStep){
	FixtureVariable<int> fv2 = FixtureVariable<int>("IntTest2");
	fv2.range(2,16).step(2);
	std::vector<int> testVec2 = {2,4,6,8,10,12,14,16};

	EXPECT_EQ(testVec2,fv2.values());
}

TEST(FixtureVariableInt,StepRange){
	FixtureVariable<int> fv3 = FixtureVariable<int>("IntTest3");
	fv3.step(2).range(2,16);
	std::vector<int> testVec3 = {2,4,6,8,10,12,14,16};

	EXPECT_EQ(testVec3,fv3.values());
}

TEST(FixtureVariableInt,RangeStepTimes){
	FixtureVariable<int> fv4 = FixtureVariable<int>("IntTest4");
	fv4.range(1,32).step(times<int>(2));
	std::vector<int> testVec4 = {1,2,4,8,16,32};

	EXPECT_EQ(testVec4,fv4.values());

}

TEST(FixtureVariableDouble,StepTimesRange){
	FixtureVariable<double> fv5 = FixtureVariable<double>("DoubleTest");
	fv5.step(times<double>(2.0)).range(1.0,32.0);
	std::vector<double> testVec5 = {1.0,2.0,4.0,8.0,16.0,32.0};

	EXPECT_EQ(testVec5,fv5.values());

}

TEST(FixtureBase, Constructors) {

    


}


int main (int argc, char* argv[]){
	testing::InitGoogleTest(&argc, argv);

  Result r;

  //  http://www.cplusplus.com/reference/sstream/stringstream/
  std::cout << "int value: "   << 123 << '\n'
            << "float value: " << std::fixed << std::setprecision(4) << 1.23
            << r
            << std::endl;

	return RUN_ALL_TESTS();
}
