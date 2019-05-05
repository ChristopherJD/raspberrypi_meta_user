cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(lsm9ds1_client)
SET(LICENSE "TBD")

######## Build and include settings ########
include_directories(
	inc
)

link_directories(
	${LINK_DIRECTORIES}
)


file(GLOB SOURCES
	"src/*.cpp"
)

add_executable(
	lsm9ds1_client

	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	lsm9ds1_client
	boost_system
	boost_thread
	pthread
)

######## Install targets ########
INSTALL(TARGETS lsm9ds1_client
	RUNTIME DESTINATION usr/bin
)
