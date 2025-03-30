#define BOOST_TEST_MODULE test_version

#include <custom_allocator.h>

#include <gtest/gtest.h>

TEST(Push5test, Positive)
{
	const int SIZE = 5;
	std::vector<int, CustomAllocator<int>> v;

	for (size_t i = 0; i < SIZE; ++i) {
		v.push_back(i);
	}

	EXPECT_EQ(SIZE, v.size());


	for (size_t i = 0; i < SIZE; ++i) {
		EXPECT_EQ(i, v[i]);
	}
}


int main()
{

	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}