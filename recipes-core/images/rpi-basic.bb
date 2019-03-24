SUMMARY = "A console-only image that fully supports the target device \
hardware."

IMAGE_FEATURES += "splash"
IMAGE_FEATURES += "ssh-server-dropbear"

LICENSE = "MIT"

inherit core-image
