THORSANVIL_ROOT             = $(realpath ../../)

TARGET                      = ThorsIOUtil.head Example.app
%/fake.o:					FILE_WARNING_FLAGS	+= -Wno-unknown-pragmas
%/Example.o:				FILE_WARNING_FLAGS	+= -Wno-unknown-pragmas

FILE_WARNING_FLAGS			+= -Wno-unknown-pragmas
UNITTEST_CXXFLAGS			+= -Wno-deprecated-declarations
VERA_PROFILE_FormatInfo.h	= ThorsIOUtil_Format
VERA_PROFILE_Formatter.h	= ThorsIOUtil_Format

include $(THORSANVIL_ROOT)/build/tools/Makefile
