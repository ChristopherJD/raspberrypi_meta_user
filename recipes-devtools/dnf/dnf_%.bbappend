FILES_${PN} += "${SYSCONFDIR}/dnf/"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " \
	file://dnf.conf \
"

do_install_append () {
	# Overwrite the configuration.
	#
	install -d "${D}/etc/dnf"
	install -D ${WORKDIR}/dnf.conf "${D}/etc/dnf/dnf.conf"
}

