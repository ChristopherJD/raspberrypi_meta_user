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


PROVIDES = "dofpipe"

DEPENDS += "cjson"
DEPENDS += "lsm9ds1"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = "\
    file://doflogd.service \
    file://doflogger.sh \
"

# https://lists.yoctoproject.org/pipermail/yocto/2014-July/020408.html
# https://wiki.yoctoproject.org/wiki/TipsAndTricks/Packaging_Prebuilt_Libraries
# I think we need to version the library to remove this statement.

systemd_system_unitdir = "/lib/systemd/system/"
FILES_${PN} += "${systemd_system_unitdir}"
FILES_${PN} += "${bindir}"
FILES_${PN} += "/usr/share/man/man8*"

RDEPENDS_${PN} = "bash"
SYSTEMD_SERVICE_${PN} = "doflogd.service"

SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/ChristopherJD/dofpipe.git;protocol=http;branch=master"

S = "${WORKDIR}/git"

do_install_append () {
	install -d "${D}/${bindir}"
	install -D ${WORKDIR}/doflogger.sh "${D}/${bindir}"

	install -d "${D}/${systemd_system_unitdir}"
    install -m 0644 ${WORKDIR}/doflogd.service ${D}/${systemd_system_unitdir}
}

inherit pkgconfig cmake

