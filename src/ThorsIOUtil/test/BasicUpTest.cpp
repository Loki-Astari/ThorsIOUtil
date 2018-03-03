#include "Format.h"


#include "gtest/gtest.h"
#include <sstream>

using ThorsAnvil::IOUtil::make_format;

TEST(BasicUpTest, NormalString)
{
    std::stringstream s;
    s << make_format("Test One\n");

    EXPECT_EQ(s.str(), "Test One\n");
}

TEST(BasicUpTest, StringWithInteger)
{
    std::stringstream s;
    s << make_format("Test Two   %d\n", 12);

    EXPECT_EQ(s.str(), "Test Two   12\n");
}

TEST(BasicUpTest, StringWithIntegerAndFloat)
{
    std::stringstream s;
    s << make_format("Test Three %d %f\n", 12, 4.56);

    EXPECT_EQ(s.str(), "Test Three 12 4.560000\n");
}

TEST(BasicUpTest, BadTypeThrows)
{
    std::stringstream s;
    auto action = [&s](){s << make_format("Test Four  %d %d\n", 12, 4.56);};

    EXPECT_THROW(
        action(),
        std::invalid_argument
    );
}

