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

# No information for SRC_URI yet (only an external source tree was specified)
FILES_${PN} += "${SYSCONFDIR}"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = "file://ntp.conf"

do_install_append () {
	# Overwrite the configuration.
	#
    	install -m 644 ${WORKDIR}/ntp.conf ${D}${sysconfdir}
}

