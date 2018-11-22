---
layout: plain
generate: false
---
    Flags:  one or more of:
        // For integers, floating point, char, string and pointer values
        -           Left justify output inside the field.
                    This assumes you specify a `<Width>` field otherwise this will have no affect

        // For integers and floating point values
        +           Print the '+' symbol for positive values.
        <Space>     Print the ' ' symbol for positive values (ignored if + also used)
                    This helps positive and negative values align with forcing the '+' symbol
        '           Seporate digits into groups specified by LC_NUMERIC
        0           Pad number with zero rather than space. Padding comes after sign and base information.
                    It is used to make sure the serialized output is at least `<Width>` wide.
                    Ignored if the '-' flag is used.

        // For integers values
        #           Add base information to number (After sign)
                    For %o values prefix value with '0'
                    For %x values prefix value with '0x'
                    For %X values prefix value with '0X'
        // For floating point values
        #           Allways add a decimal point
                    For %g %G forces trailing zero after decimal point.

The flag field is optional. If used you can use one or more of the flag characters to control how the value is serialized.

Example: `%#x`
