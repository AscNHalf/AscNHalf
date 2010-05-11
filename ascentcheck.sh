#!/bin/bash
GXX="/usr/bin/g++"
COMPILE_FLAGS="-finput-charset=UTF-8 -w -Wfatal-errors -I/usr/include -std=gnu++0x -o "
LINK_FLAGS=""
echo "Ascent C++ standard checker."
echo "Written by Twl 2010/05/11"
echo "Checks for supported stuff from the new standard."
echo ""
echo "Press return to begin..."
read
cd ./dep/checks
echo "// Ascent standard/compiler related configs." > ascent.hpp
echo "// generated using ascentcheck, do not modify it." >> ascent.hpp
echo "" >> ascent.hpp
echo -ne "Running boost check... "
sleep 1
$GXX $COMPILE_FLAGS boostcheck boostcheck.cxx $LINK_FLAGS
sleep 1
if [ -f boostcheck ]; then echo "passed." && echo "#define ASCENT_HAS_BOOST 1" >> ascent.hpp
else
echo "failed."
exit 1
fi
echo -ne "Running TR1 check... "
sleep 1
$GXX $COMPILE_FLAGS trcheck trcheck.cxx $LINK_FLAGS
sleep 1
if [ -f trcheck ]; then echo "passed." && echo "#define ASCENT_HAS_TR1 1" >> ascent.hpp
else
echo "failed."
exit 1
fi

