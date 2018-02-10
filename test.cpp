
#include "format.h"

#include <iostream>

int main()
{
    using ThorsAnvil::IOUtil::make_format;

    std::cout << make_format("Test One\n");
    std::cout << make_format("Test Two   %d\n", 12);
    std::cout << make_format("Test Three %d %f\n", 12, 4.56);
    std::cout << make_format("Test Four  %d %d\n", 12, 4.56); // Should throw
}

