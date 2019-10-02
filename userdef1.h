#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include "global.h"
#include<unistd.h>
#include<string.h>
// #include "global.h"
#include <sys/utsname.h>
#include "my_utilities.h"        // MY OBSERVATIONS ON THE NATURE OF INCLUDE: <> can be included multiple times. User defined cant. if 2 files use a common file say
                                // util.h and util.c . U can circumvent repition problem: in 1st, rewrite what is needed for .c to work, from .h. Don t include .h in 1st. Include in 2nd.
#define MAX 1001
#define LIST_MAX 2000