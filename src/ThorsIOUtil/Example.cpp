#include "Example.h"
#include "Format.h"
#include <iostream>

using namespace ThorsAnvil::IOUtil;

int main()
{
    std::cout << "Testing\n";
    std::cout << make_format("Print Intere >%5.3d<\n", 5);   // Print Intere >  005<
    std::cout << make_format("Testing\n");

    std::cout << make_format("Integer Literal:  %hhd %hd %d %ld %lld\n", 0, 0, 0, 0L, 0LL);

    char        i1 = 1;
    short       i2 = 2;
    int         i3 = 3;
    long        i4 = 4;
    long long   i5 = 5;
    std::cout << make_format("Integer Variable: %hhd %hd %d %ld %lld\n", i1, i2, i3, i4, i5);


    //std::cout << Fmt::make_cppformat("Integer Variable: %hhd\n", i5);
}
