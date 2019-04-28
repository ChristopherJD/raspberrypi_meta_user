cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(lsm9ds1_server)
SET(LICENSE "TBD")

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

add_executable(
	lsm9ds1_server

	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	lsm9ds1_server
)

######## Install targets ########
INSTALL(TARGETS lsm9ds1_server
	RUNTIME DESTINATION usr/bin
)
