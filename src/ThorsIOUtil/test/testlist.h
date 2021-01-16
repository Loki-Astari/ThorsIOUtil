#if 0
# Note: This file is a modified version of "Bart" orginal file from the project:
#       https://github.com/BartMassey/printf-tests
#       The reference to COPYING/README see the above project.
#
# Various printf tests compiled from various sources
# Copyright © 2013 Bart Massey
# This program is licensed under the GPL version 2 or later.
# Please see the file COPYING in this distribution for
# license terms.

# Please see the README in this distribution for a detailed
# description of this file.

# Regression tests from GHC
#endif
#define THOR_PRINTF_TEST_GROUP  GHC
THOR_PRINTF_TEST(1, "0.33",                  "%.*f",          2, 0.33333333)
THOR_PRINTF_TEST(2, "foo",                   "%.3s",          "foobar")
THOR_PRINTF_TEST(3, "     00004",            "%10.5d",        4)

#if 0
# Tests from NPM
#endif
#undef  THOR_PRINTF_TEST_GROUP
#define THOR_PRINTF_TEST_GROUP  NPM
THOR_PRINTF_TEST(4, " 42",                   "% d",           42)
THOR_PRINTF_TEST(5, "-42",                   "% d",           -42)
THOR_PRINTF_TEST(6, "   42",                 "% 5d",          42)
THOR_PRINTF_TEST(7, "  -42",                 "% 5d",          -42)
THOR_PRINTF_TEST(8, "             42",       "% 15d",         42)
THOR_PRINTF_TEST(9, "            -42",       "% 15d",         -42)

THOR_PRINTF_TEST(10, "+42",                   "%+d",           42)
THOR_PRINTF_TEST(11, "-42",                   "%+d",           -42)
THOR_PRINTF_TEST(12, "  +42",                 "%+5d",          42)
THOR_PRINTF_TEST(13, "  -42",                 "%+5d",          -42)
THOR_PRINTF_TEST(14, "            +42",       "%+15d",         42)
THOR_PRINTF_TEST(15, "            -42",       "%+15d",         -42)

THOR_PRINTF_TEST(16, "42",                    "%0d",           42)
THOR_PRINTF_TEST(17, "-42",                   "%0d",           -42)
THOR_PRINTF_TEST(18, "00042",                 "%05d",          42)
THOR_PRINTF_TEST(19, "-0042",                 "%05d",          -42)
THOR_PRINTF_TEST(20, "000000000000042",       "%015d",         42)
THOR_PRINTF_TEST(21, "-00000000000042",       "%015d",         -42)

THOR_PRINTF_TEST(22, "42",                    "%-d",           42)
THOR_PRINTF_TEST(23, "-42",                   "%-d",           -42)
THOR_PRINTF_TEST(24, "42   ",                 "%-5d",          42)
THOR_PRINTF_TEST(25, "-42  ",                 "%-5d",          -42)
THOR_PRINTF_TEST(26, "42             ",       "%-15d",         42)
THOR_PRINTF_TEST(27, "-42            ",       "%-15d",         -42)
THOR_PRINTF_TEST(28, "42",                    "%-0d",          42)
THOR_PRINTF_TEST(29, "-42",                   "%-0d",          -42)
THOR_PRINTF_TEST(30, "42   ",                 "%-05d",         42)
THOR_PRINTF_TEST(31, "-42  ",                 "%-05d",         -42)
THOR_PRINTF_TEST(32, "42             ",       "%-015d",        42)
THOR_PRINTF_TEST(33, "-42            ",       "%-015d",        -42)
THOR_PRINTF_TEST(34, "42",                    "%0-d",          42)
THOR_PRINTF_TEST(35, "-42",                   "%0-d",          -42)
THOR_PRINTF_TEST(36, "42   ",                 "%0-5d",         42)
THOR_PRINTF_TEST(37, "-42  ",                 "%0-5d",         -42)
THOR_PRINTF_TEST(38, "42             ",       "%0-15d",        42)
THOR_PRINTF_TEST(39, "-42            ",       "%0-15d",        -42)

#if 0
# These tests are undefined.
# 40 "42"                    "%d"            42.8952
# 41 "42"                    "%.2d"          42.8952
# 42 "42"                    "%.2i"          42.8952
#endif
THOR_PRINTF_TEST(43, "42.90",                 "%.2f",          42.8952)
THOR_PRINTF_TEST(44, "42.90",                 "%.2F",          42.8952)
THOR_PRINTF_TEST(45, "42.8952000000",         "%.10f",         42.8952)
THOR_PRINTF_TEST(46, "42.90",                 "%1.2f",         42.8952)
THOR_PRINTF_TEST(47, " 42.90",                "%6.2f",         42.8952)
#if 0
# Technically, this test is undefined according to the
# doc. If a precision is given with a numeric
# conversion (d,, i, o, u, x, and X), the 0 flag is ignored.
# For other conversions, the behavior is undefined.
#endif
THOR_PRINTF_TEST(48, "042.90",                "%06.2f",        42.8952)

THOR_PRINTF_TEST(49, "+42.90",                "%+6.2f",        42.8952)
THOR_PRINTF_TEST(50, "42.8952000000",         "%5.10f",        42.8952)
#if 0
    51 ?                       "%c"            -100
    52 ?                       "%c"            2097152

