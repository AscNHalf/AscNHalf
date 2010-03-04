add_subdirectory(ascnhalf-shared)
add_subdirectory(ascnhalf-logonserver)
add_subdirectory(ascnhalf-world)
IF(DO_SCRIPTS)
add_subdirectory(ascnhalf-scripts)
ENDIF(DO_SCRIPTS)

IF(DO_DEV)
message("* Recursing into dev.")
add_subdirectory(ascnhalf-dev)
ENDIF(DO_DEV)

FILE( GLOB _CONFIG_ *.conf )
install( FILES ${_CONFIG_} DESTINATION etc )
