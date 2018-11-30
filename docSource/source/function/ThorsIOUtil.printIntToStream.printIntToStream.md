---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/printIntToStream.h
    function:  printIntToStream
    description:  |
        Given an argument `arg` (which is one of the int types) and a format `info` serialize it to the stream `s`
    template:  template<typename T> 
    return:
        type: 'std::ostream& s'
        description: 
    parameters:
        - name: s
          type: 'std::ostream&'
          default: 
          description: 'stream to serialize onto the integer argument we want to serialize formatInfo object that defines how to serialize arg'
        - name: arg
          type: 'T'
          default: 
          description: 'the integer argument we want to serialize formatInfo object that defines how to serialize arg'
        - name: info
          type: 'FormatInfo const&'
          default: 
          description: 'formatInfo object that defines how to serialize arg'
children: []
---
