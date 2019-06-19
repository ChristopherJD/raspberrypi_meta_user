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
LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "file://LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464"


PROVIDES = "lsm9ds1"

DEPENDS += "python3"
DEPENDS += "cunit"
DEPENDS += "wiringpi"

FILES_${PN} += "${libdir}/python3.5/site-packages/"

# https://lists.yoctoproject.org/pipermail/yocto/2014-July/020408.html
# https://wiki.yoctoproject.org/wiki/TipsAndTricks/Packaging_Prebuilt_Libraries
# I think we need to version the library to remove this statement.
FILES_SOLIBSDEV = ""
FILES_${PN} += "${libdir}"


SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/ChristopherJD/lsm9ds1.git;protocol=ssh;user=git;branch=master"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

do_install () {
	install -d ${D}${libdir}
	install -d ${D}${libdir}/python3.5/site-packages
	install -m 0755 liblsm9ds1.so ${D}${libdir}
	install -m 0755 pylsm9ds1.so ${D}${libdir}/python3.5/site-packages
}

