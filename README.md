[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/G2G216KZR3)

![ThorStream](img/IOUtil.jpg)

# ThorsIOUtil
Provides IO string formatting functionality that matches that provided by `printf()`.

This library also uses the same set of tests as used by GNU to test the functionality.

[Full Documentation](https://lokiastari.com/ThorsIOUtil/#introduction)

### Example.cpp
````
#include "ThorsIOUtil/Format.h"
#include <iostream>

int main()
{
    namespace IO = ThorsAnvil::IOUtil;

    // Plain and simplt:
    std::cout << IO::make_format("This is string %s followed by a number %d or is it?", "The string", 45);
    
    // Some formatting
    std::cout << IO::make_format("Interesting Long Long %#+21.18llx", -100LL);
    // This should output: "Interesting Long Long  0x00ffffffffffffff9c"
}
````
