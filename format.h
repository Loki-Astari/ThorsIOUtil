#ifndef THORSANVIL_IOUTIL_FORMAT_H
#define THORSANVIL_IOUTIL_FORMAT_H


#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
#include <typeindex>
#include <cstdint>
#include <cstddef>
#include <cassert>

namespace ThorsAnvil::IOUtil
{

template<typename... Args>
class Format
{
    class Formatter
    {
        // The number of characters read in the formatter.
        std::size_t             used;

        // Formatter has the text representation:
        //      %<Flag>*<Width>?[.<Precision>]?<Length>?<Specifier>
        //
        //      Flag:       - + <space> # 0
        //      Width:      {1-9}{0-9}*
        //      Precision:  {0-9}*
        //      Length:     hh h l ll j z t L
        //      Specifier:  d i u o x X f F e E g G a A c s p n

        // Enum representing the Length and specifier provided in a string
        enum class Length    {none, hh, h, l, ll, j, z, t, L};
        enum class Specifier {d, i, u, o, x, X, f, F, e, E, g, G, a, A, c, s, p, n};
        enum class Type      {Int, UInt, Float, Char, String, Pointer, Count};
        // Flags
        bool                    leftJustify;    // -    Left-justify within the given field width; Right justification is the default (see width sub-specifier).
        bool                    forceSign;      // +    Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
        bool                    forceSignWidth; // (space)  If no sign is going to be written, a blank space is inserted before the value.
        bool                    prefixType;     // #    Used with o, x or X specifiers the value is preceded with 0, 0x or 0X respectively for values different than zero.
                                                //      Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
        bool                    leftPad;        // 0    Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).
        // Width and precision of the formatter.
        int                     width;
        int                     precision;
        Length                  length;
        Specifier               specifier;
        Type                    type;

