SET(ascnhalf_logon_SCRS
	AccountCache.cpp
	AccountCache.h
	AuthSocket.cpp
	AuthSocket.h
	AuthStructs.h
	LogonCommServer.cpp
	LogonCommServer.h
	LogonConsole.cpp
	LogonConsole.h
	LogonOpcodes.cpp
	LogonOpcodes.h
	LogonStdAfx.cpp
	LogonStdAfx.h
	AutoPatcher.h
	AutoPatcher.cpp
	Main.cpp
	Main.h
	PeriodicFunctionCall_Thread.h
)

add_executable(ascnhalf_logon ${ascnhalf_logon_SCRS})

target_link_libraries(
    ascnhalf_logon
    shared
    ${SSLLIB}
    ${MYSQL_LIBRARIES}
    ${POSTGRESQL_LIBRARIES}
)

install(TARGETS ascnhalf_logon DESTINATION bin)
