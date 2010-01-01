INCLUDES = -I$(top_srcdir)/src/ascnhalf-logonserver \
   -I$(top_srcdir)/src/ascnhalf-realmserver -I$(top_srcdir)/src/ascnhalf-shared -I$(top_srcdir)/src/ascnhalf-voicechat \
   -I$(top_srcdir)/src/ascnhalf-world -I$(srcdir) -I$(srcdir)/../../../../dep/include \
   -I$(srcdir)/../../../../dep/src -I$(srcdir)/../../../../src -I../Common
INCLUDES += -I$(srcdir)/../../../ascnhalf-shared/g3dlite -I$(srcdir)/../../../ascnhalf-shared/vmap

AM_CXXFLAGS = -DSCRIPTLIB

lib_LTLIBRARIES = libSunEventScripts.la

libSunEventScripts_la_SOURCES = Setup.cpp \
../Common/Base.cpp \
Halloween.cpp \
WinterVeil.cpp \
Event_DarkPortal.cpp
