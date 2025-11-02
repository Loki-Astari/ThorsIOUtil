AC_INIT([ThorsIOUtil], [3.0], [Loki.Astari+ThorsIOUtil@gmail.com])
AC_PREREQ([2.65])

AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])

AX_THOR_FUNC_INIT_BUILD([ThorsIOUtil], [src/ThorsIOUtil/Format.h], [20])

AX_THOR_FEATURE_HEADER_ONLY_VARIANT([THORS_IOUTIL])
AX_THOR_CHECK_USE_THORS_SERIALIZE([ThorsLogging])

AC_COMPILE_IFELSE(
    [AC_LANG_SOURCE([int main(){auto value = 18446744065119617025LL;}])],
    [AC_DEFINE([SUPPORT_SIGNED_INTEGER_LITERAL_THAT_IS_HUGE],1,[Not all platforms support integers this large. So lets do an explicit test])],
    []
)

LT_INIT

AX_THOR_FUNC_TERM_BUILD([IOUTIL], [src/ThorsIOUtil/ThorsIOUtilConfig.h:config.h.in])

AC_OUTPUT
