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

// AscNHalf Configuration Header File
// Feel free to customize to your needs.

#ifndef __CONFIG_H
#define __CONFIG_H

/** Enable/disable AscNHalfworld server debugging. 
 * Enabling this will cause massive spam in the world server window, but will list
 * packets recieved and certian player information.
 * Default: Disabled
 */

//#define _DEBUG 1

/** Enable/disable AscNHalf world server optimized player saving. 
 * It is not yet complete, things have to be updated, and player account data needs to be fixed.
 * Player guilds need to be updated as well, not saving correctly :|
 * Default: Disabled
 */

//#define OPTIMIZED_PLAYER_SAVING 1

/** Enable/disable AscNHalf world server cluster support.
 * Warning: AscNHalf will no longer function independantly when built in cluster mode. 
 * It will require a realmserver to function.
 * As of last update, it is nowhere near complete, only enable for dev use.
 * Default: Disabled
 */

#ifdef ENABLE_CLUSTERING
#  error Sorry but clustering is not finished yet. dont bother to try to compile it. it wont work.
#  define CLUSTERING 1
#endif

//#define CLUSTERING 1

/** Use memory mapping for map files for faster access (let OS take care of caching)
 * (currently only available under windows)
 * Only recommended under X64 builds, X86 builds will most likely run out of address space.
 * Default: Disabled
 */

//#define USE_MEMORY_MAPPING_FOR_MAPS

/** Enable/disable AscNHalf's Voice Chat support.
 * While not completely finished (but close!) you can link your AscNHalf server to a voice chat
 * server (also compiled by default) and use the client's ingame voice chat function.
 * At the moment it is only good for joining, you can't leave a voice channel yet :P
 * Also, it only works for parties. Custom chat channels are not fully supported yet.
 * However, if you want to play around with it, feel free to enable this define.
 */

//#define VOICE_CHAT 1

/** Enable/disable movement compression.
 * This allows the server to compress long-range creatures movement into a buffer and then flush
 * it periodically, compressed with deflate. This can make a large difference to server bandwidth.
 * Currently this sort of compression is only used for player and creature movement, although
 * it may be expanded in the future.
 * Default: disabled
 */

#define ENABLE_COMPRESSED_MOVEMENT 1
#define ENABLE_COMPRESSED_MOVEMENT_FOR_PLAYERS 1
#define ENABLE_COMPRESSED_MOVEMENT_FOR_CREATURES 1


/** Enable/disable the use of boost.
  * Currently it does not compile without this.
  * Default: enabled
*/

//#define ENABLE_BOOST 1

/** Enable/disable the use of boost shared_ptr's.
  * It is in testing currently, should only be used by devs.
  * Default: disabled
*/

#define ENABLE_SHARED_POINTERS 1

//Allow loading of unused testmaps.
//#define EXCLUDE_TEST_MAPS 1

#endif		// __CONFIG_H

