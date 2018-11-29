---
layout: package
generate: false
nameSpace:  ThorsAnvil::IOUtil
headers:
    base: ThorsIOUtil
    files:
        - name:   Format.h
          functions:
            - return: Format<Args...>
              name:   make_format
              param:  [   char const* fmt,  Args const&... args  ]
            - return: Format<Args...>
              name:   make_cppformat
              param:  [   char const* fmt,  Args const&... args  ]
          classes: []
children:
    - name: make_format
      value: ThorsIOUtil.Format.make_format.md
    - name: make_cppformat
      value: ThorsIOUtil.Format.make_cppformat.md
---
