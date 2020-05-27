FILESEXTRAPATHS_prepend := "${THISDIR}/qemu:"
SRC_URI_append += " \
	file://0011-linux-user-remove-host-stime-syscall.patch \
"
