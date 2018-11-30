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
    template:  template<typename... Args> 
    return:
        type: 'char const* fmt'
        description: 'A format object that keeps a const reference to each argument.'
    parameters:
        - name: fmt
          type: 'char const*'
          default: 
          description: 'The format string.'
        - name: args
          type: 'Args const&...'
          default: 
          description: 'Template parameter pack. Each argument is matched to a conversion specifier.'
children: []
---