# glibc printf fails this test, returning "%"
# haskell printf fails these tests, since no indexed arguments
!CH 53 "%1$"                   "%1$"
# This test is not obviously defined.
# 54 "%0$s"                  "%0$s"
!H 55 "Hot Pocket"            "%1$s %2$s"     "Hot" "Pocket"
!H 56 "12.0 Hot Pockets"      "%1$.1f %2$s %3$ss" 12.0 "Hot" "Pocket"
# glibc printf fails this test, returning "42"
# However, the printf(3), spec does not allow mixing positional and
# indexed args like this, so it is really not a valid test.
# 57 " 42"                   "%1$*.f"        3 42.0

!H 58 ?                       "%2$*s"         "Hot Pocket"
# haskell correctly reports an error
#endif
THOR_PRINTF_FAIL(59, "%(foo",                 "%(foo")

THOR_PRINTF_TEST(60, " foo",                  "%*s",           4, "foo")
THOR_PRINTF_TEST(61, "      3.14",            "%*.*f",         10, 2, 3.14159265)
#if 0
# This test is undefined. See test 48 above.
# 62 "0000003.14"            "%0*.*f"        10 2 3.14159265
#endif
THOR_PRINTF_TEST(63, "3.14      ",            "%-*.*f",        10, 2, 3.14159265)
THOR_PRINTF_FAIL(64, ?,                       "%*s",           "foo", "bar")
THOR_PRINTF_FAIL(65, ?,                       "%10.*f",        42, "foo")

THOR_PRINTF_TEST(66, "+hello+",               "+%s+",          "hello")
THOR_PRINTF_TEST(67, "+10+",                  "+%d+",          10)
THOR_PRINTF_TEST(68, "a",                     "%c",            'a')
THOR_PRINTF_TEST(69, " ",                     "%c",            32)
THOR_PRINTF_TEST(70, "$",                     "%c",            36)
THOR_PRINTF_TEST(71, "10",                    "%d",            10)
THOR_PRINTF_FAIL(72, ?,                       "%s%s",          42)
THOR_PRINTF_FAIL(73, ?,                       "%c")
#if 0
# glibc printf fails this test, returns ""
# Haskell fails this test claiming that argument list ended
# prematurely, which is not so reasonable.
!CH 74 "%10"                   "%10"           42
# glibc printf fails this test, returns "10 "
# Haskell correctly throws an error
#endif
THOR_PRINTF_FAIL(75, "10 %",                  "%d %",          10)

#if 0
# Tests from MSVCRT
# Haskell fails these tests due to different floating formatting
#endif
#undef  THOR_PRINTF_TEST_GROUP
#define THOR_PRINTF_TEST_GROUP  MSVCRT
THOR_PRINTF_TEST(76, "+7.894561230000000e+08",        "%+#22.15e",     789456123.0)
THOR_PRINTF_TEST(77, "7.894561230000000e+08 ",        "%-#22.15e",     789456123.0)
THOR_PRINTF_TEST(78, " 7.894561230000000e+08",        "%#22.15e",      789456123.0)
THOR_PRINTF_TEST(79, "8.e+08",                        "%#1.1g",        789456123.0)

