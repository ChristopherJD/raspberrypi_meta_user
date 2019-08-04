# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   LICENSE.MIT
#   third_party/cpplint/LICENSE
#   third_party/amalgamate/LICENSE.md
#   test/thirdparty/fifo_map/LICENSE.MIT
#
# NOTE: multiple licenses have been detected; they have been separated with &
# in the LICENSE value for now since it is a reasonable assumption that all
# of the licenses apply. If instead there is a choice between the multiple
# licenses then you should change the value to separate the licenses with |
# instead of &. If there is any doubt, check the accompanying documentation
# to determine which situation is applicable.
LICENSE = "Unknown & Apache-2.0 & MIT"
LIC_FILES_CHKSUM = "file://LICENSE.MIT;md5=f5f7c71504da070bcf4f090205ce1080 \
                    file://benchmarks/thirdparty/benchmark/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
                    file://third_party/cpplint/LICENSE;md5=a58572e3501e262ddd5da01be644887d \
                    file://third_party/amalgamate/LICENSE.md;md5=f3a63aaea4144ef8441e76dfa961d597 \
                    file://test/data/big-list-of-naughty-strings/LICENSE;md5=39405bfa5df6ad4245511f831248d02e \
                    file://test/data/nst_json_testsuite2/LICENSE;md5=bc7d15ad5f8486e9c3f2771a2eb2a12b \
                    file://test/data/nst_json_testsuite/LICENSE;md5=bc7d15ad5f8486e9c3f2771a2eb2a12b \
                    file://test/thirdparty/fifo_map/LICENSE.MIT;md5=b67209a1e36b682a8226de19d265b1e0 \
                    file://test/thirdparty/fastcov/LICENSE;md5=cbff3ed7f41bcdf0b95b6b6c6214451f \
                    file://test/thirdparty/doctest/LICENSE.txt;md5=93905b8d98a155f4078397748ecc86a3"

SRC_URI = "git://git@github.com/nlohmann/json.git;protocol=ssh"

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "ea60d40f4a60a47d3be9560d8f7bc37c163fe47b"

S = "${WORKDIR}/git"

inherit cmake

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""

