AC_PREREQ(2.61)

# package version number (not shared library version)
# odd micro numbers indicate in-progress development
# even micro numbers indicate released versions
m4_define(LSM9DS1_version_major, 0)
m4_define(LSM9DS1_version_minor, 1)
m4_define(LSM9DS1_version_micro, 0)

m4_define([LSM9DS1_version],
          [LSM9DS1_version_major.LSM9DS1_version_minor.LSM9DS1_version_micro])
m4_define([LSM9DS1_api_version],
          [LSM9DS1_version_major.LSM9DS1_version_minor])

AC_INIT(LSM9DS1, LSM9DS1_version)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

# Checks for programs.
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
AC_PROG_INSTALL

AC_SUBST(LSM9DS1_CFLAGS)
AC_SUBST(LSM9DS1_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
])

echo ""
echo "   LSM9DS1 $VERSION"
echo "   ====================="
echo ""
echo "   To build the project, run \"make\""
echo ""