#if 0
# The arg constant here is not legal C.
#endif
#if defined(SUPPORT_SIGNED_INTEGER_LITERAL_THAT_IS_HUGE)
THOR_PRINTF_TEST(80, "-8589934591",                   "%lld",         18446744065119617025LL)
#endif
THOR_PRINTF_TEST(81, "    +100",                      "%+8lld",       100LL)
THOR_PRINTF_TEST(82, "+00000100",                     "%+.8lld",      100LL)
THOR_PRINTF_TEST(83, " +00000100",                    "%+10.8lld",    100LL)
#if 0
# Haskell correctly reports an error here
#endif
THOR_PRINTF_FAIL(84, "%_1lld",                        "%_1lld",       100LL)
THOR_PRINTF_TEST(85, "-00100",                        "%-1.5lld",     -100LL)
THOR_PRINTF_TEST(86, "  100",                         "%5lld",        100LL)
THOR_PRINTF_TEST(87, " -100",                         "%5lld",        -100LL)
THOR_PRINTF_TEST(88, "100  ",                         "%-5lld",       100LL)
THOR_PRINTF_TEST(89, "-100 ",                         "%-5lld",       -100LL)
THOR_PRINTF_TEST(90, "00100",                         "%-.5lld",      100LL)
THOR_PRINTF_TEST(91, "-00100",                        "%-.5lld",      -100LL)
THOR_PRINTF_TEST(92, "00100   ",                      "%-8.5lld",     100LL)
THOR_PRINTF_TEST(93, "-00100  ",                      "%-8.5lld",     -100LL)
THOR_PRINTF_TEST(94, "00100",                         "%05lld",       100LL)
THOR_PRINTF_TEST(95, "-0100",                         "%05lld",       -100LL)
THOR_PRINTF_TEST(96, " 100",                          "% lld",        100LL)
THOR_PRINTF_TEST(97, "-100",                          "% lld",        -100LL)
THOR_PRINTF_TEST(98, "  100",                         "% 5lld",       100LL)
THOR_PRINTF_TEST(99, " -100",                         "% 5lld",       -100LL)
THOR_PRINTF_TEST(100, " 00100",                        "% .5lld",      100LL)
THOR_PRINTF_TEST(101, "-00100",                        "% .5lld",      -100LL)
THOR_PRINTF_TEST(102, "   00100",                      "% 8.5lld",     100LL)
THOR_PRINTF_TEST(103, "  -00100",                      "% 8.5lld",     -100LL)
THOR_PRINTF_TEST(104, "",                              "%.0lld",       0LL)
// C++ exception with description "Actual argument does not match supplied argument: Expected(unsigned long long) Got(long long)" thrown in the test body.
#if 0
This is not working on homebrew 11-arm
THOR_PRINTF_TEST(105, " 0x00ffffffffffffff9c",         "%#+21.18llx",  -100LL)
#endif
THOR_PRINTF_TEST(106, "0001777777777777777777634",     "%#.25llo",     -100LL)
THOR_PRINTF_TEST(107, " 01777777777777777777634",      "%#+24.20llo",  -100LL)
#if 0
This is not working on homebrew 11-arm
THOR_PRINTF_TEST(108, "0X00000FFFFFFFFFFFFFF9C",       "%#+18.21llX",  -100LL)
#endif
THOR_PRINTF_TEST(109, "001777777777777777777634",      "%#+20.24llo",  -100LL)
THOR_PRINTF_TEST(110, "   0018446744073709551615",     "%#+25.22llu",  -1LL)
THOR_PRINTF_TEST(111, "   0018446744073709551615",     "%#+25.22llu",  -1LL)
THOR_PRINTF_TEST(112, "     0000018446744073709551615", "%#+30.25llu", -1LL)
THOR_PRINTF_TEST(113, "  -0000000000000000000001",     "%+#25.22lld",  -1LL)
THOR_PRINTF_TEST(114, "00144   ",                      "%#-8.5llo",    100LL)
THOR_PRINTF_TEST(115, "+00100  ",                      "%#-+ 08.5lld", 100LL)
THOR_PRINTF_TEST(116, "+00100  ",                      "%#-+ 08.5lld", 100LL)
THOR_PRINTF_TEST(117, "0000000000000000000000000000000000000001", "%.40lld", 1LL)
THOR_PRINTF_TEST(118, " 0000000000000000000000000000000000000001", "% .40lld", 1LL)
THOR_PRINTF_TEST(119, " 0000000000000000000000000000000000000001", "% .40d", 1)
#if 0
#See above.
#endif
#if defined(SUPPORT_SIGNED_INTEGER_LITERAL_THAT_IS_HUGE)
THOR_PRINTF_TEST(120, "-8589934591",                   "%lld",          18446744065119617025LL)
#endif
#if 0
# libc fails this, with "" and return code -1 (!)
#, Haskell correctly reports an error here
#endif
THOR_PRINTF_FAIL(121, "%I",                            "%I",            1)
#if 0
# The next two tests are locale-specific and should not be used
#122 "1"                             "%I0d"          1
#123 "                               1" "%I32d"         1
# libc fails this, with "%D"
# Haskell correctly throws an error
#endif
THOR_PRINTF_FAIL(124, "%llD",                          "%llD",          -1LL)
THOR_PRINTF_TEST(125, " 1",                            "% d",           1)
THOR_PRINTF_TEST(126, "+1",                            "%+ d",          1)
#if 0
# These tests are undefined.
#127 "0001"                          "%04c"          '1'
#128 "1   "                          "%-04c"         '1'
#endif
THOR_PRINTF_TEST(129, "0x0000000001",                  "%#012x",        1)
THOR_PRINTF_TEST(130, "0x00000001",                    "%#04.8x",       1)
THOR_PRINTF_TEST(131, "0x01    ",                      "%#-08.2x",      1)
THOR_PRINTF_TEST(132, "00000001",                      "%#08o",         1)
#if 0
# Haskell has no pointers
#133 "0x39"                          "%p"            57VLL
# These tests are undefined.
#134 "  0X0000000000000039"          "%#020p"        57VLL
#135 "0000000000000039"              "%Fp"           57VLL
#136 "0X0000000000000039  "          "%#-020p"       57VLL
# Haskell has no pointers
!H 137 "0x39"                          "%p"            57V
# These tests are undefined.
#138 "  0X00000039"                  "%#012p"        57V
#139 "00000039"                      "%Fp"           57V
#140 "0X00000039  "                  "%#-012p"       57V
#endif
THOR_PRINTF_TEST(141, "0foo",                          "%04s",          "foo")
THOR_PRINTF_TEST(142, "f",                             "%.1s",          "foo")
THOR_PRINTF_TEST(143, "f",                             "%.*s",          1, "foo")
THOR_PRINTF_TEST(144, "foo  ",                         "%*s",           -5, "foo")
THOR_PRINTF_TEST(145, "hello",                         "hello")
#if 0
# This test is undefined.
#146 "not wide"                      "%Ls"           "not wide"
# Haskell correctly throws an error
#endif
THOR_PRINTF_FAIL(147, "%b",                            "%b")
THOR_PRINTF_TEST(148, "  a",                           "%3c",           'a')
THOR_PRINTF_TEST(149, "1234",                          "%3d",           1234)
#if 0
# libc fails this, with "" and return code -1
# Haskell correctly throws an error
#endif
THOR_PRINTF_FAIL(150, "%3h",                           "%3h")
#if 0
# libc fails this, with a big mess worth sorting out later.
# Note that the given result is clearly wrong.
#endif
THOR_PRINTF_FAIL(151, "jkmqrtvyz",                     "%j%k%m%q%r%t%v%y%z")
THOR_PRINTF_TEST(152, "2",                             "%-1d",          2)
THOR_PRINTF_TEST(153, "8.6000",                        "%2.4f",         8.6)
#if 0
# Haskell fails these because of different floating point formatting
#endif
THOR_PRINTF_TEST(154, "0.600000",                      "%0f",           0.6)
THOR_PRINTF_TEST(155, "1",                             "%.0f",          0.6)
THOR_PRINTF_TEST(156, "8.6000e+00",                    "%2.4e",         8.6)
THOR_PRINTF_TEST(157, " 8.6000e+00",                   "% 2.4e",        8.6)
#if 0
# This test is undefined, due to a weird codicil in the
# manpage re zero flag plus precision for non-integral formats.
# 158 " 0008.6000e+00"                 "% 014.4e"      8.6
#endif
THOR_PRINTF_TEST(159, "-8.6000e+00",                   "% 2.4e",        -8.6)
THOR_PRINTF_TEST(160, "+8.6000e+00",                   "%+2.4e",        8.6)
THOR_PRINTF_TEST(161, "8.6",                           "%2.4g",         8.6)
THOR_PRINTF_TEST(162, "-1",                            "%-i",           -1)
THOR_PRINTF_TEST(163, "1",                             "%-i",           1)
THOR_PRINTF_TEST(164, "+1",                            "%+i",           1)
THOR_PRINTF_TEST(165, "12",                            "%o",            10)
#if 0
# libc fails these, returning "(nil)",, which is not
# allowed by the spec. Haskell has no pointer type.
!CH 166 "0x0"                           "%p"            0VLL
!CH 167 "0x0"                           "%p"            0V
# This test is undefined.
#168 "(null)",                        "%s"            0
#endif
THOR_PRINTF_TEST(169, "%%%%",                          "%s",            "%%%%")
THOR_PRINTF_TEST(170, "4294967295",                    "%u",            -1)
#if 0
# Haskell correctly throws an error on these
#endif
THOR_PRINTF_FAIL(171, "%w",                            "%w",            -1)
#if 0
# libc fails these, with "" and return -1
#endif
THOR_PRINTF_FAIL(172, "%h",                            "%h",            -1)
THOR_PRINTF_FAIL(173, "%z",                            "%z",            -1)
THOR_PRINTF_FAIL(174, "%j",                            "%j",            -1)
#if 0
# This test is undefined.
#175 ""                              "%F"            -1
# Haskell correctly throws an error on this.
#endif
THOR_PRINTF_FAIL(176, "%H",                            "%H",            -1)
THOR_PRINTF_TEST(177, "%0",                            "%%0")
#if 0
# Haskell returns "12345"; this is arguably correct for Haskell.
#endif
THOR_PRINTF_TEST(178, "2345",                          "%hx",           74565)
THOR_PRINTF_TEST(179, "61",                            "%hhx",          'a')
#if 0
# This test seems hopeless: I dont understand it.
# 180 "2345"                          "%hhx"          74565

