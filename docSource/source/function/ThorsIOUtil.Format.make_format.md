---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/Format.h
    function:  make_format
    description:  |
        Builds a `Format` object based on the types of the arguments.
        @param fmt       The format string.
        @param Args      Template parameter pack. Each argument is matched to a conversion specifier.
        @return          A format object that keeps a const reference to each argument.
    template:  template<typename... Args> 
children: []
---
