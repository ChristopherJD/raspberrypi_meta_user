SUMMARY = "A console-only image that fully supports the target device \
hardware."

IMAGE_FEATURES += "splash"
IMAGE_FEATURES += "ssh-server-openssh"
IMAGE_FEATURES += "tools-debug"
IMAGE_FEATURES += "eclipse-debug"

LICENSE = "MIT"

inherit core-image
