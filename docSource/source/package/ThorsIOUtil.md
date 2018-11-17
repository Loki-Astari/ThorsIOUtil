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
        - name:   SignConversionOption.h
          functions: []
          classes:
            - name:   SignConversionOption
              parent: 
            - name:   SignConversionOption_char
              parent: 
            - name:   SignConversionOption_short
              parent: 
            - name:   SignConversionOption_int
              parent: 
            - name:   SignConversionOption_long
              parent: 
            - name:   SignConversionOption_long
              parent: 
            - name:   SignConversionOption_unsigned
              parent: 
            - name:   SignConversionOption_unsigned
              parent: 
            - name:   SignConversionOption_unsigned
              parent: 
            - name:   SignConversionOption_unsigned
              parent: 
            - name:   SignConversionOption_unsigned
              parent: 
        - name:   printIntToStream.h
          functions:
            - return: void
              name:   printIntToStream
              param:  [   std::ostream& s,  T arg,  FormatInfo const& info  ]
          classes: []
        - name:   printStringToStream.h
          functions:
            - return: void
              name:   printStringToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
          classes: []
        - name:   printToStream.h
          functions:
            - return: void
              name:   printToStreamDefault
              param:  [   std::ostream& s,  T const& arg,  FormatInfo const&  ]
            - return: void
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
            - return: void
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
            - return: void
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
          classes:
            - name:   CharIntConverter
              parent: 
            - name:   CharIntConverter_char
              parent: 
            - name:   CharIntConverter_unsigned
              parent: 
        - name:   saveToStream.h
          functions:
            - return: void
              name:   saveToStream
              param:  [   std::ostream&,  Dynamic,  T const& void,  std::ostream& s,  Dynamic pos,  int const& size  ]
            - return: void
              name:   saveToStream
              param:  [   std::ostream&,  Dynamic,  T const& void,  std::ostream& s,  Dynamic pos,  int const& size  ]
          classes: []
children:
    - name: make_format
      value: ThorsIOUtil.Format.make_format.md
    - name: Format
      value: ThorsIOUtil.Format.Format.md
    - name: FormatInfo
      value: ThorsIOUtil.FormatInfo.FormatInfo.md
    - name: Formatter
      value: ThorsIOUtil.Formatter.Formatter.md
    - name: SignConversionOption
      value: ThorsIOUtil.SignConversionOption.SignConversionOption.md
    - name: SignConversionOption_char
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_char.md
    - name: SignConversionOption_short
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_short.md
    - name: SignConversionOption_int
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_int.md
    - name: SignConversionOption_long
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_long.md
    - name: SignConversionOption_long
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_long.md
    - name: SignConversionOption_unsigned
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_unsigned.md
    - name: SignConversionOption_unsigned
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_unsigned.md
    - name: SignConversionOption_unsigned
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_unsigned.md
    - name: SignConversionOption_unsigned
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_unsigned.md
    - name: SignConversionOption_unsigned
      value: ThorsIOUtil.SignConversionOption.SignConversionOption_unsigned.md
    - name: printIntToStream
      value: ThorsIOUtil.printIntToStream.printIntToStream.md
    - name: printStringToStream
      value: ThorsIOUtil.printStringToStream.printStringToStream.md
    - name: printToStreamDefault
      value: ThorsIOUtil.printToStream.printToStreamDefault.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
    - name: CharIntConverter
      value: ThorsIOUtil.printToStream.CharIntConverter.md
    - name: CharIntConverter_char
      value: ThorsIOUtil.printToStream.CharIntConverter_char.md
    - name: CharIntConverter_unsigned
      value: ThorsIOUtil.printToStream.CharIntConverter_unsigned.md
    - name: saveToStream
      value: ThorsIOUtil.saveToStream.saveToStream.md
    - name: saveToStream
      value: ThorsIOUtil.saveToStream.saveToStream.md
---
