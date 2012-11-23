/* src/await-del.c: await util

    Copyright 2012 Josef Eisl <zapster@zapster.cc>

    This file is part of await.

    await is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    await is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with await.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <semaphore.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

const char* arg0 = NULL;

inline static void usage()
{
  fprintf(stderr, "usage: %s <semname>\n", arg0);
}

int main(int argc, char * argv[])
{
  char* semname;
  size_t len;
  
  arg0 = argv[0];

  if (argc != 2) 
  {
    usage();
    return -1;
  }

  len = sizeof(char) + strlen(argv[1]) + sizeof(char);
  semname = (char*) malloc(len);
  /* TODO: check for error */
  semname[0] = '/';
  strcat(semname,argv[1]);
  /* TODO: check for error */

  if (sem_unlink(semname) == -1)
  {
    fprintf(stderr,"%s: %s\n", arg0, strerror(errno));
    return -1;
  }

  return 0; 
}

