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

#ifndef __PACKET_H
#define __PACKET_H

typedef struct  
{
	uint32 opcode;
	uint32 size;
	uint8* buffer;
	uint32 buffer_size;
	uint32 rpos;
	uint32 wpos;
	int stack;
} packet;

static packet* packet_create(uint32 opcode, uint32 size)
{
	packet * p;

	p = (packet*)vc_malloc(sizeof(packet));
	p->buffer = (uint8*)vc_malloc(size);
	p->buffer_size = size;
	p->opcode = opcode;
	p->size = size;
	p->wpos = p->rpos = 0;
	p->stack = 0;

	return p;
}

static void packet_init(uint32 opcode, uint32 size, packet *p)
{
	p->buffer = (uint8*)vc_malloc(size);
	p->buffer_size = size;
	p->opcode = opcode;
	p->size = size;
	p->wpos = p->rpos = 0;
	p->stack = 1;
}

static uint8* packet_getbuf(packet* p)
{
	return &p->buffer[p->wpos];
}

static void packet_free(packet* p)
{
	free(p->buffer);
	if( !p->stack )
		free(p);
}


/*
static uint32 packet_readu32(packet* p)
{
	uint32 orpos = p->rpos;
	p->rpos += sizeof(uint32);
	return *(uint32*)&p->buffer[orpos];
}
*/

#define DECLARE_PACKET_OPERATOR(t, name) static t name(packet* p) { \
	uint32 orpos = p->rpos; \
	p->rpos += sizeof(t); \
	return *(t*)&p->buffer[orpos]; }

DECLARE_PACKET_OPERATOR(uint32, packet_readu32);
DECLARE_PACKET_OPERATOR(int32, packet_readi32);
DECLARE_PACKET_OPERATOR(uint16, packet_readu16);
DECLARE_PACKET_OPERATOR(int16, packet_readi16);
DECLARE_PACKET_OPERATOR(uint8, packet_readu8);
DECLARE_PACKET_OPERATOR(int8, packet_readi8);

/*
static void packet_writeu32(packet* p, uint32 v)
{
	*(uint32*)&p->buffer[p->wpos] = v;
	p->wpos += sizeof(uint32);
}
*/

#define DECLARE_PACKET_WRITE_OPERATOR(t, name) static void name(packet* p, t v) { \
	*(t*)&p->buffer[p->wpos] = v; \
	p->wpos += sizeof(t); } 

DECLARE_PACKET_WRITE_OPERATOR(uint32, packet_writeu32);
DECLARE_PACKET_WRITE_OPERATOR(int32, packet_writei32);
DECLARE_PACKET_WRITE_OPERATOR(uint16, packet_writeu16);
DECLARE_PACKET_WRITE_OPERATOR(int16, packet_writei16);
DECLARE_PACKET_WRITE_OPERATOR(uint8, packet_writeu8);
DECLARE_PACKET_WRITE_OPERATOR(int8, packet_writei8);


#endif