# Tests from libc
#endif
#undef  THOR_PRINTF_TEST_GROUP
#define THOR_PRINTF_TEST_GROUP libc
THOR_PRINTF_TEST(181, "Hallo heimur",          "Hallo heimur")
THOR_PRINTF_TEST(182, "Hallo heimur",          "%s",            "Hallo heimur")
THOR_PRINTF_TEST(183, "1024",                  "%d",            1024)
THOR_PRINTF_TEST(184, "-1024",                 "%d",            -1024)
THOR_PRINTF_TEST(185, "1024",                  "%i",            1024)
THOR_PRINTF_TEST(186, "-1024",                 "%i",            -1024)
THOR_PRINTF_TEST(187, "1024",                  "%u",            1024)
THOR_PRINTF_TEST(188, "4294966272",            "%u",            4294966272U)
THOR_PRINTF_TEST(189, "777",                   "%o",            511)
THOR_PRINTF_TEST(190, "37777777001",           "%o",            4294966785U)
THOR_PRINTF_TEST(191, "1234abcd",              "%x",            305441741)
THOR_PRINTF_TEST(192, "edcb5433",              "%x",            3989525555U)
THOR_PRINTF_TEST(193, "1234ABCD",              "%X",            305441741)
THOR_PRINTF_TEST(194, "EDCB5433",              "%X",            3989525555U)
THOR_PRINTF_TEST(195, "x",                     "%c",            'x')
THOR_PRINTF_TEST(196, "%",                     "%%")

