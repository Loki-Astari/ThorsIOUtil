AC_INIT([ThorsIOUtil], [3.0], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])

AX_THOR_FUNC_INIT_BUILD([ThorsIOUtil], [17], [src/ThorsIOUtil/Format.h])

AX_THOR_FEATURE_HEADER_ONLY_VARIANT([THORS_IOUTIL])

AC_COMPILE_IFELSE(
    [AC_LANG_SOURCE([int main(){auto value = 18446744065119617025LL;}])],
    [AC_DEFINE([SUPPORT_SIGNED_INTEGER_LITERAL_THAT_IS_HUGE],1,[Not all platforms support integers this large. So lets do an explicit test])],
    []
)

LT_INIT

AX_THOR_FUNC_TERM_BUILD([IOUTIL], [src/ThorsIOUtil/ThorsIOUtilConfig.h])

AC_OUTPUT
