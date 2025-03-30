#define BOOST_TEST_MODULE test_version

#include <custom_allocator.h>
#include <custom_vector.h>

#include <gtest/gtest.h>

TEST(Push5testWithStdAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}
	
	EXPECT_EQ(SIZE, vector.size());
}

TEST(SizeChangeAfterEraseWithStdAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}
	
	vector.erase(3);
	EXPECT_NE(SIZE, vector.size());
}


TEST(CorrectEraseWithStdAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int, CustomAllocator<int>> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}

	vector.erase(3);

	for (size_t i = 0; i < vector.size(); ++i) {
		int v_correct = i >= 3 ? i + 1 : i;
		EXPECT_EQ(v_correct, vector[i]);
	}
}

TEST(Push5testWitCustomAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int, CustomAllocator<int>> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}
	
	EXPECT_EQ(SIZE, vector.size());
}

TEST(SizeChangeAfterEraseWithCustomAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int, CustomAllocator<int>> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}
	
	vector.erase(3);
	EXPECT_NE(SIZE, vector.size());
}

TEST(CorrectEraseWithCustomAllocator, Positive)
{
	const size_t SIZE = 5;
	CustomVector<int, CustomAllocator<int>> vector;

	for (size_t i = 0; i < SIZE; ++i) {
		vector.push(i);
	}

	vector.erase(3);

	for (size_t i = 0; i < vector.size(); ++i) {
		int v_correct = i >= 3 ? i + 1 : i;
		EXPECT_EQ(v_correct, vector[i]);
	}
}

int main()
{

	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}