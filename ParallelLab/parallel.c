//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name :
 * UCLA ID : 
 * Email :
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
  long we = we_need_the_func();
  long DIM2 = DIM * DIM;
  
  for (i=DIM2; i<DIM-1; i=i+DIM2) {
    for (j=DIM; j<DIM-1; j=j+DIM) {
      for (k=1; k<DIM-1; k++) {
        compute_it = old[i+j+k];
        aggregate+= compute_it +4942;
      }
    }
  }
  aggregate = aggregate * (we/gimmie);

  printf("AGGR:%ld\n",aggregate);
  
  int iDIM = DIM2;
  int jDIM = DIM;
  for (i=DIM2; i<DIM-1; i=i+DIM2) {
    for (j=DIM; j<DIM-1; j=j+DIM) {
      for (k=1; k<DIM-1; k++) {
        new[i+j+k]=0;
        for (u=-1*DIM2; u<=1; u=u+DIM2) {
          for (v=-1*DIM; v<=1; v=v+DIM) {
            for (w=-1; w<=1; w++) {
               new[i+j+k]+=old[i+u+j+v+(k+w)];
            }
          }
        }
        new[i+j+k]/=27;
      }
    }
  }

  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
    }

}
