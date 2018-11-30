---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/printStringToStream.h
    function:  printStringToStream
    description:  |
        Given an argument `arg` and a format `info` serialize it to the stream `s`
    template:   
    return:
        type: 'std::ostream& s'
        description: 
    parameters:
        - name: s
          type: 'std::ostream&'
          default: 
          description: 'stream to serialize onto the string argument we want to serialize formatInfo object that defines how to serialize arg'
        - name: arg
          type: 'char const* const&'
          default: 
          description: 'the string argument we want to serialize formatInfo object that defines how to serialize arg'
        - name: info
          type: 'FormatInfo const&'
          default: 
          description: 'formatInfo object that defines how to serialize arg'
children: []
---
