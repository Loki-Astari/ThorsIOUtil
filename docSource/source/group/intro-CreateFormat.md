---
layout: plain
generate: false
---
````cpp
#include "ThorsIOUtil/Format.h"
#include <iostream>

using namespace Fmt = ThorsAnvil::IOUtil;

int main()
{
    std::cout << Fmt::make_format("Print Integre >%5.3d<\n", 5);   // Print Integre >  005<
}
````
So how do you build a `Format` object?

The easiest way is to use the `make_format(<format string> [, argument]*)`. This function takes the format string and the arguments and creates a `Format` object using the types of the arguments to construct a Format object of the correct type. Note this can be done by hand, but like `std::pair<>` it is simpler to use the utility function.


