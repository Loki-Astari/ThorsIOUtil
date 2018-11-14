#ifndef THORSANVIL_IOUTIL_FORMAT_H
#define THORSANVIL_IOUTIL_FORMAT_H

#include "printToStream.h"
#include "Formatter.h"

#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

namespace ThorsAnvil::IOUtil
{

template<typename... Args>
// @class
class Format
{
    std::string                     format;
    std::tuple<Args const&...>      arguments;
    std::vector<std::string>        prefixString;
    std::vector<Formatter>          formater;
    public:
        Format(char const* fmt, Args const&... args)
            : format(fmt)
            , arguments(args...)
        {
            std::size_t count       = sizeof...(args);
            std::size_t pos         = 0;
            Dynamic     dynamicSize = Dynamic::None;
            for (std::size_t loop = 0; loop < count; ++loop)
            {
                // Find the prefix string before the next % sign (this may be empty)
                std::pair<std::string, std::size_t> prefix = getNextPrefix(format, pos, [](std::size_t p){return p == std::string::npos;}, "not enough format");
                pos += prefix.second;
                prefixString.emplace_back(std::move(prefix.first));

                // Now that I have found the %
                // Convert the next part of the string into a Formatter object.
                formater.emplace_back(format.data() + pos, dynamicSize);
                pos         += formater.back().size();

                // Take into account the Dynamic Width/Precesion prevent the format from being read.
                // Note we can have Width/Precision or Both.
                Dynamic     newDynamic  = formater.back().isDynamicSize();
                dynamicSize = (newDynamic == Dynamic::Precision && dynamicSize == Dynamic::Width) ? Dynamic::Both : newDynamic;
            }
            // After the last formatter check for a last fixed string (this may be empty)
            // But there better not be any more % signs as we don't have any parameters left for them.
            std::pair<std::string, std::size_t> prefix = getNextPrefix(format, pos, [](std::size_t p){return p != std::string::npos;}, "too many format");
            pos += prefix.second;
            prefixString.emplace_back(std::move(prefix.first));
        }
        // Using the operator<< is the same as calling print on the object.
        friend std::ostream& operator<<(std::ostream& s, Format const& format)
        {
            format.print(s);
            return s;
        }
        void print(std::ostream& s) const
        {
            doPrint(s, std::make_index_sequence<sizeof...(Args)>());
        }
    private:
        // This finds the next '%' taking into account that %% is a not a scan token.
        std::pair<std::string, std::size_t> getNextPrefix(std::string const&, std::size_t pos, std::function<bool(std::size_t)>&& test, char const* mes)
        {
            std::string prefix;
            std::size_t extra = 0;
            std::size_t nextFormatter = format.find('%', pos);
            while (nextFormatter != std::string::npos && format[nextFormatter + 1] == '%')
            {
                nextFormatter = format.find('%', nextFormatter + 2);
            }
            prefix += format.substr(pos, nextFormatter - pos);
            prefix.erase(std::remove_if(std::begin(prefix), std::end(prefix), [first = false](char val) mutable
            {
                if (val == '%')
                {
                    first = !first;
                    return !first;
                }
                return false;
            }), std::end(prefix));
            if (test(nextFormatter))
            {
                std::stringstream message;
                message << "Invalid Format: " << mes << " specifiers for provided arguments";
                throw std::invalid_argument(message.str());
            }
            return {prefix, prefix.size() + extra};
        }
        // For each argument we pass
        // Pass a prefix string (might be empty) the formatter then the argument.
        template<std::size_t I>
        std::ostream& printValue(std::ostream& s) const
        {
            return s << prefixString[I] << formater[I] << std::get<I>(arguments);
        }

        // Print all the values in order by calling printValue() on each parameter.
        // Then print the final fixed string (might be empty)
        template<std::size_t... I>
        void doPrint(std::ostream& s, std::index_sequence<I...> const&) const
        {
            std::ostream* ignore[] = {&printValue<I>(s)...};
            s << prefixString.back();
        }

};

template<typename... Args>
// @class
Format<Args...> make_format(char const* fmt, Args const&... args)
{
    return Format<Args...>(fmt, args...);
}

}

#endif
