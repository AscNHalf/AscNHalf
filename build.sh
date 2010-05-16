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
chmod +x ./extract_git_hash.sh
sleep 2
cmake -DPREFIX="$currentdir/build" -DDO_MYSQL=1 -DDO_SCRIPTS=1
if [ "$?" = "0" ]; then echo -e "Cmake finished successfully.\n"
else
echo -e "\nCmake returned errors. Aborting.\n";
exit 1
fi
#echo -e "\nExtracting revision...";
sleep 1
# ./extract_git_hash.sh
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

echo -e "\n\nBuild complete!\n";




