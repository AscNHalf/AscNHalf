INCLUDES = -I$(top_srcdir)/src/ascnhalf-logonserver \
   -I$(top_srcdir)/src/ascnhalf-realmserver -I$(top_srcdir)/src/ascnhalf-shared -I$(top_srcdir)/src/ascnhalf-voicechat \
   -I$(top_srcdir)/src/ascnhalf-world -I$(srcdir) -I$(srcdir)/../../../../dep/include \
   -I$(srcdir)/../../../../dep/src -I$(srcdir)/../../../../src
INCLUDES += -I$(srcdir)/../../../ascnhalf-shared/g3dlite -I$(srcdir)/../../../ascnhalf-shared/vmap

AM_CXXFLAGS = -DSCRIPTLIB

lib_LTLIBRARIES = libSunMiscScripts.la

libSunMiscScripts_la_SOURCES = Creatures.cpp \
GameObjects.cpp \
RandomScripts.cpp \
QuelDanasPortal.cpp \
DarkmoonFaireObjects.cpp \
Setup.cpp
