#!/bin/bash

# SVN Revision Extractor for Unix systems
# Written by Burlex, 2008/02/20

revision=`svn info | grep Revision | cut -d' ' -f2`
echo "// This file was automatically generated by the SVN revision extractor." > svn_revision.h
echo "// There is no need to modify it." >> svn_revision.h
echo "" >> svn_revision.h
echo "#ifndef SVN_REVISION_H" >> svn_revision.h
echo "#define SVN_REVISION_H" >> svn_revision.h
echo "" >> svn_revision.h
echo "static const char * BUILD_TAG = \"ASCNHALF-1.0\";" >> svn_revision.h
echo "static int BUILD_REVISION = "$revision";" >> svn_revision.h
echo "static const char * BUILD_USER = \"$USER\";" >> svn_revision.h
echo "static const char * BUILD_HOST = \"`hostname -f`\";" >> svn_revision.h
echo "" >> svn_revision.h
echo "#endif         // SVN_REVISION_H" >> svn_revision.h
echo "" >> svn_revision.h
mv ./svn_revision.h ./src/ascnhalf-shared
echo "Found revision: $revision";