DESCRIPTION = "Custom Package Group"

inherit packagegroup

PACKAGES = "\
    packagegroup-dof \
    packagegroup-nav \
    packagegroup-dbg \
    packagegroup-net \
    "

RDEPENDS_packagegroup-dof = "\
    cjson \
    lsm9ds1 \
    dofpipe"

RDEPENDS_packagegroup-nav = "\
    gpsd \
    gps-utils \
    gpsd-systemd \
    libgps \
    python-pygps \
    pps-tools \
    ntp \
    ntp-utils \
    logrotate \
    mt3339-utils"

RDEPENDS_packagegroup-dbg = "\
    vim \
    valgrind \
    cunit \
    "

RDEPENDS_packagegroup-net = "\
    network-conf \
    ssh-conf \
    "
#RRECOMMENDS_packagegroup-custom-tools = "\
#    kernel-module-oprofile"
