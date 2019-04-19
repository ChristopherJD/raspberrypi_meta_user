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
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

inherit systemd

# No information for SRC_URI yet (only an external source tree was specified)
SRC_URI = "file://20-wired.network \
	file://25-wireless.network \
	file://lib/systemd/system/wpa_supplicant-wlan0.service \
	file://wpa_supplicant/wpa_supplicant-wlan0.conf"

FILES_${PN} += "${sysconfdir}/wpa_supplicant"
FILES_${PN} += "${sysconfdir}/systemd"
FILES_${PN} += "${systemd_unitdir}/system"
FILES_${PN} += "${sysconfdir}/systemd/system/multi-user.target.wants"

SYSTEMD_SERVICE_${PN} = "wpa_supplicant-wlan0.service"

PROVIDES = "network-conf"

# NOTE: no Makefile found, unable to determine what needs to be done

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# Specify compilation commands here
	:
}

do_install () {
	# Specify install commands here
	#
	install -d ${D}${systemd_unitdir}/system
	install -d ${D}${sysconfdir}/systemd/network
	install -d ${D}${sysconfdir}/systemd/system
	install -d ${D}${sysconfdir}/systemd/system/multi-user.target.wants
	install -d ${D}${sysconfdir}/wpa_supplicant

	install -c -m 0644 ${WORKDIR}/20-wired.network ${D}${sysconfdir}/systemd/network
	install -c -m 0644 ${WORKDIR}/25-wireless.network ${D}${sysconfdir}/systemd/network
	install -c -m 0644 ${WORKDIR}${systemd_unitdir}/system/wpa_supplicant-wlan0.service ${D}${systemd_unitdir}/system
	install -c -m 0644 ${WORKDIR}/wpa_supplicant/wpa_supplicant-wlan0.conf ${D}${sysconfdir}/wpa_supplicant/

	# Needed to enable the wpa service, this is hacky why do I have to do this?
	ln -s -r ${D}${systemd_unitdir}/system/wpa_supplicant-wlan0.service ${D}${sysconfdir}/systemd/system/dbus-fi.w1.wpa_supplicant1.service
	ln -s -r ${D}${systemd_uintdir}/system/wpa_supplicant-wlan0.service ${D}${sysconfdir}/systemd/system/multi-user.target.wants/wpa_supplicant-wlan0.service
}

