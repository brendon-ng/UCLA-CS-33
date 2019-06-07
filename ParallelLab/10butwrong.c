//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Brendon Ng
 * UCLA ID : 304-925-492
 * Email : brendonn8@ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i, j, k;
  int u, v, w;
  long aggregate=1.0;
  long gimmie_the_func_var = gimmie_the_func();
  long we_need_the_func_var = we_need_the_func();
  long sum = 0.0;
  int DIM2 = DIM*DIM;
  int iDIM2, jDIM, index;
  iDIM2 = DIM2;

#pragma omp parallel for firstprivate(iDIM2) private(index,jDIM) reduction(+:sum)
  for (i=1; i<DIM-1; i++) {
    jDIM = DIM;
    for (j=1; j<DIM-1; j++) {
      index = iDIM2 + jDIM;
      for (k=1; k<DIM-1; k++) {
        sum+= old[index+k] * we_need_the_func_var/gimmie_the_func_var;
      }
      jDIM += DIM;
    }
    iDIM2 += DIM2;
  }
 
  aggregate += sum;

  printf("AGGR:%ld\n",aggregate);

  int  uDIM2, vDIM;
  iDIM2 = DIM2;
  int negDIM = -1*DIM;
  int negDIM2 = negDIM*DIM;
  
#pragma omp parallel for
  for (i=1; i<DIM-1; i++) {
    jDIM = DIM;
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        int sum = 0;
	uDIM2 = negDIM2;
        for (u=-1; u<=1; u++) {
	  vDIM = negDIM;
          for (v=-1; v<=1; v++) {
            for (w=-1; w<=1; w++) {
               sum+=old[iDIM2+uDIM2+jDIM+vDIM+(k+w)];
            }
	    vDIM += DIM;
          }
	  uDIM2 += DIM2;
        }	
        new[iDIM2+jDIM+k] = sum / 27;
      }
      jDIM += DIM;
    }
    iDIM2 += DIM2;
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
