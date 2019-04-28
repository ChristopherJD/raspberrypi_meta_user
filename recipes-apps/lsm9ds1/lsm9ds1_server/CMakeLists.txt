cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(lsm9ds1_server)
SET(LICENSE "MIT")

######## Build and include settings ########
include_directories(
	inc
)

link_directories(
	${LINK_DIRECTORIES}
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB SOURCES
	"src/*.c"
	"src/*.cpp"
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
