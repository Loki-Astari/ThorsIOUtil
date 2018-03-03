#ifndef THORSANVIL_IOUTIL_PRINT_STRING_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_STRING_TO_STREAM_H

#include "FormatInfo.h"
#include "printToStream.h"

namespace ThorsAnvil::IOUtil
{

inline void printStringToStream(std::ostream& s, char const* const& arg, int width, FormatInfo const& info)
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
