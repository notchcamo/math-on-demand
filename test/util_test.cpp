// By notchcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

using namespace soo;

TEST(Util, is_equal_range)
{
    const std::vector<int> vec1{1, 2, 3};
    const std::vector<int> vec2{1, 2, 3};

    EXPECT_TRUE(util::isEqual(vec1, vec2));

    const std::array<double, 3> arr1{1.0, 2.0, 3.0};
    const std::array<double, 3> arr2{1.0, 2.0, 3.0};

    EXPECT_TRUE(util::isEqual(arr1, arr2));
}
