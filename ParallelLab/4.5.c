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
  long compute_it;
  long func = we_need_the_func();
  long gimmie = gimmie_the_func();
  long aggregate=1.0;
  int jDIM, iDIM2,index;
  int DIM2 = DIM*DIM;
  iDIM2 = DIM*DIM;
  long sum;

#pragma parallel for private(j,k,iDIM2,index, sum) 
  for (i=1; i<DIM-1; i++) {
    jDIM = DIM;
    sum=0;
    for (j=1; j<DIM-1; j++) {
      index = iDIM2 + jDIM;
      for (k=1; k<DIM-1; k++) {
        sum+= old[index+k] * func / gimmie;
      }
      jDIM += DIM;
    }
    iDIM2 += DIM2;
#pragma omp critical
    aggregate += sum;
  }


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

#pragma omp parallel for private(j,k,u) reduction(+:histogrammy)
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
