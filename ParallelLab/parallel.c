//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Brendon
 * UCLA ID : 304-924-492
 * Email : brendonn8@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i, j, k;
  int u, v, w;
  long compute_it;
  long aggregate=1.0;
  long gimmie = gimmie_the_func();
  long func = we_need_the_func();
  int index;
#pragma omp parallel for private(index,j,k,u,v,w,compute_it) reduction(+:aggregate,histogrammy)  
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      index = i*DIM*DIM+j*DIM;
      for (k=1; k<DIM-1; k++) {
        compute_it = old[index+k] * func;
        aggregate+= compute_it / gimmie;

        u=(new[index+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;

        new[index+k]=0;
        for (u=-1; u<=1; u++) {
          for (v=-1; v<=1; v++) {
            for (w=-1; w<=1; w++) {
               new[index+k]+=old[u*DIM*DIM+v*DIM+(k+w)+index];
            }
          }
        }
        new[index+k]/=27;
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);

}