THOR_PRINTF_TEST(197, "Hallo heimur",          "%+s",           "Hallo heimur")
THOR_PRINTF_TEST(198, "+1024",                 "%+d",           1024)
THOR_PRINTF_TEST(199, "-1024",                 "%+d",           -1024)
THOR_PRINTF_TEST(200, "+1024",                 "%+i",           1024)
THOR_PRINTF_TEST(201, "-1024",                 "%+i",           -1024)
THOR_PRINTF_TEST(202, "1024",                  "%+u",           1024)
THOR_PRINTF_TEST(203, "4294966272",            "%+u",           4294966272U)
THOR_PRINTF_TEST(204, "777",                   "%+o",           511)
THOR_PRINTF_TEST(205, "37777777001",           "%+o",           4294966785U)
THOR_PRINTF_TEST(206, "1234abcd",              "%+x",           305441741)
THOR_PRINTF_TEST(207, "edcb5433",              "%+x",           3989525555U)
THOR_PRINTF_TEST(208, "1234ABCD",              "%+X",           305441741)
THOR_PRINTF_TEST(209, "EDCB5433",              "%+X",           3989525555U)
THOR_PRINTF_TEST(210, "x",                     "%+c",           'x')

THOR_PRINTF_TEST(211, "Hallo heimur",          "% s",           "Hallo heimur")
THOR_PRINTF_TEST(212, " 1024",                 "% d",           1024)
THOR_PRINTF_TEST(213, "-1024",                 "% d",           -1024)
THOR_PRINTF_TEST(214, " 1024",                 "% i",           1024)
THOR_PRINTF_TEST(215, "-1024",                 "% i",           -1024)
THOR_PRINTF_TEST(216, "1024",                  "% u",           1024)
THOR_PRINTF_TEST(217, "4294966272",            "% u",           4294966272U)
THOR_PRINTF_TEST(218, "777",                   "% o",           511)
THOR_PRINTF_TEST(219, "37777777001",           "% o",           4294966785U)
THOR_PRINTF_TEST(220, "1234abcd",              "% x",           305441741)
THOR_PRINTF_TEST(221, "edcb5433",              "% x",           3989525555U)
THOR_PRINTF_TEST(222, "1234ABCD",              "% X",           305441741)
THOR_PRINTF_TEST(223, "EDCB5433",              "% X",           3989525555U)
THOR_PRINTF_TEST(224, "x",                     "% c",           'x')

THOR_PRINTF_TEST(225, "Hallo heimur",          "%+ s",          "Hallo heimur")
THOR_PRINTF_TEST(226, "+1024",                 "%+ d",          1024)
THOR_PRINTF_TEST(227, "-1024",                 "%+ d",          -1024)
THOR_PRINTF_TEST(228, "+1024",                 "%+ i",          1024)
THOR_PRINTF_TEST(229, "-1024",                 "%+ i",          -1024)
THOR_PRINTF_TEST(230, "1024",                  "%+ u",          1024)
THOR_PRINTF_TEST(231, "4294966272",            "%+ u",          4294966272U)
THOR_PRINTF_TEST(232, "777",                   "%+ o",          511)
THOR_PRINTF_TEST(233, "37777777001",           "%+ o",          4294966785U)
THOR_PRINTF_TEST(234, "1234abcd",              "%+ x",          305441741)
THOR_PRINTF_TEST(235, "edcb5433",              "%+ x",          3989525555U)
THOR_PRINTF_TEST(236, "1234ABCD",              "%+ X",          305441741)
THOR_PRINTF_TEST(237, "EDCB5433",              "%+ X",          3989525555U)
THOR_PRINTF_TEST(238, "x",                     "%+ c",          'x')

THOR_PRINTF_TEST(239, "0777",                  "%#o",           511)
THOR_PRINTF_TEST(240, "037777777001",          "%#o",           4294966785U)
THOR_PRINTF_TEST(241, "0x1234abcd",            "%#x",           305441741)
THOR_PRINTF_TEST(242, "0xedcb5433",            "%#x",           3989525555U)
THOR_PRINTF_TEST(243, "0X1234ABCD",            "%#X",           305441741)
THOR_PRINTF_TEST(244, "0XEDCB5433",            "%#X",           3989525555U)
THOR_PRINTF_TEST(245, "0",                     "%#o",           0U)
THOR_PRINTF_TEST(246, "0",                     "%#x",           0U)
THOR_PRINTF_TEST(247, "0",                     "%#X",           0U)

THOR_PRINTF_TEST(248, "Hallo heimur",          "%1s",           "Hallo heimur")
THOR_PRINTF_TEST(249, "1024",                  "%1d",           1024)
THOR_PRINTF_TEST(250, "-1024",                 "%1d",           -1024)
THOR_PRINTF_TEST(251, "1024",                  "%1i",           1024)
THOR_PRINTF_TEST(252, "-1024",                 "%1i",           -1024)
THOR_PRINTF_TEST(253, "1024",                  "%1u",           1024)
THOR_PRINTF_TEST(254, "4294966272",            "%1u",           4294966272U)
THOR_PRINTF_TEST(255, "777",                   "%1o",           511)
THOR_PRINTF_TEST(256, "37777777001",           "%1o",           4294966785U)
THOR_PRINTF_TEST(257, "1234abcd",              "%1x",           305441741)
THOR_PRINTF_TEST(258, "edcb5433",              "%1x",           3989525555U)
THOR_PRINTF_TEST(259, "1234ABCD",              "%1X",           305441741)
THOR_PRINTF_TEST(260, "EDCB5433",              "%1X",           3989525555U)
THOR_PRINTF_TEST(261, "x",                     "%1c",           'x')

