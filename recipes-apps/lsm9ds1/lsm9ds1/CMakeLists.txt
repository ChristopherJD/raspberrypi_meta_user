cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(liblsm9ds1)
SET(LICENSE "TBD")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

######## Build and include settings ########
include_directories(
	inc
)

link_directories(
	${LINK_DIRECTORIES}
)


file(GLOB SOURCES
	"src/*.c"
)

#Generate the shared library from the sources
add_library(lsm9ds1 SHARED ${SOURCES})

######## Install targets ########
INSTALL(TARGETS lsm9ds1
	DESTINATION usr/lib/
)
