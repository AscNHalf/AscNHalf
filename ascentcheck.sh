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
rm -f *.tst
rm -f *.log
echo "// Ascent standard/compiler related configs." > ascent.hpp
echo "// generated using ascentcheck, do not modify it." >> ascent.hpp
echo "" >> ascent.hpp
echo -ne "Running boost check... "
sleep 1
$GXX $COMPILE_FLAGS boostcheck.tst boostcheck.cxx $LINK_FLAGS &> boostcheck.log
sleep 1
if [ -f boostcheck.tst ]; then echo "passed." && echo "#define ASCENT_HAS_BOOST 1" >> ascent.hpp
else
echo "failed."
exit 1
fi
echo -ne "Running TR1 check... "
sleep 1
$GXX $COMPILE_FLAGS trcheck.tst trcheck.cxx $LINK_FLAGS &> trcheck.log
sleep 1
if [ -f trcheck.tst ]; then echo "passed." && echo "#define ASCENT_HAS_TR1 1" >> ascent.hpp
else
echo "failed."
exit 1
fi
echo -ne "Running standard shared_ptr check... "
sleep 1
$GXX $COMPILE_FLAGS stdspcheck.tst stdspcheck.cxx $LINK_FLAGS &> stdspcheck.log
sleep 1
if [ -f stdspcheck.tst ]; then echo "passed." && echo "#define ASCENT_HAS_STD_SHARED_POINTER 1" >> ascent.hpp
else
echo "failed."
#exit 1
fi
echo -ne "Running auto type check... "
sleep 1
$GXX $COMPILE_FLAGS autocheck.tst autocheck.cxx $LINK_FLAGS &> autocheck.log
sleep 1
if [ -f autocheck.tst ]; then echo "passed." && echo "#define ASCENT_HAS_AUTO_TYPE 1" >> ascent.hpp
else
echo "failed."
#exit 1
fi
