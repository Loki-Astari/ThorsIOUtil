---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/Format.h
    function:  make_cppformat
    description:  |
        Builds a `Format` object based on the types of the arguments.
        
        This version has slightly tighter restrictions on matching parameters to conversion specifiers.
        Like C++ the type system is much pickier than C.
        @param fmt       The format string.
        @param Args      Template parameter pack. Each argument is matched to a conversion specifier.
        @return          A format object that keeps a const reference to each argument.
    template:  template<typename... Args> 
children: []
---
