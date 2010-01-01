/* AscNHalf */

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
