#ifndef THORSANVIL_IOUTIL_PRINT_INT_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_INT_TO_STREAM_H

#include "FormatInfo.h"
#include "printToStream.h"

#include <ostream>
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
inline void printIntToStream(std::ostream& s, T arg, int width, FormatInfo const& info)
{
    static long double  const logFor16    = std::log10(16.0L);
    static long double  const logFor10    = std::log10(10.0L);
    static long double  const logFor08    = std::log10(8.0L);

    double const&  logBase = s.flags() & std::ios_base::oct ? logFor08 : s.flags() & std::ios_base::hex ? logFor16 : logFor10;

    if (width == 0 && info.precision == -1)
    {
        s << arg;
    }
    else if (info.precision == -1)
    {
        std::size_t reduceWidth = 0;
        bool octOrHex = s.flags() & (std::ios_base::oct | std::ios_base::hex);
        reduceWidth += ((arg >= 0 && info.forceSign && !octOrHex) || arg < 0) ? 1 : 0;
        reduceWidth += (info.prefixType && (s.flags() & std::ios_base::oct)) ? 1 : 0;
        reduceWidth += (info.prefixType && (s.flags() & std::ios_base::hex)) ? 2 : 0;
        width        = reduceWidth > width ? 0 : width - reduceWidth;

        s.width(0);
        s.unsetf(std::ios_base::showpos | std::ios_base::showbase);
        std::size_t padding = 0;
        if (!info.leftPad)
        {
            std::size_t numberOfDigits = arg != 0 ? static_cast<int>((std::log10(static_cast<long double>(absm(arg))) / logBase + 1)) : ( info.precision == 0 ? 0 : 1);;
            padding        = (numberOfDigits >= width) ? 0 :  (width - numberOfDigits);
            width          -= padding;
        }
        if (!info.leftJustify)
        {
            for(std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        if ((arg >= 0 && info.forceSign && !octOrHex) || arg < 0 )
        {
            s.put(arg < 0 ? '-' : '+');

            arg = absm(arg);
        }
        if (info.prefixType)
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
        if (info.leftJustify)
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
        bool octOrHex = s.flags() & (std::ios_base::oct | std::ios_base::hex);
        s.width(0);
        s.unsetf(std::ios_base::showpos | std::ios_base::showbase);
        std::size_t extraWidth      = (arg < 0) || (arg >=0 && info.forceSign && !octOrHex) ? 1 : 0;
        std::size_t extraDigits     = 0;

        if (info.prefixType)
        {
            switch (s.flags() & std::ios_base::basefield)
            {
                case std::ios_base::hex:    extraWidth  += 2;break;
                case std::ios_base::oct:    extraDigits += 1;break;
            }
        }
        width = extraWidth > width ? 0 : width - extraWidth;

        std::size_t numberOfDigits = arg != 0 ? static_cast<int>((std::log10(static_cast<long double>(absm(arg))) / logBase + 1)) : ( info.precision == 0 ? 0 : 1);;
        numberOfDigits += extraDigits;
        std::size_t sizeOfNumber   = numberOfDigits > info.precision ? numberOfDigits : info.precision;
        std::size_t prefix         = info.precision == -1 ? 0 : numberOfDigits > info.precision ? 0 : (info.precision - numberOfDigits);
        std::size_t padding        = (sizeOfNumber >= width) ? 0 :  (width - sizeOfNumber);
        if (!info.leftJustify)
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
        else if (arg >=0 && info.forceSign && !octOrHex)
        {
            s.put('+');
        }
        if (info.prefixType)
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
        if (info.precision != 0 || arg != 0)
        {
            s << absm(arg);
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
