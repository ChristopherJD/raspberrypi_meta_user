AC_PREREQ(2.61)

# package version number (not shared library version)
# odd micro numbers indicate in-progress development
# even micro numbers indicate released versions
m4_define(hello_world_version_major, 0)
m4_define(hello_world_version_minor, 1)
m4_define(hello_world_version_micro, 0)

m4_define([hello_world_version],
          [hello_world_version_major.hello_world_version_minor.hello_world_version_micro])
m4_define([hello_world_api_version],
          [hello_world_version_major.hello_world_version_minor])

AC_INIT(hello_world, hello_world_version)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

# Checks for programs.
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
AC_PROG_INSTALL

AC_SUBST(hello_world_CFLAGS)
AC_SUBST(hello_world_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
])

echo ""
echo "   hello_world $VERSION"
echo "   ====================="
echo ""
echo "   To build the project, run \"make\""
echo ""
