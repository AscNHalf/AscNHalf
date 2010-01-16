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

#ifndef _GETOPT_H
#define _GETOPT_H

/* getopt() wrapper */
#define no_argument            0
#define required_argument      1
#define optional_argument      2
struct option
{
	const char *name;
	int has_arg;
	int *flag;
	int val;
};
extern char optarg[514];
int getopt_long_only (int ___argc, char *const *___argv, const char *__shortopts, const struct option *__longopts, int *__longind);

#endif
