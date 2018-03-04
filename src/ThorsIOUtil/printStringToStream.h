#ifndef THORSANVIL_IOUTIL_PRINT_STRING_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_STRING_TO_STREAM_H

#include "FormatInfo.h"
#include "printToStream.h"

namespace ThorsAnvil::IOUtil
{

inline void printStringToStream(std::ostream& s, char const* const& arg, std::size_t width, std::size_t precision, bool forceLeft, FormatInfo const& info)
{
    if (precision == -1)
    {
        s << arg;
    }
    else
    {
        s.width(0);
        std::size_t     padding = (precision >= width) ? 0 :  (width - precision);
        if (!forceLeft)
        {
            for (std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
        for (std::size_t loop = 0; arg[loop] != '\0' && loop < precision; ++loop)
        {
            s.put(arg[loop]);
        }
        if (forceLeft)
        {
            for (std::size_t loop = 0; loop < padding; ++loop)
            {
                s.put(' ');
            }
        }
    }
}

}

#endif
