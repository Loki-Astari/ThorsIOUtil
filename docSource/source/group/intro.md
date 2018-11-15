---
layout: plain
generate: false
---

[ThorsIOUtil](https://github.com/Loki-Astari/ThorsIOUtil) A C++ IO type stream formatting like `printf()`.

````c++
    #include "ThorsIOUtil/Format.h"

    int main()
    {
        namespace tio = ThorsAnvil::IOUtil;
        std::cout << tio::make_format("A standard printf format string "%d : %20s", 15, "Text") << "\n";
    }
````

This library has been tested using the test suite used by GNU.