THOR_PRINTF_TEST(262, "               Hallo",  "%20s",          "Hallo")
THOR_PRINTF_TEST(263, "                1024",  "%20d",          1024)
THOR_PRINTF_TEST(264, "               -1024",  "%20d",          -1024)
THOR_PRINTF_TEST(265, "                1024",  "%20i",          1024)
THOR_PRINTF_TEST(266, "               -1024",  "%20i",          -1024)
THOR_PRINTF_TEST(267, "                1024",  "%20u",          1024)
THOR_PRINTF_TEST(268, "          4294966272",  "%20u",          4294966272U)
THOR_PRINTF_TEST(269, "                 777",  "%20o",          511)
THOR_PRINTF_TEST(270, "         37777777001",  "%20o",          4294966785U)
THOR_PRINTF_TEST(271, "            1234abcd",  "%20x",          305441741)
THOR_PRINTF_TEST(272, "            edcb5433",  "%20x",          3989525555U)
THOR_PRINTF_TEST(273, "            1234ABCD",  "%20X",          305441741)
THOR_PRINTF_TEST(274, "            EDCB5433",  "%20X",          3989525555U)
THOR_PRINTF_TEST(275, "                   x",  "%20c",          'x')

THOR_PRINTF_TEST(276, "Hallo               ",  "%-20s",         "Hallo")
THOR_PRINTF_TEST(277, "1024                ",  "%-20d",         1024)
THOR_PRINTF_TEST(278, "-1024               ",  "%-20d",         -1024)
THOR_PRINTF_TEST(279, "1024                ",  "%-20i",         1024)
THOR_PRINTF_TEST(280, "-1024               ",  "%-20i",         -1024)
THOR_PRINTF_TEST(281, "1024                ",  "%-20u",         1024)
THOR_PRINTF_TEST(282, "4294966272          ",  "%-20u",         4294966272U)
THOR_PRINTF_TEST(283, "777                 ",  "%-20o",         511)
THOR_PRINTF_TEST(284, "37777777001         ",  "%-20o",         4294966785U)
THOR_PRINTF_TEST(285, "1234abcd            ",  "%-20x",         305441741)
THOR_PRINTF_TEST(286, "edcb5433            ",  "%-20x",         3989525555U)
THOR_PRINTF_TEST(287, "1234ABCD            ",  "%-20X",         305441741)
THOR_PRINTF_TEST(288, "EDCB5433            ",  "%-20X",         3989525555U)
THOR_PRINTF_TEST(289, "x                   ",  "%-20c",         'x')

THOR_PRINTF_TEST(290, "00000000000000001024",  "%020d",         1024)
THOR_PRINTF_TEST(291, "-0000000000000001024",  "%020d",         -1024)
THOR_PRINTF_TEST(292, "00000000000000001024",  "%020i",         1024)
THOR_PRINTF_TEST(293, "-0000000000000001024",  "%020i",         -1024)
THOR_PRINTF_TEST(294, "00000000000000001024",  "%020u",         1024)
THOR_PRINTF_TEST(295, "00000000004294966272",  "%020u",         4294966272U)
THOR_PRINTF_TEST(296, "00000000000000000777",  "%020o",         511)
THOR_PRINTF_TEST(297, "00000000037777777001",  "%020o",         4294966785U)
THOR_PRINTF_TEST(298, "0000000000001234abcd",  "%020x",         305441741)
THOR_PRINTF_TEST(299, "000000000000edcb5433",  "%020x",         3989525555U)
THOR_PRINTF_TEST(300, "0000000000001234ABCD",  "%020X",         305441741)
THOR_PRINTF_TEST(301, "000000000000EDCB5433",  "%020X",         3989525555U)

THOR_PRINTF_TEST(302, "                0777",  "%#20o",         511)
THOR_PRINTF_TEST(303, "        037777777001",  "%#20o",         4294966785U)
THOR_PRINTF_TEST(304, "          0x1234abcd",  "%#20x",         305441741)
THOR_PRINTF_TEST(305, "          0xedcb5433",  "%#20x",         3989525555U)
THOR_PRINTF_TEST(306, "          0X1234ABCD",  "%#20X",         305441741)
THOR_PRINTF_TEST(307, "          0XEDCB5433",  "%#20X",         3989525555U)

THOR_PRINTF_TEST(308, "00000000000000000777",  "%#020o",        511)
THOR_PRINTF_TEST(309, "00000000037777777001",  "%#020o",        4294966785U)
THOR_PRINTF_TEST(310, "0x00000000001234abcd",  "%#020x",        305441741)
THOR_PRINTF_TEST(311, "0x0000000000edcb5433",  "%#020x",        3989525555U)
THOR_PRINTF_TEST(312, "0X00000000001234ABCD",  "%#020X",        305441741)
THOR_PRINTF_TEST(313, "0X0000000000EDCB5433",  "%#020X",        3989525555U)

