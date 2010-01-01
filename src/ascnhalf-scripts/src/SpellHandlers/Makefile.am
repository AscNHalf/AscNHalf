INCLUDES = -I$(top_srcdir)/src/ascnhalf-logonserver \
   -I$(top_srcdir)/src/ascnhalf-realmserver -I$(top_srcdir)/src/ascnhalf-shared -I$(top_srcdir)/src/ascnhalf-voicechat \
   -I$(top_srcdir)/src/ascnhalf-world -I$(srcdir) -I$(srcdir)/../../../../dep/include \
   -I$(srcdir)/../../../../dep/src -I$(srcdir)/../../../../src
INCLUDES += -I$(srcdir)/../../../ascnhalf-shared/g3dlite -I$(srcdir)/../../../ascnhalf-shared/vmap
AM_CXXFLAGS = -DSCRIPTLIB

lib_LTLIBRARIES = libSpellHandlers.la

libSpellHandlers_la_SOURCES = DruidSpells.cpp HunterSpells.cpp ItemSpells_1.cpp \
MageSpells.cpp PaladinSpells.cpp PriestSpells.cpp OldSpellCPPStuff.cpp RogueSpells.cpp \
ShamanSpells.cpp WarlockSpells.cpp WarriorSpells.cpp Raid_BlackTemple.cpp QIspells.cpp Setup.cpp
