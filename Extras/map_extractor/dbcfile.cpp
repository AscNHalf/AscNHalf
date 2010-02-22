/*
  * AscNHalf MMORPG Server
  * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
  * Copyright (C) 2010 AscNHalf Team <http://ascnhalf.scymex.info/>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Affero General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Affero General Public License for more details.
  *
  * You should have received a copy of the GNU Affero General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */


#include "dbcfile.h"
#include "mpq_libmpq.h"

DBCFile::DBCFile(const std::string &filename):
	filename(filename),
	data(0)
{
	
}
void DBCFile::open()
{
	MPQFile f(filename.c_str());
	char header[4];
	unsigned int na,nb,es,ss;

	f.read(header,4); // Number of records
	assert(header[0]=='W' && header[1]=='D' && header[2]=='B' && header[3] == 'C');
	f.read(&na,4); // Number of records
	f.read(&nb,4); // Number of fields
	f.read(&es,4); // Size of a record
	f.read(&ss,4); // String size
	
	recordSize = es;
	recordCount = na;
	fieldCount = nb;
	stringSize = ss;
	assert(fieldCount*4 == recordSize);

	data = new unsigned char[recordSize*recordCount+stringSize];
	stringTable = data + recordSize*recordCount;
	f.read(data,recordSize*recordCount+stringSize);
	f.close();
}
DBCFile::~DBCFile()
{
	delete [] data;
}

DBCFile::Record DBCFile::getRecord(size_t id)
{
	assert(data);
	return Record(*this, data + id*recordSize);
}

DBCFile::Iterator DBCFile::begin()
{
	assert(data);
	return Iterator(*this, data);
}
DBCFile::Iterator DBCFile::end()
{
	assert(data);
	return Iterator(*this, stringTable);
}