THOR_PRINTF_TEST(314, "Hallo               ",  "%0-20s",        "Hallo")
THOR_PRINTF_TEST(315, "1024                ",  "%0-20d",        1024)
THOR_PRINTF_TEST(316, "-1024               ",  "%0-20d",        -1024)
THOR_PRINTF_TEST(317, "1024                ",  "%0-20i",        1024)
THOR_PRINTF_TEST(318, "-1024               ",  "%0-20i",        -1024)
THOR_PRINTF_TEST(319, "1024                ",  "%0-20u",        1024)
THOR_PRINTF_TEST(320, "4294966272          ",  "%0-20u",        4294966272U)
THOR_PRINTF_TEST(321, "777                 ",  "%-020o",        511)
THOR_PRINTF_TEST(322, "37777777001         ",  "%-020o",        4294966785U)
THOR_PRINTF_TEST(323, "1234abcd            ",  "%-020x",        305441741)
THOR_PRINTF_TEST(324, "edcb5433            ",  "%-020x",        3989525555U)
THOR_PRINTF_TEST(325, "1234ABCD            ",  "%-020X",        305441741)
THOR_PRINTF_TEST(326, "EDCB5433            ",  "%-020X",        3989525555U)
THOR_PRINTF_TEST(327, "x                   ",  "%-020c",        'x')

THOR_PRINTF_TEST(328, "               Hallo",  "%*s",           20, "Hallo")
THOR_PRINTF_TEST(329, "                1024",  "%*d",           20, 1024)
THOR_PRINTF_TEST(330, "               -1024",  "%*d",           20, -1024)
THOR_PRINTF_TEST(331, "                1024",  "%*i",           20, 1024)
THOR_PRINTF_TEST(332, "               -1024",  "%*i",           20, -1024)
THOR_PRINTF_TEST(333, "                1024",  "%*u",           20, 1024)
THOR_PRINTF_TEST(334, "          4294966272",  "%*u",           20, 4294966272U)
THOR_PRINTF_TEST(335, "                 777",  "%*o",           20, 511)
THOR_PRINTF_TEST(336, "         37777777001",  "%*o",           20, 4294966785U)
THOR_PRINTF_TEST(337, "            1234abcd",  "%*x",           20, 305441741)
THOR_PRINTF_TEST(338, "            edcb5433",  "%*x",           20, 3989525555U)
THOR_PRINTF_TEST(339, "            1234ABCD",  "%*X",           20, 305441741)
THOR_PRINTF_TEST(340, "            EDCB5433",  "%*X",           20, 3989525555U)
THOR_PRINTF_TEST(341, "                   x",  "%*c",           20, 'x')

THOR_PRINTF_TEST(342, "Hallo heimur",          "%.20s",         "Hallo heimur")
THOR_PRINTF_TEST(343, "00000000000000001024",  "%.20d",         1024)
THOR_PRINTF_TEST(344, "-00000000000000001024", "%.20d",         -1024)
THOR_PRINTF_TEST(345, "00000000000000001024",  "%.20i",         1024)
THOR_PRINTF_TEST(346, "-00000000000000001024", "%.20i",         -1024)
THOR_PRINTF_TEST(347, "00000000000000001024",  "%.20u",         1024)
THOR_PRINTF_TEST(348, "00000000004294966272",  "%.20u",         4294966272U)
THOR_PRINTF_TEST(349, "00000000000000000777",  "%.20o",         511)
THOR_PRINTF_TEST(350, "00000000037777777001",  "%.20o",         4294966785U)
THOR_PRINTF_TEST(351, "0000000000001234abcd",  "%.20x",         305441741)
THOR_PRINTF_TEST(352, "000000000000edcb5433",  "%.20x",         3989525555U)
THOR_PRINTF_TEST(353, "0000000000001234ABCD",  "%.20X",         305441741)
THOR_PRINTF_TEST(354, "000000000000EDCB5433",  "%.20X",         3989525555U)

THOR_PRINTF_TEST(355, "               Hallo",  "%20.5s",        "Hallo heimur")
THOR_PRINTF_TEST(356, "               01024",  "%20.5d",        1024)
THOR_PRINTF_TEST(357, "              -01024",  "%20.5d",        -1024)
THOR_PRINTF_TEST(358, "               01024",  "%20.5i",        1024)
THOR_PRINTF_TEST(359, "              -01024",  "%20.5i",        -1024)
THOR_PRINTF_TEST(360, "               01024",  "%20.5u",        1024)
THOR_PRINTF_TEST(361, "          4294966272",  "%20.5u",        4294966272U)
THOR_PRINTF_TEST(362, "               00777",  "%20.5o",        511)
THOR_PRINTF_TEST(363, "         37777777001",  "%20.5o",        4294966785U)
THOR_PRINTF_TEST(364, "            1234abcd",  "%20.5x",        305441741)
THOR_PRINTF_TEST(365, "          00edcb5433",  "%20.10x",       3989525555U)
THOR_PRINTF_TEST(366, "            1234ABCD",  "%20.5X",        305441741)
THOR_PRINTF_TEST(367, "          00EDCB5433",  "%20.10X",       3989525555U)

