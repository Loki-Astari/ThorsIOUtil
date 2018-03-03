#ifndef THORSANVIL_IOUTIL_PRINT_INT_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_INT_TO_STREAM_H

#include "printToStream.h"

#include <ostream>
//#include <cstdint>
//#include <cstddef>
//#include <cctype>
#include <cmath>

namespace ThorsAnvil::IOUtil
{

inline long long            absm(long long arg)            {return std::abs(arg);}
inline long                 absm(long arg)                 {return std::abs(arg);}
inline int                  absm(int arg)                  {return std::abs(arg);}
inline unsigned long long   absm(unsigned long long arg)   {return arg;}
inline unsigned long        absm(unsigned long arg)        {return arg;}
inline unsigned int         absm(unsigned int arg)         {return arg;}

template<typename T>
inline void printIntToStream(std::ostream& s, T arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType)
{
    static double  const logFor16    = std::log10(16);
    static double  const logFor10    = std::log10(10);
    static double  const logFor08    = std::log10(8);

    double const&  logBase = s.flags() & std::ios_base::oct ? logFor08 : s.flags() & std::ios_base::hex ? logFor16 : logFor10;

    if (width == 0 && precision == -1)
    {
        s << arg;
    }
    else if (precision == -1)
    {
        std::size_t reduceWidth = 0;
        reduceWidth += ((arg >= 0 && forceSign) || arg < 0) ? 1 : 0;
        reduceWidth += (prefixType && (s.flags() & std::ios_base::oct)) ? 1 : 0;
        reduceWidth += (prefixType && (s.flags() & std::ios_base::hex)) ? 2 : 0;
        width        = reduceWidth > width ? 0 : width - reduceWidth;

        s.width(0);
        s.unsetf(std::ios_base::showpos | std::ios_base::showbase);
        std::size_t padding = 0;
        if (!leftPad)
        {
            std::size_t numberOfDigits = arg != 0 ? static_cast<int>((std::log10(absm(arg)) / logBase + 1)) : ( precision == 0 ? 0 : 1);;
            padding        = (numberOfDigits >= width) ? 0 :  (width - numberOfDigits);
            width          -= padding;
        }
        if (!leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        if ((arg >= 0 && forceSign) || arg < 0 )
        {
            s.put(arg < 0 ? '-' : '+');

            arg = absm(arg);
        }
        if (prefixType)
        {
            if (s.flags() & (std::ios_base::hex | std::ios_base::oct))
            {
                s.put('0');
            }
            if (s.flags() & std::ios_base::hex)
            {
                s.put(s.flags() & std::ios_base::uppercase ? 'X' : 'x');
            }
        }
        s.width(width);
        s << arg;
        if (leftJustify)
        {
            s.width(0);
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
    }
    else
    {
        s.width(0);
        s.unsetf(std::ios_base::showpos | std::ios_base::showbase);
        std::size_t extraWidth      =  (arg < 0) || (arg >=0 && forceSign) ? 1 : 0;

        if (s.flags() & std::ios_base::showbase)
        {
            switch (s.flags() & std::ios_base::basefield)
            {
                case std::ios_base::hex:    extraWidth += 2;break;
                case std::ios_base::oct:    extraWidth += 1;break;
            }
        }
        width = extraWidth > width ? 0 : width - extraWidth;

        std::size_t numberOfDigits = arg != 0 ? static_cast<int>((std::log10(absm(arg)) / logBase + 1)) : ( precision == 0 ? 0 : 1);;
        std::size_t sizeOfNumber   = numberOfDigits > precision ? numberOfDigits : precision;
        std::size_t prefix         = precision == -1 ? 0 : numberOfDigits > precision ? 0 : (precision - numberOfDigits);
        std::size_t padding        = (sizeOfNumber >= width) ? 0 :  (width - sizeOfNumber);
        if (!leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        if (arg < 0)
        {
            s.put('-');
        }
        else if (arg >=0 && forceSign)
        {
            s.put('+');
        }
        if (prefixType)
        {
            if (s.flags() & (std::ios_base::hex | std::ios_base::oct))
            {
                s.put('0');
            }
            if (s.flags() & std::ios_base::hex)
            {
                s.put(s.flags() & std::ios_base::uppercase ? 'X' : 'x');
            }
        }
        for(std::size_t loop = 0; loop < prefix; ++loop)
        {
            s.put('0');
        }
        if (precision != 0 || arg != 0)
        {
            s << absm(arg);
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

inline void printIntToStream(std::ostream& s, unsigned long long const& arg, int width, int precision, bool leftJustify, bool leftPad, bool forceSign, bool prefixType, bool)
{
    printIntToStream(s, arg, width, precision, leftJustify, leftPad, forceSign, prefixType);
}

}

#endif
