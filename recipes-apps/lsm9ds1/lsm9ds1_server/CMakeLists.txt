cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(lsm9ds1_server)
SET(LICENSE "MIT")

######## Build and include settings ########
include_directories(
	inc
	../lsm9ds1/inc
)

#For the shared library:
set ( PROJECT_LINK_LIBS liblsm9ds1.so )

link_directories(
	${LINK_DIRECTORIES}
	"../lsm9ds1/Debug"
)

file(GLOB SOURCES
	"src/*.cpp"
)

add_executable(
	lsm9ds1_server

	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	lsm9ds1_server
	${PROJECT_LINK_LIBS}
)

######## Install targets ########
INSTALL(TARGETS lsm9ds1_server
	RUNTIME DESTINATION usr/bin
)
