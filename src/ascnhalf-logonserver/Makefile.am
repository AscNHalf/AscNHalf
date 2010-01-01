INCLUDES += -I$(srcdir) -I$(srcdir)/../../dep/include -I$(srcdir)/../ascnhalf-shared

bin_PROGRAMS = ascnhalf-logonserver

ascnhalf_logonserver_SOURCES = \
	AccountCache.cpp \
	AccountCache.h \
	AuthSocket.cpp \
	AuthSocket.h \
	AuthStructs.h \
	LogonCommServer.cpp \
	LogonCommServer.h \
	LogonConsole.cpp \
	LogonConsole.h \
	LogonOpcodes.cpp \
	LogonOpcodes.h \
	LogonStdAfx.cpp \
	LogonStdAfx.h \
	AutoPatcher.h \
	AutoPatcher.cpp \
	Main.cpp \
	Main.h \
	PeriodicFunctionCall_Thread.h

ascnhalf_logonserver_LDADD = -lshared -lz
ascnhalf_logonserver_LDFLAGS = -L$(srcdir)/../ascnhalf-shared
