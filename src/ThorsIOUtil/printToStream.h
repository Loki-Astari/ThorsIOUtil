#ifndef THORSANVIL_IOUTIL_PRINT_TO_STREAM_H
#define THORSANVIL_IOUTIL_PRINT_TO_STREAM_H

#include "FormatInfo.h"
#include "printIntToStream.h"
#include "printStringToStream.h"

#include <ostream>

namespace ThorsAnvil::IOUtil
{

template<typename T>
inline void printToStreamDefault(std::ostream& s, T const& arg, int, FormatInfo const&)
{
    s << arg;
}

template<typename T>
inline
typename std::enable_if<!std::is_integral<T>::value>::type
printToStream(std::ostream& s, T const& arg, int width, FormatInfo const& info)
{
    printToStreamDefault(s, arg, width, info);
}

template<typename T>
struct CharIntConverter
{
    using Integer   = T;
    using Character = T;
};
template<>
struct CharIntConverter<int>
{
    using Integer   = int;
    using Character = char;
};
template<>
struct CharIntConverter<unsigned int>
{
    using Integer   = unsigned int;
    using Character = char;
};
template<>
struct CharIntConverter<char>
{
    using Integer   = unsigned int;
    using Character = char;
};
template<>
struct CharIntConverter<unsigned char>
{
    using Integer   = unsigned int;
    using Character = char;
};


template<typename T>
inline 
typename std::enable_if<std::is_integral<T>::value>::type
printToStream(std::ostream& s, T const& arg, int width, FormatInfo const& info)
{
    if (info.type == Type::Char)
    {
        printToStreamDefault(s, static_cast<typename CharIntConverter<T>::Character>(arg), width, info);
    }
    else
    {
        printIntToStream(s, static_cast<typename CharIntConverter<T>::Integer>(arg), width, info);
    }
}

// C-String
inline void printToStream(std::ostream& s, char const* const& arg, int width, FormatInfo const& info)
{
    printStringToStream(s, arg, width, info);
}


}

#endif
