---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/Format.h
    function:  make_format
    description:  |
        Builds a `Format` object based on the types of the arguments.
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
