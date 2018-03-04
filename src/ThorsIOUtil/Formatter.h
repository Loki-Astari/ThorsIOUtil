#ifndef THORSANVIL_IOUTIL_FORMATTER_H
#define THORSANVIL_IOUTIL_FORMATTER_H

#include "printToStream.h"
#include "saveToStream.h"
#include "FormatInfo.h"

#include <ostream>
#include <string>
#include <map>
#include <exception>
#include <stdexcept>
#include <typeindex>
#include <cassert>
#include <type_traits>


namespace ThorsAnvil::IOUtil
{

template<typename T>
struct SignConversionOption
{
    using Actual        = T;
    using Alternative   = T;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(T const&) {return 0;}
    static int truncate(T const& arg, int mask) {return 0;};
};

template<>
struct SignConversionOption<char>
{
    using Actual        = char;
    using Alternative   = unsigned char;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(char const& arg) {return arg;}
    static int truncate(char const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<short>
{
    using Actual        = short;
    using Alternative   = unsigned short;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(short const& arg) {return arg;}
    static int truncate(short const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<int>
{
    using Actual        = int;
    using Alternative   = unsigned int;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(int const&) {return 0;}
    static int truncate(int const& arg, int mask) {return arg & mask;};
};
template<>
struct SignConversionOption<long>
{
    using Actual        = long;
    using Alternative   = unsigned long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(long const&) {return 0;}
    static int truncate(long const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<long long>
{
    using Actual        = long long;
    using Alternative   = unsigned long long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(long long const&) {return 0;}
    static int truncate(long long const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<unsigned char>
{
    using Actual        = unsigned char;
    using Alternative   = char;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(unsigned char const& arg) {return arg;}
    static int truncate(unsigned char const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<unsigned short>
{
    using Actual        = unsigned short;
    using Alternative   = short;
    static constexpr bool allowIntConversion = true;
    static int convertToInt(unsigned short const& arg) {return arg;}
    static int truncate(unsigned short const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<unsigned int>
{
    using Actual        = unsigned int;
    using Alternative   = int;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(unsigned int const&) {return 0;}
    static int truncate(unsigned int const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<unsigned long>
{
    using Actual        = unsigned long;
    using Alternative   = long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(unsigned long const&) {return 0;}
    static int truncate(unsigned long const& arg, int mask) {return 0;};
};
template<>
struct SignConversionOption<unsigned long long>
{
    using Actual        = unsigned long long;
    using Alternative   = long long;
    static constexpr bool allowIntConversion = false;
    static int convertToInt(unsigned long long const&) {return 0;}
    static int truncate(unsigned long long const& arg, int mask) {return 0;};
};

template<typename T>
inline bool checkNumLargerEqualToZero(T const& value)      {return value >= 0;}
inline bool checkNumLargerEqualToZero(char const*)         {return false;}

class Formatter
{
    // The number of characters read in the formatter.
    std::size_t             used;
    Dynamic                 dynamicSize;

    // Details extracted from the format string.
    FormatInfo              info;

    // When you apply a `Formatter` object to a stream this temporary object is created.
    // When the actual object is then applied to this object we call back to the Formatter::apply()
    // method to do the actual work of setting up the stream and printing the value. When it is
    // all done we return the original stream.
    // see below friend FormatterCheck operator<<(std::ostream&, Format const&)
    // Usage:
    //      stream << FormatObject << value;
    //      Notes:
    //          stream << FormatObject          returns a FormatChecker
    //          FormatChecker << value          calls apply()
    //                                          the returns the original stream
    struct FormatterCheck
    {
        std::ostream&       stream;
        Formatter const&    formatter;
        FormatterCheck(std::ostream& s, Formatter const& formatter)
            : stream(s)
            , formatter(formatter)
        {}
        template<typename A>
        std::ostream& operator<<(A const& nextArg)
        {
            formatter.apply(stream, nextArg);
            return stream;
        }
    };
    public:
       Formatter(char const* formatStr, Dynamic dynamicWidthHandeled)
            : used(0)
            , dynamicSize(Dynamic::None)
            , info()
        {
            info.precision = -1;
            // Scan the format string to set up all the
            // the member variables.
            char const* fmt = formatStr;

            // Must start with a '%'
            assert(*fmt == '%');

            bool flag = true;
            // Scan the flags.
            // There can be more than one. So loop until we don't find a flag.
            do
            {
                ++fmt;
                switch (*fmt)
                {
                    case '-':   info.leftJustify     = true;break;
                    case '+':   info.forceSign       = true;break;
                    case ' ':   info.forceSignWidth  = true;break;
                    case '#':   info.prefixType      = true;break;
                    case '0':   info.leftPad         = true;break;
                    default:    flag = false;
                }
            } while (flag);

            // Check to see if there is a width.
            if (std::isdigit(*fmt))
            {
                char* end;
                info.width = std::strtol(fmt, &end, 10);
                fmt = end;
            }
            else if (*fmt == '*')
            {
                if (dynamicWidthHandeled == Dynamic::None)
                {
                    dynamicSize         = Dynamic::Width;
                    info                = FormatInfo();
                    return;
                }
                ++fmt;
            }

            // Check to see if there is a precision
            if (*fmt == '.')
            {
                ++fmt;
                if (std::isdigit(*fmt))
                {
                    char* end;
                    info.precision = std::strtol(fmt, &end, 10);
                    fmt = end;
                }
                else if (*fmt == '*')
                {
                    if (dynamicWidthHandeled == Dynamic::None || dynamicWidthHandeled == Dynamic::Width)
                    {
                        dynamicSize         = Dynamic::Precision;
                        info                = FormatInfo();
                        return;
                    }
                    ++fmt;
                }
                else
                {
                    // The actual value is not required (just the dot).
                    // If there is no value precision is 0 (rather than default)
                    info.precision = 0;
                }
            }

            // Check for the length
            // This converts from int to long int etc.
            // note this is optional.
            char first = *fmt;
            ++fmt;
            switch (first)
            {
                case 'h':   info.length = Length::h;
                            if (*fmt == 'h')
                            {
                                ++fmt;
                                info.length  = Length::hh;
                            }
                            break;
#pragma vera-pushoff
                case 'l':   info.length = Length::l;
                            if (*fmt == 'l')
                            {
                                ++fmt;
                                info.length  = Length::ll;
                            }
                            break;
#pragma vera-pop
                case 'j':   info.length = Length::j;break;
                case 'z':   info.length = Length::z;break;
                case 't':   info.length = Length::t;break;
                case 'L':   info.length = Length::L;break;
                default:
                    --fmt;
            }

            // Check for the specifier value.
            switch (*fmt)
            {
                case 'd':   info.specifier = Specifier::d;info.type = Type::Int;      break;
                case 'i':   info.specifier = Specifier::i;info.type = Type::Int;      break;
                case 'u':   info.specifier = Specifier::u;info.type = Type::UInt;     break;
                case 'o':   info.specifier = Specifier::o;info.type = Type::UInt;     break;
                case 'x':   info.specifier = Specifier::x;info.type = Type::UInt;     break;
                case 'X':   info.specifier = Specifier::X;info.type = Type::UInt;     break;
                case 'f':   info.specifier = Specifier::f;info.type = Type::Float;    break;
                case 'F':   info.specifier = Specifier::F;info.type = Type::Float;    break;
                case 'e':   info.specifier = Specifier::e;info.type = Type::Float;    break;
                case 'E':   info.specifier = Specifier::E;info.type = Type::Float;    break;
                case 'g':   info.specifier = Specifier::g;info.type = Type::Float;    break;
                case 'G':   info.specifier = Specifier::G;info.type = Type::Float;    break;
                case 'a':   info.specifier = Specifier::a;info.type = Type::Float;    break;
                case 'A':   info.specifier = Specifier::A;info.type = Type::Float;    break;
                case 'c':   info.specifier = Specifier::c;info.type = Type::Char;     break;
                case 's':   info.specifier = Specifier::s;info.type = Type::String;   break;
                case 'p':   info.specifier = Specifier::p;info.type = Type::Pointer;  break;
                case 'n':   info.specifier = Specifier::n;info.type = Type::Count;    break;
                default:
                    // Not optional so throw if we don't find it.
                   throw std::invalid_argument(std::string("Invalid Parameter specifier: ") + *fmt);
            }
            ++fmt;


            info.useDynamicSize = dynamicWidthHandeled;

            // Now we know how much string was used to calculate the value.
            used  = fmt - formatStr;

            // Pre-calculate the type information of the next argument.
            info.expectedType = getType(info.length, info.type);

            // Pre-calculate the format flags that will be used to set up the stream.
            info.format  |= (info.leftJustify ? std::ios_base::left : std::ios_base::right);

            // Are we expecting a number type?
            // Set dec/oct/hex/fixed/scientific
            if (info.specifier == Specifier::d || info.specifier == Specifier::i)
            {
                info.format  |= std::ios_base::dec;
            }
            else if (info.specifier == Specifier::o)
            {
                info.format  |= std::ios_base::oct;
            }
            else if (info.specifier == Specifier::x || info.specifier == Specifier::X)
            {
                info.format  |= std::ios_base::hex;
            }
            else if (info.specifier == Specifier::f || info.specifier == Specifier::F)
            {
                info.format |= std::ios_base::fixed;
            }
            else if (info.specifier == Specifier::e || info.specifier == Specifier::E)
            {
                info.format |= std::ios_base::scientific;
            }
            else if (info.specifier == Specifier::a || info.specifier == Specifier::A)
            {
                info.format |= (std::ios_base::fixed | std::ios_base::scientific);
            }

            // Some specifiers define if we are using upper case (rather than the default lowercase for any letters)
            if (info.specifier == Specifier::X || info.specifier == Specifier::F || info.specifier == Specifier::E || info.specifier == Specifier::A || info.specifier == Specifier::G)
            {
                info.format |= std::ios_base::uppercase;
            }

            // Show the base types for certain output specifiers.
            if (info.prefixType && (info.specifier == Specifier::o || info.specifier == Specifier::x || info.specifier == Specifier::X))
            {
                info.format |= std::ios_base::showbase;
            }

            // Show the floating point even if there is no fraction.
            if (info.prefixType && (info.specifier == Specifier::a || info.specifier == Specifier::A || info.specifier == Specifier::e || info.specifier == Specifier::E || info.specifier == Specifier::f || info.specifier == Specifier::F || info.specifier == Specifier::g || info.specifier == Specifier::G))
            {
                info.format |= std::ios_base::showpoint;
            }

            // Show the '+' sign for positive values.
            if (info.forceSign && (info.specifier != Specifier::c && info.specifier != Specifier::s && info.specifier != Specifier::p))
            {
                info.format |= std::ios_base::showpos;
            }
        }
        std::size_t size()          const {return used;}
        Dynamic     isDynamicSize() const {return dynamicSize;}

        // We pass the formatter to the stream first
        // So we create a marker object used to print the actual argument.
        // This will call apply() with the actual argument.
        friend FormatterCheck operator<<(std::ostream& s, Formatter const& formatter)
        {
            return FormatterCheck(s, formatter);
        }
        private:
            template<typename A>
            void apply(std::ostream& s, A const& arg) const
            {
                if (dynamicSize == Dynamic::None)
                {
                    using Actual       = typename SignConversionOption<A>::Actual;
                    using Alternative  = typename SignConversionOption<A>::Alternative;

                    if (std::type_index(typeid(Actual)) == std::type_index(*info.expectedType.first))
                    {
                        applyData(s, arg);
                    }
                    else if (std::type_index(typeid(Actual)) != std::type_index(typeid(Alternative)) && std::type_index(*info.expectedType.first) == std::type_index(typeid(Alternative)))
                    {
                        applyData(s, static_cast<Alternative const&>(arg));
                    }
                    else if (SignConversionOption<A>::allowIntConversion)
                    {
                        applyData(s, SignConversionOption<A>::convertToInt(arg));
                    }
                    else if (std::type_index(typeid(A)) == std::type_index(typeid(int)) && info.expectedType.second)
                    {
                        applyData(s, SignConversionOption<A>::truncate(arg, info.expectedType.second));
                    }
                    else
                    {
                        throw std::invalid_argument(std::string("Actual argument does not match supplied argument (or conversions): Expected(") + info.expectedType.first->name() + ") Got(" + typeid(A).name() + ")");
                    }
                }
                else
                {
                    if (std::type_index(typeid(A)) != std::type_index(typeid(int)))
                    {
                        throw std::invalid_argument("Dynamic Width of Precision is not an int");
                    }
                    saveToStream(s, dynamicSize, arg);
                }
            }

            template<typename A>
            void applyData(std::ostream& s, A const& arg) const
            {
                // Fill is either 0 or space and only used for numbers.
                char        fill      = (!info.leftJustify && info.leftPad) ? '0' : ' ';
                std::size_t fillWidth = (info.useDynamicSize == Dynamic::Width || info.useDynamicSize == Dynamic::Both)
                                            ? std::abs(s.iword(static_cast<int>(Dynamic::Width)))
                                            : info.width;
                std::size_t fractPrec = (info.useDynamicSize == Dynamic::Precision || info.useDynamicSize == Dynamic::Both)
                                            ? s.iword(static_cast<int>(Dynamic::Precision))
                                            : info.precision == -1 && info.type == Type::Float ? 6 : info.precision;
                bool                    forceLeft = info.leftJustify;
                std::ios_base::fmtflags format    = info.format;
                if ((info.useDynamicSize == Dynamic::Width || info.useDynamicSize == Dynamic::Both) && s.iword(static_cast<int>(Dynamic::Width)) < 0)
                {
                    forceLeft   = true;
                    format  |=  std::ios_base::left;
                    format  &=  ~std::ios_base::right;

                }

                // Take special care if we forcing a space in-front of positive values.
                if (info.forceSignWidth && !info.forceSign && checkNumLargerEqualToZero(arg) && (info.type == Type::Float || info.type == Type::Int))
                {
                    s << ' ';
                    fillWidth = fillWidth == 0 ? 0 : fillWidth - 1;
                }

                // Set up the stream for formatting
                auto oldFlags = s.flags(format);
                auto oldFill  = s.fill(fill);
                auto oldWidth = s.width(fillWidth);
                auto oldPrec  = s.precision(fractPrec);

                printToStream(s, arg, fillWidth, fractPrec, forceLeft, info);

                // reset the stream to original state
                s.precision(oldPrec);
                s.width(oldWidth);
                s.fill(oldFill);
                s.flags(oldFlags);
            }
            // Only certain combinations of Specifier and Length are supported.
            static AllowedType getType(Length length, Type type)
            {
                static std::map<std::pair<Type, Length>, AllowedType>    typeMap =
                {
#pragma vera-pushoff
                    {{Type::Int,   Length::none}, {&typeid(int), 0}},
                    {{Type::Int,   Length::hh},   {&typeid(signed char), 0xFF}},
                    {{Type::Int,   Length::h},    {&typeid(short int), 0xFFFF}},
                    {{Type::Int,   Length::l},    {&typeid(long int), 0}},
                    {{Type::Int,   Length::ll},   {&typeid(long long int), 0}},
                    {{Type::Int,   Length::j},    {&typeid(std::intmax_t), 0}},
                    {{Type::Int,   Length::z},    {&typeid(std::size_t), 0}},
                    {{Type::Int,   Length::t},    {&typeid(std::ptrdiff_t), 0}},

                    {{Type::UInt,  Length::none}, {&typeid(unsigned int), 0}},
                    {{Type::UInt,  Length::hh},   {&typeid(unsigned char), 0xFF}},
                    {{Type::UInt,  Length::h},    {&typeid(unsigned short int), 0xFFFF}},
                    {{Type::UInt,  Length::l},    {&typeid(unsigned long int), 0}},
                    {{Type::UInt,  Length::ll},   {&typeid(unsigned long long int), 0}},
                    {{Type::UInt,  Length::j},    {&typeid(std::intmax_t), 0}},
                    {{Type::UInt,  Length::z},    {&typeid(std::size_t), 0}},
                    {{Type::UInt,  Length::t},    {&typeid(std::ptrdiff_t), 0}},

                    {{Type::Float, Length::none}, {&typeid(double), 0}},       {{Type::Float, Length::l}, {&typeid(double), 0}},          {{Type::Float, Length::L}, {&typeid(long double), 0}},
                    {{Type::Char,  Length::none}, {&typeid(int), 0}},          {{Type::Char,  Length::l}, {&typeid(std::wint_t), 0}},
                    {{Type::String,Length::none}, {&typeid(char const*), 0}},  {{Type::String,Length::l}, {&typeid(wchar_t const*), 0}},

                    {{Type::Pointer,Length::none},{&typeid(void*), 0}},

                    {{Type::Count, Length::none}, {&typeid(int*), 0}},
                    {{Type::Count, Length::hh},   {&typeid(signed char*), 0}},
                    {{Type::Count, Length::h},    {&typeid(short int*), 0}},
                    {{Type::Count, Length::l},    {&typeid(long int*), 0}},
                    {{Type::Count, Length::ll},   {&typeid(long long int*), 0}},
                    {{Type::Count, Length::j},    {&typeid(std::intmax_t*), 0}},
                    {{Type::Count, Length::z},    {&typeid(std::size_t*), 0}},
                    {{Type::Count, Length::t},    {&typeid(std::ptrdiff_t*), 0}}
#pragma vera-pop
                };
                auto find = typeMap.find({type, length});
                if (find == typeMap.end())
                {
                    throw std::invalid_argument("Specifier and length are not a valid combination");
                }
                return find->second;
            }
};

}

#endif