        // Pre-calculate a some values based on the format string
        std::type_info const*   expectedType;   // Type info we expect the next argument to be based on length/specifier
        std::ios_base::fmtflags format;         // The format flags that will be applied to stream before the next argument

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
           Formatter(char const* formatStr)
                : used(0)
                , leftJustify(false)
                , forceSign(false)
                , forceSignWidth(false)
                , prefixType(false)
                , leftPad(false)
                , width(0)
                , precision(6)
                , length(Length::none)
                , format(0)
            {
                // Scan the format string to set up all the
                // the member variables.
                char const* fmt = formatStr;

                // Must start with a '%'
                assert(*fmt == '%');

                bool flag = true;
                // Scan the flags.
                // There can be more than one. So loop until we don't find a flag.
                do {
                    ++fmt;
                    switch(*fmt) {
                        case '-':   leftJustify     = true;break;
                        case '+':   forceSign       = true;break;
                        case ' ':   forceSignWidth  = true;break;
                        case '#':   prefixType      = true;break;
                        case '0':   leftPad         = true;break;
                        default:    flag = false;
                    }
                } while (flag);

                // Check to see if there is a width.
                if (std::isdigit(*fmt)) {
                    char* end;
                    width = std::strtol(fmt, &end, 10);
                    fmt = end;
                }

                // Check to see if there is a precision
                if (*fmt == '.') {
                    ++fmt;
                    if (std::isdigit(*fmt)) {
                        char* end;
                        precision = std::strtol(fmt, &end, 10);
                        fmt = end;
                    }
                    else {
                        // The actual value is not required (just the dot).
                        // If there is no value precision is 0 (rather than default)
                        precision = 0;
                    }
                }

                // Check for the length
                // This converts from int to long int etc.
                // note this is optional.
                char first = *fmt;
                ++fmt;
                switch(first) {
                    case 'h':   length = Length::h;
                                if (*fmt == 'h') {
                                    ++fmt;
                                    length  = Length::hh;
                                }
                                break;
                    case 'l':   length = Length::l;
                                if (*fmt == 'l') {
                                    ++fmt;
                                    length  = Length::ll;
                                }
                                break;
                    case 'j':   length = Length::j;break;
                    case 'z':   length = Length::z;break;
                    case 't':   length = Length::t;break;
                    case 'L':   length = Length::L;break;
                    default:
                        --fmt;
                }

                // Check for the specifier value.
                switch(*fmt) {
                    case 'd':   specifier = Specifier::d;type = Type::Int;      break;
                    case 'i':   specifier = Specifier::i;type = Type::Int;      break;
                    case 'u':   specifier = Specifier::u;type = Type::UInt;     break;
                    case 'o':   specifier = Specifier::o;type = Type::UInt;     break;
                    case 'x':   specifier = Specifier::x;type = Type::UInt;     break;
                    case 'X':   specifier = Specifier::X;type = Type::UInt;     break;
                    case 'f':   specifier = Specifier::f;type = Type::Float;    break;
                    case 'F':   specifier = Specifier::F;type = Type::Float;    break;
                    case 'e':   specifier = Specifier::e;type = Type::Float;    break;
                    case 'E':   specifier = Specifier::E;type = Type::Float;    break;
                    case 'g':   specifier = Specifier::g;type = Type::Float;    break;
                    case 'G':   specifier = Specifier::G;type = Type::Float;    break;
                    case 'a':   specifier = Specifier::a;type = Type::Float;    break;
                    case 'A':   specifier = Specifier::A;type = Type::Float;    break;
                    case 'c':   specifier = Specifier::c;type = Type::Char;     break;
                    case 's':   specifier = Specifier::s;type = Type::String;   break;
                    case 'p':   specifier = Specifier::p;type = Type::Pointer;  break;
                    case 'n':   specifier = Specifier::n;type = Type::Count;    break;
                    default:
                        // Not optional so throw if we don't find it.
                       throw std::invalid_argument(std::string("Invalid Parameter specifier: ") + *fmt);
                }
                ++fmt;

                // Now we know how much string was used to calculate the value.
                used  = fmt - formatStr;

                // Pre-calculate the type information of the next argument.
                expectedType = getType(specifier, length, type);

                // Pre-calculate the format flags that will be used to set up the stream.
                format  |= (leftJustify ? std::ios_base::left : std::ios_base::right);

                // Are we expecting a number type?
                // Set dec/oct/hex/fixed/scientific
                if (specifier == Specifier::d || specifier == Specifier::i) {
                    format  |= std::ios_base::dec;
                }
                else if (specifier == Specifier::o) {
                    format  |= std::ios_base::oct;
                }
                else if (specifier == Specifier::x || specifier == Specifier::X) {
                    format  |= std::ios_base::hex;
                }
                else if (specifier == Specifier::f || specifier == Specifier::F) {
                    format |= std::ios_base::fixed;
                }
                else if (specifier == Specifier::e || specifier == Specifier::E) {
                    format |= std::ios_base::scientific;
                }
                else if (specifier == Specifier::a || specifier == Specifier::A) {
                    format |= (std::ios_base::fixed | std::ios_base::scientific);
                }

                // Some specifiers define if we are using upper case (rather than the default lowercase for any letters)
                if (specifier == Specifier::X || specifier == Specifier::F || specifier == Specifier::E || specifier == Specifier::A || specifier == Specifier::G) {
                    format |= std::ios_base::uppercase;
                }

                // Show the base types for certain output specifiers.
                if (prefixType && (specifier == Specifier::o || specifier == Specifier::x || specifier == Specifier::X)) {
                    format |= std::ios_base::showbase;
                }

                // Show the floating point even if there is no fraction.
                if (prefixType && (specifier == Specifier::a || specifier == Specifier::A || specifier == Specifier::e || specifier == Specifier::E || specifier == Specifier::f || specifier == Specifier::F || specifier == Specifier::g || specifier == Specifier::G)) {
                    format |= std::ios_base::showpoint;
                }

                // Show the '+' sign for positive values.
                if (forceSign && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) {
                    format |= std::ios_base::showpos;
                }
            }
            std::size_t size() const {return used;}

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
                    if (std::type_index(*expectedType) != std::type_index(typeid(A))) {
                        throw std::invalid_argument(std::string("Actual argument does not match supplied argument: Expected(") + expectedType->name() + ") Got(" + typeid(A).name() + ")");
                    }

                    // Fill is either 0 or space and only used for numbers.
                    char fill      = (!leftJustify && leftPad && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) ? '0' : ' ';
                    int  fillWidth = width;

                    // Take special care if we forcing a space in-front of positive values.
                    if (forceSignWidth && !forceSign && (arg >= 0) && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) {
                        s << ' ';
                        --fillWidth;
                    }

                    // Set up the stream for formatting
                    std::ios_base::fmtflags oldFlags = s.flags(format);
                    char                    oldFill  = s.fill(fill);
                    std::streamsize         oldWidth = s.width(fillWidth);
                    std::streamsize         oldPrec  = s.precision(precision);

                    // Print the value.
                    s << arg;

