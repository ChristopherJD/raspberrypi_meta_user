AC_PREREQ(2.61)

# package version number (not shared library version)
# odd micro numbers indicate in-progress development
# even micro numbers indicate released versions
m4_define(spidev_test_version_major, 0)
m4_define(spidev_test_version_minor, 1)
m4_define(spidev_test_version_micro, 0)

m4_define([spidev_test_version],
          [spidev_test_version_major.spidev_test_version_minor.spidev_test_version_micro])
m4_define([spidev_test_api_version],
          [spidev_test_version_major.spidev_test_version_minor])

AC_INIT(spidev_test, spidev_test_version)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

# Checks for programs.
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
AC_PROG_INSTALL

AC_SUBST(spidev_test_CFLAGS)
AC_SUBST(spidev_test_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
])

echo ""
echo "   spidev_test $VERSION"
echo "   ====================="
echo ""
echo "   To build the project, run \"make\""
echo ""
