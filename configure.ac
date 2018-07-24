
AC_INIT([ThorsIOUtil], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
if [[ ! -e build/Notes ]]; then
    git submodule init
    git submodule update
fi
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])
AX_THOR_FUNC_BUILD


AC_CONFIG_SRCDIR([src/ThorsIOUtil/format.h])

# Find the C++ Copiler
# The minimumm requirements.
AC_PROG_CXX

AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], [" -ansi"])])
# Check what version of the C++ language is supported
AX_THOR_FUNC_LANG_FLAG(17)

# Find the code coverage tool.
# All the testing will depend on this.
AX_THOR_PROG_COV

# Add support for shared libraries.
LT_INIT


#
# Add your defintions in here.
# Note there are some predefined macros in build/autotools/m4/



# Build all the Makefiles and configuration files.
# Used by ThorMaker
# Note: you can push the config file to sub directories in the AC_CONFIG_HEADERS macro (see example)
# Note: Local Make variables should be placed in Makefile.config.in
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([ src/ThorsIOUtil/ThorsIOUtilConfig.h ])
AC_CONFIG_FILES([Makefile.extra Makefile.config:build/autotools/build/Makefile.config.in:Makefile.config.in])
AC_OUTPUT
