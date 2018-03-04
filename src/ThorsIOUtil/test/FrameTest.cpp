#include "Format.h"


#include "gtest/gtest.h"
#include <string>
#include <sstream>
#include <cstdio>

using ThorsAnvil::IOUtil::make_format;

template<typename... Args>
std::string const& doPrint1(char const* format, Args... args)
{
    static std::string buffer(2048, '\0');
    auto size = std::sprintf(&buffer[0], format, args...);
    buffer.resize(size);
    return buffer;
}

template<typename... Args>
std::string doPrint(char const* format, Args... args)
{
    static std::stringstream buffer;
    buffer.str(std::string());

    buffer << make_format(format, args...);
    return buffer.str();
}

#define THOR_TEST_CAT(Base, Ext)        Base ## Ext
#define THOR_TEST_EVAL(Base)            Base
#define THOR_TEST_EXPAND(Base)          THOR_TEST_EVAL(Base)

#define THOR_PRINTF_TEST(Number, Result, ...)                                       \
    TEST(THOR_TEST_EXPAND(THOR_PRINTF_TEST_GROUP), THOR_TEST_CAT(Test_, Number))    \
    {                                                                               \
        EXPECT_EQ(Result, doPrint( __VA_ARGS__ ));                                  \
    }

#define THOR_PRINTF_FAIL(Number, Result, ...)                                       \
    TEST(THOR_TEST_EXPAND(THOR_PRINTF_TEST_GROUP), THOR_TEST_CAT(Test_, Number))    \
    {                                                                               \
        auto action = [](){doPrint( __VA_ARGS__ );};                                \
                                                                                    \
        EXPECT_THROW(                                                               \
            action(),                                                               \
            std::invalid_argument                                                   \
        );                                                                          \
    }

#include "testlist.h"

