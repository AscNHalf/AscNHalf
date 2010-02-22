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

#ifndef _COMMON_H
#define _COMMON_H

#define LIBMPQ_CONF_FL_INCREMENT	512			/* i hope we did not need more :) */
#define LIBMPQ_CONF_EXT			".conf"			/* listdb file seems to be valid with this extension */
#define LIBMPQ_CONF_HEADER		"LIBMPQ_VERSION"	/* listdb file must include this entry to be valid */
#define LIBMPQ_CONF_BUFSIZE		4096			/* maximum number of bytes a line in the file could contain */

#define LIBMPQ_CONF_TYPE_CHAR		1			/* value in config file is from type char */
#define LIBMPQ_CONF_TYPE_INT		2			/* value in config file is from type int */

#define LIBMPQ_CONF_EOPEN_DIR		-1			/* error on open directory */
#define LIBMPQ_CONF_EVALUE_NOT_FOUND	-2			/* value for the option was not found */

int libmpq_init_buffer(mpq_archive *mpq_a);
int libmpq_read_hashtable(mpq_archive *mpq_a);
int libmpq_read_blocktable(mpq_archive *mpq_a);
int libmpq_file_read_file(mpq_archive *mpq_a, mpq_file *mpq_f, unsigned int filepos, char *buffer, unsigned int toread);
int libmpq_read_listfile(mpq_archive *mpq_a, FILE *fp);

int libmpq_conf_get_value(FILE *fp, char *search_value, void *return_value, int type, int size);
char *libmpq_conf_delete_char(char *buf, char *chars);
int libmpq_conf_get_array(FILE *fp, char *search_value, char ***filelist, int *entries);
int libmpq_free_listfile(char **filelist);
int libmpq_read_listfile(mpq_archive *mpq_a, FILE *fp);

#endif
