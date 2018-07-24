# ThorsIOUtil
Provides IO string formatting functionality that matches that provided by `printf()`.

This library also uses the same set of tests as used by GNU to test the functionality.


### Example.cpp
````
#include ""
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
