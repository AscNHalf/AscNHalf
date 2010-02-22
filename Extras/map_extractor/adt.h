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


#ifndef ADT_H
#define ADT_H

#define TILESIZE (533.33333f)
#define CHUNKSIZE ((TILESIZE) / 16.0f)
#define UNITSIZE (CHUNKSIZE / 8.0f)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
class Liquid;
typedef struct {
float x;
float y;
float z;
}svec;

typedef struct {
double x;
double y;
double z;
}vec;

typedef struct{
	vec v[3];

}triangle;	

typedef struct{
float v9[16*8+1][16*8+1];
float v8[16*8][16*8];
}Cell;

typedef struct{
double v9[9][9];
double v8[8][8];
uint16 area_id;
//Liquid *lq;
float waterlevel;
uint8 flag;
}chunk;


class WMO;
class WMOManager;
void fixname(std::string &name);


typedef struct
{
chunk ch[16][16];
}mcell;
class MPQFile;
struct MapChunkHeader;
void LoadMapChunk(MapChunkHeader *,chunk*);
bool LoadWMO(char* filename);
#endif