                    // reset the stream to original state
                    s.precision(oldPrec);
                    s.width(oldWidth);
                    s.fill(oldFill);
                    s.flags(oldFlags);
                }
                // Only certain combinations of Specifier and Length are supported.
                static std::type_info const* getType(Specifier specifier, Length length, Type type)
                {
                    static std::map<std::pair<Type, Length>, std::type_info const*>    typeMap = {
                        // Integers.
                        {{Type::Int,   Length::none}, &typeid(int)},
                        {{Type::Int,   Length::hh},   &typeid(signed char)},
                        {{Type::Int,   Length::h},    &typeid(short int)},
                        {{Type::Int,   Length::l},    &typeid(long int)},
                        {{Type::Int,   Length::ll},   &typeid(long long int)},
                        {{Type::Int,   Length::j},    &typeid(std::intmax_t)},
                        {{Type::Int,   Length::z},    &typeid(std::size_t)},
                        {{Type::Int,   Length::t},    &typeid(std::ptrdiff_t)},

                        {{Type::UInt,  Length::none}, &typeid(unsigned int)},
                        {{Type::UInt,  Length::none}, &typeid(unsigned char)},
                        {{Type::UInt,  Length::none}, &typeid(unsigned short int)},
                        {{Type::UInt,  Length::none}, &typeid(unsigned long int)},
                        {{Type::UInt,  Length::none}, &typeid(unsigned long long int)},
                        {{Type::UInt,  Length::none}, &typeid(std::intmax_t)},
                        {{Type::UInt,  Length::none}, &typeid(std::size_t)},
                        {{Type::UInt,  Length::none}, &typeid(std::ptrdiff_t)},

                        {{Type::Float, Length::none}, &typeid(double)}, {{Type::Float, Length::l}, &typeid(double)}, {{Type::Float, Length::L}, &typeid(long double)},
                        {{Type::Char,  Length::none}, &typeid(int)},    {{Type::Char,  Length::l}, &typeid(std::wint_t)},
                        {{Type::String,Length::none}, &typeid(char*)},  {{Type::String,Length::l}, &typeid(wchar_t*)},

                        {{Type::Pointer,Length::none},&typeid(void*)},

                        {{Type::Count, Length::none}, &typeid(int*)},
                        {{Type::Count, Length::hh},   &typeid(signed char*)},
                        {{Type::Count, Length::h},    &typeid(short int*)},
                        {{Type::Count, Length::l},    &typeid(long int*)},
                        {{Type::Count, Length::ll},   &typeid(long long int*)},
                        {{Type::Count, Length::j},    &typeid(std::intmax_t*)},
                        {{Type::Count, Length::z},    &typeid(std::size_t*)},
                        {{Type::Count, Length::t},    &typeid(std::ptrdiff_t*)}
                    };
                    auto find = typeMap.find({type, length});
                    if (find == typeMap.end()) {
                        throw std::invalid_argument("Specifier and length are not a valid combination");
                    }
                    return find->second;
                }
    };
    std::string                     format;
    std::tuple<Args const&...>      arguments;
    std::vector<std::string>        prefixString;
    std::vector<Formatter>          formater;
    public:
        Format(char const* fmt, Args const&... args)
            : format(fmt)
            , arguments(args...)
        {
            std::size_t count = sizeof...(args);
            std::size_t pos   = 0;
            for(int loop = 0; loop < count; ++loop) {
                // Not dealing with '\%' yet just trying to get it working.
                std::size_t nextFormatter = format.find('%', pos);
                if (nextFormatter == std::string::npos) {
                    throw std::invalid_argument("Invalid Format: not enough format specifiers for provided arguments");
                }
                prefixString.emplace_back(format.substr(pos, (nextFormatter - pos)));

                formater.emplace_back(format.data() + nextFormatter);
                pos = nextFormatter + formater.back().size();
            }
            std::size_t nextFormatter = format.find(pos, '%');
            if (nextFormatter != std::string::npos) {
                throw std::invalid_argument("Invalid Format: too many format specifiers for provided arguments");
            }
            prefixString.emplace_back(format.substr(pos));
        }
        void print(std::ostream& s) const
        {
            doPrint(s, std::make_index_sequence<sizeof...(Args)>());
        }
    private:
        template<std::size_t I>
        std::ostream& printValue(std::ostream& s) const
        {
            return s << prefixString[I] << formater[I] << std::get<I>(arguments);
        }

        template<std::size_t... I>
        void doPrint(std::ostream& s, std::index_sequence<I...> const&) const
        {
            std::ostream* ignore[] = {&printValue<I>(s)...};
            s << prefixString.back();
        }

        friend std::ostream& operator<<(std::ostream& s, Format const& format)
        {
            format.print(s);
            return s;
        }
};

template<typename... Args>
Format<Args...> make_format(char const* fmt, Args const&... args)
{
    return Format<Args...>(fmt, args...);
}

}

#endif
