---
layout: plain
generate: false
---
    Length: 
        // The specifiers d/i/o/u/x/X match integer values.
        // Unless proceeeded by one of the following length specifiers.
        // That allow us match against alternatives object types.
        hh          matches a char      or  unsigned char           parameter
        h           marches a short     or  unsigned short          parameter
        l           matches a long      or  unsigned long           parameter
        ll          matches a long long or  unsigned long long      parameter
        L           matches a long long or  unsigned long long      parameter
        q           matches a long long or  unsigned long long      parameter
        j           matches a std::intmax_t                         parameter
        t           matches a std::ptrdiff_t                        parameter
        z           matches a std::size_t                           parameter

        // The following match floating point values unless modified by the Length parameter
        L           matches a long double                           parameter

        // The following match char and string conversions.
        //      rather than `char` the base of the char/string will be std::wchar_t


The `<Length>` specifier changes the type of value that is bound to the specifier.

Example:    `%ld`

