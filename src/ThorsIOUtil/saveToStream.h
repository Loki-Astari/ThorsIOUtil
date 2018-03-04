#ifndef THORSANVIL_IOUTIL_SAVE_TO_STREAM_H
#define THORSANVIL_IOUTIL_SAVE_TO_STREAM_H

#include "FormatInfo.h"
#include <iostream>

namespace ThorsAnvil::IOUtil
{

template<typename T>
inline void saveToStream(std::ostream&, Dynamic, T const&)
{}

template<>
inline void saveToStream(std::ostream& s, Dynamic pos, int const& size)
{
    s.iword(static_cast<int>(pos)) = size;
}

}

#endif