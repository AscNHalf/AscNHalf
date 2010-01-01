#!/bin/sh
echo Extracting svn_revision...
sh svn_revision_extractor.sh
echo Building Precompiled Header...
cd src/ascnhalf-world
g++ -std=c++0x -pthread -Wall -DHAVE_CONFIG_H -I. -I../.. -I/usr/include/mysql -I/usr/include/openssl -I/usr/local/include/openssl -I/usr/local/include -I. -I./../ascnhalf-shared -o StdAfx.h.gch StdAfx.h

echo Done!
echo You should run this again every time a .h file changes.