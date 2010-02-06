add_subdirectory(ascnhalf-shared)
add_subdirectory(ascnhalf-logonserver)
add_subdirectory(ascnhalf-world)
IF(DO_SCRIPTS)
add_subdirectory(ascnhalf-scripts)
ENDIF(DO_SCRIPTS)

FILE( GLOB _CONFIG_ *.conf )
install( FILES ${_CONFIG_} DESTINATION etc )
