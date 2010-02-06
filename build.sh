#!/bin/bash
# Copyright (C) 2010 Twl and the AscNHalf Team.
# Autobuilder

echo -e "\nAscNHalf Auto Builder by Twl.\n";
echo -e "The builder will now execute the required operations to build the core.\n";
echo -e "Press any key...";
read
clear
sleep 1
currentdir=`pwd`
mkdir build
echo -e "Running cmake...\nPrefix is: $currentdir/build";
chmod +x ./extract_svn_revision.sh
sleep 2
cmake -DPREFIX="$currentdir/build" -DDO_SCRIPTS=1
if [ "$?" = "0" ]; then echo -e "Cmake finished successfully.\n"
else
echo -e "\nCmake returned errors. Aborting.\n";
exit 1
fi
#echo -e "\nExtracting revision...";
sleep 1
# ./extract_svn_revision.sh
echo -e "\nNow proceeding to the main process.\n";
echo -e "Press any key...";
read
clear
echo -e "\nRunning make and make install. This may take a long time.\n"
sleep 2
make -j2
if [ "$?" = "0" ]; then echo -e "\nMake successful.\n"
else
echo -e "\nMake returned errors. Aborting\n";
exit 1
fi
sleep 1
make -j2 install
if [ "$?" = "0" ]; then echo -e "\nInstall successful.\n"
else
echo -e "\nInstall failed. Aborting.\n";
exit 1
fi
sleep 1
echo -e "Copying required files...\n";
mkdir ./build/lib
mv src/ascnhalf-scripts/src/libevent.a ./build/lib
echo -e "Copying: libevent.a\n";
mv src/ascnhalf-scripts/src/libgossip.a ./build/lib
echo -e "Copying: libgossip.a\n";
mv src/ascnhalf-scripts/src/libextra.a ./build/lib
echo -e "Copying: libextra.a\n";
mv src/ascnhalf-scripts/src/libmisc.a ./build/lib
echo -e "Copying: libmisc.a\n";
mv src/ascnhalf-scripts/src/libinstance.a ./build/lib
echo -e "Copying: libinstance.a\n";
mv src/ascnhalf-scripts/src/libpvp.a ./build/lib
echo -e "Copying: libpvp.a\n";
mv src/ascnhalf-scripts/src/libspell.a ./build/lib
echo -e "Copying: libspell.a\n";
mv src/ascnhalf-scripts/src/libquest.a ./build/lib
echo -e "Copying: libquest.a";

echo -e "\n\nBuild complete!\n";




