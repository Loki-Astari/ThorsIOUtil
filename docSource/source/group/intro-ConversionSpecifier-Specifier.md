---
layout: plain
generate: false
---
    Specifier
        %           %% generates '%'

        // The following match integer values.
        //      will match an int parameter unless modified by the `Length`
        d           prints a signed integer base 10
        i           prints a signed integer base 10
        o           prints an unsigned integer base 8
        u           prints an unsigned integer base 10
        X/x         prints an unsigned integer base 16

        // The following matches floating point values
        //      will match a double value unless modified by the `Length`
        f           prints using a fixed point notation:                -?ddd.ddd
        E/e         prints using expontent notation                     -?d.ddd[Ee][+-]?dd
        G/g         prints using fixed point or exponent notation.
        A/a         prints using a hexidecimal fraction notation.       -?0xh.hhh[Pp][+-]?dd

        // Charavter types
        //      Can use the `Length` modifier to change what it matches.
        c           matches a char input                prints an unsigned char
        s           matches a char* or std::string      prints a string of characters

        // Other conversions
        p           matches any pointer                 prints a hex number prefixed with 0x
        n           does not match anything             prints the number of characters printed

The specifier field basically describes what type of object is being serialized. There are basically four types of object:

* Interger
* Floating Point
* Character (String is a list of characters)
* Pointer

There are two special cases:

* `%%`: This is the escape sequence and generates a '%' character.
* `%n`: Outputs the number of characters serialized to the output stream.

Example:    `%d`

