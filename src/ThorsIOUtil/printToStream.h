#ifndef THORSANVIL_IOUTIL_PRINT_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_TO_STREAM_H

#include "printIntToStream.h"

#include <ostream>

namespace ThorsAnvil::IOUtil
{

template<typename T>
inline void printToStream(std::ostream& s, T const& arg, int, int, bool, bool, bool, bool, bool)
{
    s << arg;
}

// Signed integers.
inline void printToStream(std::ostream& s, long long const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool)
{
    printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
}

inline void printToStream(std::ostream& s, long const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool)
{
    printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
}

inline void printToStream(std::ostream& s, int const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool isChar)
{
    if (isChar)
    {
        printToStream(s, static_cast<char>(arg), width, precision, leftJustify, leftPad, forceSign, prefixType, isChar);
    }
    else
    {
        printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
    }
}

// Unsigned integers.
inline void printToStream(std::ostream& s, unsigned long long const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool, bool)
{
    printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
}

inline void printToStream(std::ostream& s, unsigned long const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool, bool)
{
    printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
}

inline void printToStream(std::ostream& s, unsigned int const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool isChar)
{
    if (isChar)
    {
        printToStream(s, static_cast<char>(arg), width, precision, leftJustify, leftPad, forceSign, prefixType, isChar);
    }
    else
    {
        printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
    }
}

// C-String
inline void printToStream(std::ostream& s, char const* const& arg, int width, int precision, bool leftJustify, bool, bool, bool prefixType, bool)
{
    if (precision == -1)
    {
        s << arg;
    }
    else
    {
        s.width(0);
        std::size_t     padding = (precision >= width) ? 0 :  (width - precision);
        if (!leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        for(std::size_t loop = 0; arg[loop] != '\0' && loop < precision; ++loop)
        {
            s.put(arg[loop]);
        }
        if (leftJustify)
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
