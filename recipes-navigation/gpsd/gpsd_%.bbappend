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
#LICENSE = "BSD"
#LICENSE = "CLOSED"
#LIC_FILES_CHKSUM = "file://COPYING;md5=d217a23f408e91c94359447735bc1800"

# No information for SRC_URI yet (only an external source tree was specified)
#DEPENDS += "gpsd"
#FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

FILES_${PN} += " ${sysconfdir}/default \
	${systemd_system_unitdir} \
	${bindir} \
"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = "\
	file://gpsd.default \
	file://gpslogd.service \
	file://0001-Handle-SIGHUP-for-daemon-reloads.patch \
    file://gpslogger.sh \
"

#RDEPENDS_${PN} = "bash"
RDEPENDS_gps-utils = "bash"
SYSTEMD_SERVICE_${PN} = "gpsd.service"
SYSTEMD_SERVICE_${PN} = "gpslogd.service"


do_install_append () {
	# Overwrite the configuration.
	#
	install -d "${D}/etc/default"
	install -D ${WORKDIR}/gpsd.default "${D}/etc/default/gpsd.default"

	install -d "${D}${bindir}"
	install -D ${WORKDIR}/gpslogger.sh "${D}${bindir}"

	install -d ${D}/${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/gpslogd.service ${D}/${systemd_system_unitdir}
}

