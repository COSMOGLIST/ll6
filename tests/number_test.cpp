#include <lib/number.h>
#include <gtest/gtest.h>
#include <tuple>

class ConvertingTestsSuite : public testing::TestWithParam<std::tuple<uint32_t, const char*, bool>> {
};

TEST_P(ConvertingTestsSuite, EqualTest) {
    uint2022_t a = from_uint(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    if(std::get<2>(GetParam()))
        ASSERT_EQ(a,b) << std::get<0>(GetParam()) << " == " << std::get<1>(GetParam());
    else
        ASSERT_NE(a,b) << std::get<0>(GetParam()) << " != " << std::get<1>(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    Group,
    ConvertingTestsSuite,
    testing::Values(
        // positive
        std::make_tuple(0, "0", true),
        std::make_tuple(239,"239", true),
        std::make_tuple(255,"255", true),
        std::make_tuple(256,"256", true),
        std::make_tuple(10000,"10000", true),
        std::make_tuple(32767,"32767", true),
        std::make_tuple(32768,"32768", true),
        std::make_tuple(65535,"65535", true),
        std::make_tuple(2147483647,"2147483647", true),

        // negative
        std::make_tuple(0, "1", false),
        std::make_tuple(32768,"32769", false),
        std::make_tuple(255,"256", false),
        std::make_tuple(256,"255", false),
        std::make_tuple(31251,"31252", false),
        std::make_tuple(2147483647,"2147483648", false)
    )
);


class OperationTestsSuite
    : public testing::TestWithParam<
        std::tuple<
            const char*, // lhs
            const char*, // rhs
            const char*, // +
            const char*, // -
            const char*  // *
        >
    > {
};

TEST_P(OperationTestsSuite, AddTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a + b;
    uint2022_t expected = from_string((std::get<2>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, SubstTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a - b;
    uint2022_t expected = from_string((std::get<3>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, MultTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a * b;
    uint2022_t expected = from_string((std::get<4>(GetParam())));

    ASSERT_EQ(result, expected);
}
