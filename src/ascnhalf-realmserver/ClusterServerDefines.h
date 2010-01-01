/* AscNHalf */

#ifndef _CLUSTERSERVER_DEFINES_H
#define _CLUSTERSERVER_DEFINES_H

class Database;

SERVER_DECL extern Database* Database_Character;
SERVER_DECL extern Database* Database_World;

#define WorldDatabase (*Database_World)
#define CharacterDatabase (*Database_Character)

#endif
