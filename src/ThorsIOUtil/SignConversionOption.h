#ifndef THORSANVIL_IOUTIL_SIGNCONVERSIONOPTION_H
#define THORSANVIL_IOUTIL_SIGNCONVERSIONOPTION_H

namespace ThorsAnvil::IOUtil
{

/*
 * When handling integer types some
 * automatic conversions are allowed.
 *
 * This type handles these conversions.
 * It is used by Formatter::apply()
 */
template<typename T>
// @class-internal
struct SignConversionOption
{
    using Actual        = T;                                    // The Current Type
    using Alternative   = T;                                    // Acceptable alternative type we can cast from
    static constexpr bool allowIntConversion = false;           // Can we convert this type from int by call convertToInt()
    static int convertToInt(T const&) {return 0;}
    static int truncate(T const& arg, int mask) {return 0;};    // Int only we truncate the value by masking if top bits.
                                                                // The mask is retrieved from Formatter::getType()
};

template<>
// @class-internal
struct SignConversionOption<char>
{
    using Actual        = char;
    using Alternative   = unsigned char;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(char const& arg) {return arg;}
    static int truncate(char const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<short>
{
    using Actual        = short;
    using Alternative   = unsigned short;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(short const& arg) {return arg;}
    static int truncate(short const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<int>
{
    using Actual        = int;
    using Alternative   = unsigned int;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(int const&) {return 0;}
    static int truncate(int const& arg, int mask) {return arg & mask;};
};
template<>
// @class-internal
struct SignConversionOption<long>
{
    using Actual        = long;
    using Alternative   = unsigned long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(long const&) {return 0;}
    static int truncate(long const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<long long>
{
    using Actual        = long long;
    using Alternative   = unsigned long long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(long long const&) {return 0;}
    static int truncate(long long const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<unsigned char>
{
    using Actual        = unsigned char;
    using Alternative   = char;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(unsigned char const& arg) {return arg;}
    static int truncate(unsigned char const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<unsigned short>
{
    using Actual        = unsigned short;
    using Alternative   = short;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(unsigned short const& arg) {return arg;}
    static int truncate(unsigned short const& arg, int mask) {return 0;};
};
template<>
// @class-internal
// Must have some description
struct SignConversionOption<unsigned int>
{
    using Actual        = unsigned int;
    using Alternative   = int;
    static constexpr bool allowIntConversion = false;
    // @method
    // @return  Bla
    // @param   value unused
    // Some Stuff
    static int convertToInt(unsigned int const&) {return 0;}
    static int truncate(unsigned int const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<unsigned long>
{
    using Actual        = unsigned long;
    using Alternative   = long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(unsigned long const&) {return 0;}
    static int truncate(unsigned long const& arg, int mask) {return 0;};
};
template<>
// @class-internal
struct SignConversionOption<unsigned long long>
{
    using Actual        = unsigned long long;
    using Alternative   = long long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(unsigned long long const&) {return 0;}
    static int truncate(unsigned long long const& arg, int mask) {return 0;};
};

}

#endif
