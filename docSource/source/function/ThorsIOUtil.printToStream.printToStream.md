---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/printToStream.h
    function:  printToStream
    description:  |
        Template method for strings
    template:  template<typename T> 
    return:
        type: 'std::ostream& s'
        description: 
    parameters:
        - name: s
          type: 'std::ostream&'
          default: 
          description: 
        - name: arg
          type: 'char const* const&'
          default: 
          description: 
        - name: info
          type: 'FormatInfo const&'
          default: 
          description: 
children: []
---
