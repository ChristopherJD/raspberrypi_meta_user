# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=080960691ed1de63889eff39979df3b1"

DEPENDS += "boost"

PROVIDES = "served"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/meltwater/served.git;protocol=http;branch=master"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

