---
layout: package
generate: false
nameSpace:  ThorsAnvil::IOUtil
headers:
    base: ThorsIOUtil
    files:
        - name:   printToStream.h
          functions:
            - return: void
              name:   printToStreamDefault
              param:  [   std::ostream& s,  T const& arg,  FormatInfo const&  ]
            - return: void
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
          classes: []
children:
    - name: printToStreamDefault
      value: ThorsIOUtil.printToStream.printToStreamDefault.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
---
