THORSANVIL_ROOT             ?= $(realpath ../../)

TARGET                      = ThorsIOUtil.head Example.app
NAMESPACE					= ThorsAnvil::IOUtil

include $(THORSANVIL_ROOT)/build/tools/Makefile

%/FixTest.o:				FILE_WARNING_FLAGS += -Wno-deprecated-declarations
%/FrameTest.o:				FILE_WARNING_FLAGS += -Wno-deprecated-declarations
