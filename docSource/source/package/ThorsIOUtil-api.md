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
          classes:
            - name:   Format
              parent:  
        - name:   FormatInfo.h
          functions: []
          classes:
            - name:   FormatInfo
              parent:  
        - name:   Formatter.h
          functions: []
          classes:
            - name:   Formatter
              parent:  
children:
    - name: make_format
      value: ThorsIOUtil.Format.make_format.md
    - name: make_cppformat
      value: ThorsIOUtil.Format.make_cppformat.md
    - name: Format
      value: ThorsIOUtil.Format.Format.md
    - name: FormatInfo
      value: ThorsIOUtil.FormatInfo.FormatInfo.md
    - name: Formatter
      value: ThorsIOUtil.Formatter.Formatter.md
---
