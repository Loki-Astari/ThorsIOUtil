---
layout: plain
generate: false
---
````Cpp
#include "ThorsIOUtil/Format.h"
#include <iostream>

using namespace Fmt = ThorsAnvil::IOUtil;

int main()
{
    short shortValue = 10;
    std::cout << Fmt::make_format("Print short >%hd<\n", shortValue);
    std::cout << Fmt::make_cppformat("Print short >%hd<\n", shortValue);

    int intValue = 10;
    std::cout << Fmt::make_format("Print short >%hd<\n", intValue);
    std::cout << Fmt::make_cppformat("Print short >%hd<\n", intValue);  // This will throw a runtime error.
}
````
In C `char` and `short` values are converted to int before being passed as arguments to `printf()`. Thus the `<Length>` fields `hh` and `h` will convert the int back to the appropriate type (char, short) before `printf()` serializes the value. This has the side affect that you can pass `int` values to `printf()` and it will serialize correctly.

To conform with `C` we also allow `int` values to bind to `%hd` and `%hhd` *conversion specifiers* by default. But we also provide a stricter interpretation for C++ users that only allows `char` to bind to `%hhd` values and `short` to bind to `%hd` values.

If you use `make_format()` the formatter uses C compatibility mode and will match `%hhd` and `%hd` against `int` values in addition to the match type expected.

If you use `make_cppformat()` the *conversion specifiers* use the stricter C++ type mode.


