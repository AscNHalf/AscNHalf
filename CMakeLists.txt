PROJECT(AscNHalf)
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0005 OLD)

include(CheckIncludeFiles)
include(cmake/FindMySql.cmake)
include(cmake/FindPostgreSql.cmake)
include(cmake/PreHeader.cmake)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

OPTION(DO_MYSQL "With MySQL support" 1)
OPTION(DO_POSTGRESQL "With PostgreSQL support" 0) # not complete yet, may not link properly.
OPTION(DO_SCRIPTS "With scripts" 1)
OPTION(DO_DEBUG "Debug mode" 0)
OPTION(DO_WARN "Enable all compile warnings" 0)
OPTION(DO_DEV "Enable developer mode" 0)
OPTION(NO_WARN "Disable all compile warnings" 1)
OPTION(DO_FATAL_ERROR "Define -Wfatal-errors. Stop at first error." 1)


EXECUTE_PROCESS(
        COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/extract_git_hash.sh ${CMAKE_CURRENT_SOURCE_DIR} {rev}
        OUTPUT_VARIABLE GIT_HASH
)

message("* AscNHalf Core hash: ${GIT_HASH}")


IF(PREFIX)
    SET(CMAKE_INSTALL_PREFIX ${PREFIX})
ELSE(PREFIX)
	EXECUTE_PROCESS(COMMAND pwd OUTPUT_VARIABLE CURRENT_DIR)
    SET(CMAKE_INSTALL_PREFIX ${CURRENT_DIR}/build)
ENDIF(PREFIX)


EXECUTE_PROCESS(COMMAND pwd OUTPUT_VARIABLE CDIR)
SET(ASCNHALF_SOURCE ${CDIR}/src)

message("* AscNHalf Binary directory: ${CMAKE_INSTALL_PREFIX}")

add_definitions("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")

SET(CONFDIR ${CMAKE_INSTALL_PREFIX}/etc)
SET(LIBSDIR ${CMAKE_INSTALL_PREFIX}/lib)
SET(BINDIR ${CMAKE_INSTALL_PREFIX}/bin)

#SET(SHARED_LIB ./src/ascnhalf-shared/libshared.a)

add_definitions("-DCONFDIR=\"${CONFDIR}\"")
add_definitions("-DLIBSDIR=\"${LIBSDIR}\"")
add_definitions("-DBINDIR=\"${BINDIR}\"")

if(DO_FATAL_ERROR)
message("* Stopping at first error.")
add_definitions(-Wfatal-errors)
endif(DO_FATAL_ERROR)

IF(DO_DEV)
message("* Developer mode: ON")
add_definitions("-DASCENT_DEV")
ENDIF(DO_DEV)

if(DO_SCRIPTS)
message("* With Script library")
else(DO_SCRIPTS)
message("* Without Script library")
endif(DO_SCRIPTS)


message("* Will install to: ${CMAKE_INSTALL_PREFIX}")
message("* With config dir at: ${CONFDIR}")
message("* Libs install dir at: ${LIBSDIR}")

FIND_LIBRARY(SSLLIB NAMES ssl DOC "SSL library")
FIND_LIBRARY(ZLIB z "Zlib library")
find_library(PCRE_LIBRARY pcre)

IF(DO_POSTGRESQL)
    MESSAGE("* With PostgreSQL")
    FIND_PostgreSQL()
    ADD_DEFINITIONS(-DDO_POSTGRESQL)
ENDIF(DO_POSTGRESQL)

IF(DO_MYSQL)
    MESSAGE("* With MySQL")
    FIND_MYSQL()
    ADD_DEFINITIONS(-DDO_MYSQL)
ENDIF(DO_MYSQL)

message("-- Miscellaneus options:")

if(DO_DEBUG)
message("* Debug mode ON")
add_definitions(-g -D_DEBUG)
endif(DO_DEBUG)

if(DO_WARN)
    message("* All warnings mode")
    add_definitions(-Wall -Wextra)
endif(DO_WARN)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

IF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
  SET(OSX_LIBS /opt/local/lib/libcrypto.dylib)
  add_definitions(-D__ASSERTMACROS__)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

IF(NO_WARN)
message("* No warnings mode.")
add_definitions(--no-warnings)
ENDIF(NO_WARN)



INCLUDE_DIRECTORIES(
    src/ascnhalf-shared
    src/ascnhalf-shared/Auth
    src/ascnhalf-shared/Database
    src/ascnhalf-shared/Collision
    src/ascnhalf-shared/Config
    src/ascnhalf-shared/Network-New
    src/ascnhalf-shared/Threading
    src/ascnhalf-world
    ${CMAKE_BINARY_DIR}
    ${MYSQL_INCLUDE_DIR}
    ${POSTGRESQL_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/src/shared
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(src)
