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

TEST(FixNPM, Test_4)
{
    EXPECT_EQ(" 42", doPrint("% d", 42));
}


