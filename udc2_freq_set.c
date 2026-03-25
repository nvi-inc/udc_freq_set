/*
 * Copyright (c) 2026 NVI, Inc.
 *
 * This file is part of VLBI Field System
 * (see http://github.com/nvi-inc/fs).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "/usr2/fs/include/params.h"
#include "/usr2/fs/include/fs_types.h"
#include "/usr2/fs/include/fscom.h"

extern struct fscom *shm_addr;

static int ip[5] = { 0, 0, 0, 0, 0};

int main(int argc, char **argv)
{
  int i;
  char number[17];
  char command[128];

  setup_ids();

  if (nsem_test("fs   ") != 1) {
    printf("fs isn't running\n");
    exit(-1);
  }

  for(i=0;i<MAX_LO;i++) {
    if(shm_addr->lo.lo[i]<0.0 || 1==i%2 && shm_addr->lo.lo[i-1]>=0.0)
      continue;
    snprintf(number,sizeof(number),"%lf",shm_addr->lo.lo[i]);
    int len=strlen(number);
    while(len-->0 && '0' == number[len])
      number[len]=0;
    if(len>=0 && '.'==number[len])
      number[len]=0;
    switch(i) {
      case 0:
      case 1:
	sprintf(command,"popen 's_client -t 2 -h udca -c udc_lo=%s 2>&1' -n udcca",number);
	break;
      case 2:
      case 3:
	sprintf(command,"popen 's_client -t 2 -h udcb -c udc_lo=%s 2>&1' -n udccb",number);
	break;
      case 4:
      case 5:
	sprintf(command,"popen 's_client -t 2 -h udcc -c udc_lo=%s 2>&1' -n udccc",number);
	break;
      case 6:
      case 7:
	sprintf(command,"popen 's_client -t 2 -h udcd -c udc_lo=%s 2>&1' -n udccd",number);
	break;
      default:
        continue;
	break;
    }
    printf("%s\n",command);
    system(command);
  }
  return (0);  /* ok termination */
}
