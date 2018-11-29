---
layout: class
generate: false
typeInfo:
    namespace: ThorsAnvil::IOUtil
    header:    ThorsIOUtil/Format.h
    classname: Format
    parent:    
    template:  template<typename... Args>
    description:  |
        This is the object returned by make_format() and make_cppformat()
        This is the object that is passed to the `std::ostream` via `operator<<`.
        
        Internally it keeps the original string and references to all the parameters that
        need to be serialized. When the object is constructed (at runtime) the conversion
        specifiers in the string are validated against the actual parameters to make sure
        the correctly match.
    methods: []
    protected: []
    virtual: []
children: []
---
