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
        std::size_t             used;
        // Flags
        enum class Length    {none, hh, h, l, ll, j, z, t, L};
        enum class Specifier {d, i, u, o, x, X, f, F, e, E, g, G, a, A, c, s, p, n};
        bool                    leftJustify;    // -    Left-justify within the given field width; Right justification is the default (see width sub-specifier).
        bool                    forceSign;      // +    Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
        bool                    forceSignWidth; // (space)  If no sign is going to be written, a blank space is inserted before the value.
        bool                    prefixType;     // #    Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero.
                                                // Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
        bool                    leftPad;        // 0    Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).
        int                     width;
        int                     precision;
        Length                  length;
        Specifier               specifier;
        std::type_info const*   expectedType;
        std::ios_base::fmtflags format;

        public:
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
                char const* fmt = formatStr;
                assert(*fmt == '%');

                bool flag = true;
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
                if (std::isdigit(*fmt)) {
                    char* end;
                    width = std::strtol(fmt, &end, 10);
                    fmt = end;
                }
                if (*fmt == '.') {
                    ++fmt;
                    if (std::isdigit(*fmt)) {
                        char* end;
                        precision = std::strtol(fmt, &end, 10);
                        fmt = end;
                    }
                    else {
                        precision = 0;
                    }
                }
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
                switch(*fmt) {
                    case 'd':   specifier = Specifier::d;break;
                    case 'i':   specifier = Specifier::i;break;
                    case 'u':   specifier = Specifier::u;break;
                    case 'o':   specifier = Specifier::o;break;
                    case 'x':   specifier = Specifier::x;break;
                    case 'X':   specifier = Specifier::X;break;
                    case 'f':   specifier = Specifier::f;break;
                    case 'F':   specifier = Specifier::F;break;
                    case 'e':   specifier = Specifier::e;break;
                    case 'E':   specifier = Specifier::E;break;
                    case 'g':   specifier = Specifier::g;break;
                    case 'G':   specifier = Specifier::G;break;
                    case 'a':   specifier = Specifier::a;break;
                    case 'A':   specifier = Specifier::A;break;
                    case 'c':   specifier = Specifier::c;break;
                    case 's':   specifier = Specifier::s;break;
                    case 'p':   specifier = Specifier::p;break;
                    case 'n':   specifier = Specifier::n;break;
                    default:
                       throw std::invalid_argument(std::string("Invalid Parameter specifier: ") + *fmt);
                }
                ++fmt;

                expectedType = getType(specifier, length);

                used  = fmt - formatStr;

                format  |= (leftJustify ? std::ios_base::left : std::ios_base::right);

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
                if (specifier == Specifier::X || specifier == Specifier::F || specifier == Specifier::E || specifier == Specifier::A || specifier == Specifier::G) {
                    format |= std::ios_base::uppercase;
                }
                if (prefixType && (specifier == Specifier::o || specifier == Specifier::x || specifier == Specifier::X)) {
                    format |= std::ios_base::showbase;
                }
                if (prefixType && (specifier == Specifier::a || specifier == Specifier::A || specifier == Specifier::e || specifier == Specifier::E || specifier == Specifier::f || specifier == Specifier::F || specifier == Specifier::g || specifier == Specifier::G)) {
                    format |= std::ios_base::showpoint;
                }
                if (forceSign && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) {
                    format |= std::ios_base::showpos;
                }
            }
            std::size_t size() const {return used;}

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


                    char fill      = (!leftJustify && leftPad && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) ? '0' : ' ';
                    int  fillWidth = width;

                    if (forceSignWidth && !forceSign && (arg >= 0) && (specifier != Specifier::c && specifier != Specifier::s && specifier != Specifier::p)) {
                        s << ' ';
                        --fillWidth;
                    }
                    std::ios_base::fmtflags oldFlags = s.flags(format);
                    char                    oldFill  = s.fill(fill);
                    int                     oldWidth = s.width(fillWidth);
                    std::streamsize         oldPrec  = s.precision(precision);

                    s << arg;

                    s.precision(oldPrec);
                    s.width(oldWidth);
                    s.fill(oldFill);
                    s.flags(oldFlags);
                }

                static std::type_info const* getType(Specifier specifier, Length length)
                {
                    static std::map<std::pair<Specifier, Length>, std::type_info const*>    typeMap = {
                        {{Specifier::d, Length::none}, &typeid(int)},           {{Specifier::i, Length::none}, &typeid(int)},           {{Specifier::d, Length::none}, &typeid(int*)},
                        {{Specifier::d, Length::hh},   &typeid(signed char)},   {{Specifier::i, Length::none}, &typeid(signed char)},   {{Specifier::d, Length::hh},   &typeid(signed char*)},
                        {{Specifier::d, Length::h},    &typeid(short int)},     {{Specifier::i, Length::none}, &typeid(short int)},     {{Specifier::d, Length::h},    &typeid(short int*)},
                        {{Specifier::d, Length::l},    &typeid(long int)},      {{Specifier::i, Length::none}, &typeid(long int)},      {{Specifier::d, Length::l},    &typeid(long int*)},
                        {{Specifier::d, Length::ll},   &typeid(long long int)}, {{Specifier::i, Length::none}, &typeid(long long int)}, {{Specifier::d, Length::ll},   &typeid(long long int*)},
                        {{Specifier::d, Length::j},    &typeid(std::intmax_t)}, {{Specifier::i, Length::none}, &typeid(std::intmax_t)}, {{Specifier::d, Length::j},    &typeid(std::intmax_t*)},
                        {{Specifier::d, Length::z},    &typeid(std::size_t)},   {{Specifier::i, Length::none}, &typeid(std::size_t)},   {{Specifier::d, Length::z},    &typeid(std::size_t*)},
                        {{Specifier::d, Length::t},    &typeid(std::ptrdiff_t)},{{Specifier::i, Length::none}, &typeid(std::ptrdiff_t)},{{Specifier::d, Length::t},    &typeid(std::ptrdiff_t*)},


                        {{Specifier::u, Length::none}, &typeid(unsigned int)},          {{Specifier::o, Length::none}, &typeid(unsigned int)},          {{Specifier::x, Length::none}, &typeid(unsigned int)},          {{Specifier::X, Length::none}, &typeid(unsigned int)},
                        {{Specifier::u, Length::hh},   &typeid(unsigned char)},         {{Specifier::o, Length::hh},   &typeid(unsigned char)},         {{Specifier::x, Length::hh},   &typeid(unsigned char)},         {{Specifier::X, Length::hh},   &typeid(unsigned char)},
                        {{Specifier::u, Length::h},    &typeid(unsigned short int)},    {{Specifier::o, Length::h},    &typeid(unsigned short int)},    {{Specifier::x, Length::h},    &typeid(unsigned short int)},    {{Specifier::X, Length::h},    &typeid(unsigned short int)},
                        {{Specifier::u, Length::l},    &typeid(unsigned long int)},     {{Specifier::o, Length::l},    &typeid(unsigned long int)},     {{Specifier::x, Length::l},    &typeid(unsigned long int)},     {{Specifier::X, Length::l},    &typeid(unsigned long int)},
                        {{Specifier::u, Length::ll},   &typeid(unsigned long long int)},{{Specifier::o, Length::ll},   &typeid(unsigned long long int)},{{Specifier::x, Length::ll},   &typeid(unsigned long long int)},{{Specifier::X, Length::ll},   &typeid(unsigned long long int)},
                        {{Specifier::u, Length::j},    &typeid(std::uintmax_t)},        {{Specifier::o, Length::j},    &typeid(std::uintmax_t)},        {{Specifier::x, Length::j},    &typeid(std::uintmax_t)},        {{Specifier::X, Length::j},    &typeid(std::uintmax_t)},
                        {{Specifier::u, Length::z},    &typeid(std::size_t)},           {{Specifier::o, Length::z},    &typeid(std::size_t)},           {{Specifier::x, Length::z},    &typeid(std::size_t)},           {{Specifier::X, Length::z},    &typeid(std::size_t)},
                        {{Specifier::u, Length::t},    &typeid(ptrdiff_t)},             {{Specifier::o, Length::t},    &typeid(ptrdiff_t)},             {{Specifier::x, Length::t},    &typeid(ptrdiff_t)},             {{Specifier::X, Length::t},    &typeid(ptrdiff_t)},

                        {{Specifier::f, Length::none}, &typeid(double)}, {{Specifier::F, Length::none}, &typeid(double)},   {{Specifier::f, Length::L}, &typeid(long double)}, {{Specifier::F, Length::L}, &typeid(long double)},
                        {{Specifier::e, Length::none}, &typeid(double)}, {{Specifier::E, Length::none}, &typeid(double)},   {{Specifier::e, Length::L}, &typeid(long double)}, {{Specifier::E, Length::L}, &typeid(long double)},
                        {{Specifier::g, Length::none}, &typeid(double)}, {{Specifier::G, Length::none}, &typeid(double)},   {{Specifier::g, Length::L}, &typeid(long double)}, {{Specifier::G, Length::L}, &typeid(long double)},
                        {{Specifier::a, Length::none}, &typeid(double)}, {{Specifier::A, Length::none}, &typeid(double)},   {{Specifier::a, Length::L}, &typeid(long double)}, {{Specifier::A, Length::L}, &typeid(long double)},

                        {{Specifier::c, Length::none}, &typeid(int)},   {{Specifier::c, Length::l}, &typeid(std::wint_t)},
                        {{Specifier::s, Length::none}, &typeid(char*)}, {{Specifier::c, Length::l}, &typeid(wchar_t*)},

                        {{Specifier::p, Length::none}, &typeid(void*)}
                    };
                    auto find = typeMap.find({specifier, length});
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
            prefixString.emplace_back(format.substr(pos, format.size() - pos));
        }
        void print(std::ostream& s) const
        {
            doPrint(s, std::make_index_sequence<sizeof...(Args)>());
        }
    private:
        template<typename A>
        struct Printer
        {
            Printer(std::ostream& s, std::string const& prefix, Formatter const& format, A const& value)
            {
                s << prefix << format << value;
            }
        };
        template<typename A>
        void forward(A const&...) const{}
        template<std::size_t... I>
        void doPrint(std::ostream& s, std::index_sequence<I...> const&) const
        {
            forward(1, Printer<decltype(std::get<I>(arguments))>(s, prefixString[I], formater[I], std::get<I>(arguments))...);
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
