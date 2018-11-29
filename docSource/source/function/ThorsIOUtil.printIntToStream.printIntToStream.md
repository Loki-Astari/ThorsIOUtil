---
layout: function
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/printIntToStream.h
    function:  printIntToStream
    description:  |
        Given an argument `arg` (which is one of the int types) and a format `info` serialize it to the stream `s`
        @param s             stream to serialize onto
        @param arg           the integer argument we want to serialize
        @param info          formatInfo object that defines how to serialize arg
    template:  template<typename T> 
children: []
---
