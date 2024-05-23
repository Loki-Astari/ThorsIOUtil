THORSANVIL_ROOT             ?= $(realpath ../../)
COVERAGE_REQUIRED			= 20

TARGET                      = ThorsIOUtil.head Example.prog
NAMESPACE					= ThorsAnvil::IOUtil

include $(THORSANVIL_ROOT)/build/tools/Makefile

%/FixTest.o:				FILE_WARNING_FLAGS += -Wno-deprecated-declarations
%/FrameTest.o:				FILE_WARNING_FLAGS += -Wno-deprecated-declarations
