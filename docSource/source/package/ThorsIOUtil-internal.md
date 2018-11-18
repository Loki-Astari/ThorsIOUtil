---
layout: package
generate: false
nameSpace:  ThorsAnvil::IOUtil
headers:
    base: ThorsIOUtil
    files:
        - name:   SignConversionOption.h
          functions: []
          classes:
            - name:   SignConversionOption
              parent:  
            - name:   SignConversionOption-Lchar-R
              parent:  
            - name:   SignConversionOption-Lshort-R
              parent:  
            - name:   SignConversionOption-Lint-R
              parent:  
            - name:   SignConversionOption-Llong-R
              parent:  
            - name:   SignConversionOption-Llong-long-R
              parent:  
            - name:   SignConversionOption-Lunsigned-char-R
              parent:  
            - name:   SignConversionOption-Lunsigned-short-R
              parent:  
            - name:   SignConversionOption-Lunsigned-int-R
              parent:  
            - name:   SignConversionOption-Lunsigned-long-R
              parent:  
            - name:   SignConversionOption-Lunsigned-long-long-R
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
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
            - return: void
              name:   printToStream
              param:  [   std::ostream& s,  char const* const& arg,  FormatInfo const& info  ]
          classes:
            - name:   CharIntConverter
              parent:  
            - name:   CharIntConverter-Lchar-R
              parent:  
            - name:   CharIntConverter-Lunsigned-char-R
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
    - name: SignConversionOption
      value: ThorsIOUtil.SignConversionOption.SignConversionOption.md
    - name: SignConversionOption-Lchar-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lchar-R.md
    - name: SignConversionOption-Lshort-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lshort-R.md
    - name: SignConversionOption-Lint-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lint-R.md
    - name: SignConversionOption-Llong-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Llong-R.md
    - name: SignConversionOption-Llong-long-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Llong-long-R.md
    - name: SignConversionOption-Lunsigned-char-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lunsigned-char-R.md
    - name: SignConversionOption-Lunsigned-short-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lunsigned-short-R.md
    - name: SignConversionOption-Lunsigned-int-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lunsigned-int-R.md
    - name: SignConversionOption-Lunsigned-long-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lunsigned-long-R.md
    - name: SignConversionOption-Lunsigned-long-long-R
      value: ThorsIOUtil.SignConversionOption.SignConversionOption-Lunsigned-long-long-R.md
    - name: printIntToStream
      value: ThorsIOUtil.printIntToStream.printIntToStream.md
    - name: printStringToStream
      value: ThorsIOUtil.printStringToStream.printStringToStream.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
    - name: printToStream
      value: ThorsIOUtil.printToStream.printToStream.md
    - name: CharIntConverter
      value: ThorsIOUtil.printToStream.CharIntConverter.md
    - name: CharIntConverter-Lchar-R
      value: ThorsIOUtil.printToStream.CharIntConverter-Lchar-R.md
    - name: CharIntConverter-Lunsigned-char-R
      value: ThorsIOUtil.printToStream.CharIntConverter-Lunsigned-char-R.md
    - name: saveToStream
      value: ThorsIOUtil.saveToStream.saveToStream.md
    - name: saveToStream
      value: ThorsIOUtil.saveToStream.saveToStream.md
---
