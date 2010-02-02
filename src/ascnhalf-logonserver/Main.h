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

#ifndef LOGONSERVER_MAIN
#define LOGONSERVER_MAIN

#include "../ascnhalf-shared/Singleton.h"

extern bool mrunning;
class AuthSocket;
extern set<AuthSocket*> _authSockets;
extern Mutex _authSocketLock;
extern bool m_encryptedPasswords;

struct AllowedIP
{
	unsigned int IP;
	unsigned char Bytes;
};

bool IsServerAllowed(unsigned int IP);
bool IsServerAllowedMod(unsigned int IP);

class LogonServer : public Singleton< LogonServer >
{
public:
	void CheckForDeadSockets();
	void Run(int argc, char ** argv);
	void Stop();
	uint32 max_build;
	uint32 min_build;
	uint8 sql_hash[20];

private:
	bool m_stopEvent;
};

#endif	// LOGONSERVER_MAIN