#if 0
# This test is undefined. Common sense says libc fails it.
#368 "               Hallo"  "%020.5s"       "Hallo heimur"
#endif
THOR_PRINTF_TEST(369, "               01024",  "%020.5d",       1024)
THOR_PRINTF_TEST(370, "              -01024",  "%020.5d",       -1024)
THOR_PRINTF_TEST(371, "               01024",  "%020.5i",       1024)
THOR_PRINTF_TEST(372, "              -01024",  "%020.5i",       -1024)
THOR_PRINTF_TEST(373, "               01024",  "%020.5u",       1024)
THOR_PRINTF_TEST(374, "          4294966272",  "%020.5u",       4294966272U)
THOR_PRINTF_TEST(375, "               00777",  "%020.5o",       511)
THOR_PRINTF_TEST(376, "         37777777001",  "%020.5o",       4294966785U)
THOR_PRINTF_TEST(377, "            1234abcd",  "%020.5x",       305441741)
THOR_PRINTF_TEST(378, "          00edcb5433",  "%020.10x",      3989525555U)
THOR_PRINTF_TEST(379, "            1234ABCD",  "%020.5X",       305441741)
THOR_PRINTF_TEST(380, "          00EDCB5433",  "%020.10X",      3989525555U)

THOR_PRINTF_TEST(381, "",                      "%.0s",          "Hallo heimur")
THOR_PRINTF_TEST(382, "                    ",  "%20.0s",        "Hallo heimur")
THOR_PRINTF_TEST(383, "",                      "%.s",           "Hallo heimur")
THOR_PRINTF_TEST(384, "                    ",  "%20.s",         "Hallo heimur")
THOR_PRINTF_TEST(385, "                1024",  "%20.0d",        1024)
THOR_PRINTF_TEST(386, "               -1024",  "%20.d",         -1024)
THOR_PRINTF_TEST(387, "                    ",  "%20.d",         0)
THOR_PRINTF_TEST(388, "                1024",  "%20.0i",        1024)
THOR_PRINTF_TEST(389, "               -1024",  "%20.i",         -1024)
THOR_PRINTF_TEST(390, "                    ",  "%20.i",         0)
THOR_PRINTF_TEST(391, "                1024",  "%20.u",         1024)
THOR_PRINTF_TEST(392, "          4294966272",  "%20.0u",        4294966272U)
THOR_PRINTF_TEST(393, "                    ",  "%20.u",         0U)
THOR_PRINTF_TEST(394, "                 777",  "%20.o",         511)
THOR_PRINTF_TEST(395, "         37777777001",  "%20.0o",        4294966785U)
THOR_PRINTF_TEST(396, "                    ",  "%20.o",         0U)
THOR_PRINTF_TEST(397, "            1234abcd",  "%20.x",         305441741)
THOR_PRINTF_TEST(398, "            edcb5433",  "%20.0x",        3989525555U)
THOR_PRINTF_TEST(399, "                    ",  "%20.x",         0U)
THOR_PRINTF_TEST(400, "            1234ABCD",  "%20.X",         305441741)
THOR_PRINTF_TEST(401, "            EDCB5433",  "%20.0X",        3989525555U)
THOR_PRINTF_TEST(402, "                    ",  "%20.X",         0U)

THOR_PRINTF_TEST(403, "Hallo               ",  "% -0+*.*s",     20, 5, "Hallo heimur")
THOR_PRINTF_TEST(404, "+01024              ",  "% -0+*.*d",     20, 5, 1024)
THOR_PRINTF_TEST(405, "-01024              ",  "% -0+*.*d",     20, 5, -1024)
THOR_PRINTF_TEST(406, "+01024              ",  "% -0+*.*i",     20, 5, 1024)
THOR_PRINTF_TEST(407, "-01024              ",  "% 0-+*.*i",     20, 5, -1024)
THOR_PRINTF_TEST(408, "01024               ",  "% 0-+*.*u",     20, 5, 1024)
THOR_PRINTF_TEST(409, "4294966272          ",  "% 0-+*.*u",     20, 5, 4294966272U)
THOR_PRINTF_TEST(410, "00777               ",  "%+ -0*.*o",     20, 5, 511)
THOR_PRINTF_TEST(411, "37777777001         ",  "%+ -0*.*o",     20, 5, 4294966785U)
THOR_PRINTF_TEST(412, "1234abcd            ",  "%+ -0*.*x",     20, 5, 305441741)
THOR_PRINTF_TEST(413, "00edcb5433          ",  "%+ -0*.*x",     20, 10, 3989525555U)
THOR_PRINTF_TEST(414, "1234ABCD            ",  "% -+0*.*X",     20, 5, 305441741)
THOR_PRINTF_TEST(415, "00EDCB5433          ",  "% -+0*.*X",     20, 10, 3989525555U)

#if 0
# Another GHC regression test
#endif
#undef  THOR_PRINTF_TEST_GROUP
#define THOR_PRINTF_TEST_GROUP  GHC_regression
THOR_PRINTF_TEST(416, "hi x",                  "%*sx",          -3, "hi")

