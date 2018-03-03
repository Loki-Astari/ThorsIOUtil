#ifndef THORSANVIL_IOUTIL_PRINT_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_TO_STREAM_H

#include "FormatInfo.h"
#include "printIntToStream.h"

#include <ostream>

namespace ThorsAnvil::IOUtil
{

template<typename T>
inline void printToStream(std::ostream& s, T const& arg, int, FormatInfo const&)
{
    s << arg;
}

// Signed integers.
inline void printToStream(std::ostream& s, long long const& arg, int width, FormatInfo const& info)
{
    printIntToStream(s, arg, width, info);
}

inline void printToStream(std::ostream& s, long const& arg, int width, FormatInfo const& info)
{
    printIntToStream(s, arg, width, info);
}

inline void printToStream(std::ostream& s, int const& arg, int width, FormatInfo const& info)
{
    if (info.type == Type::Char)
    {
        printToStream(s, static_cast<char>(arg), width, info);
    }
    else
    {
        printIntToStream(s, arg, width, info);
    }
}

// Unsigned integers.
inline void printToStream(std::ostream& s, unsigned long long const& arg, int width, FormatInfo const& info)
{
    printIntToStream(s, arg, width, info);
}

inline void printToStream(std::ostream& s, unsigned long const& arg, int width, FormatInfo const& info)
{
    printIntToStream(s, arg, width, info);
}

inline void printToStream(std::ostream& s, unsigned int const& arg, int width, FormatInfo const& info)
{
    if (info.type == Type::Char)
    {
        printToStream(s, static_cast<char>(arg), width, info);
    }
    else
    {
        printIntToStream(s, arg, width, info);
    }
}

// C-String
inline void printToStream(std::ostream& s, char const* const& arg, int width, FormatInfo const& info)
{
    if (info.precision == -1)
    {
        s << arg;
    }
    else
    {
        s.width(0);
        std::size_t     padding = (info.precision >= width) ? 0 :  (width - info.precision);
        if (!info.leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        for(std::size_t loop = 0; arg[loop] != '\0' && loop < info.precision; ++loop)
        {
            s.put(arg[loop]);
        }
        if (info.leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
    }
}

}

#endif
