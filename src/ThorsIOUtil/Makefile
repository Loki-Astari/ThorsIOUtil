THORSANVIL_ROOT             = $(realpath ../../)

TARGET                      = ThorsIOUtil.head Example.app
%/fake.o:					FILE_WARNING_FLAGS	+= -Wno-unknown-pragmas
%/Example.o:				FILE_WARNING_FLAGS	+= -Wno-unknown-pragmas

FILE_WARNING_FLAGS			+= -Wno-unknown-pragmas
VERA						= echo

include $(THORSANVIL_ROOT)/build/tools/Makefile
