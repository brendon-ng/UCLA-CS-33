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
  int DIM2= DIM*DIM;

  int jDIM;


#pragma omp parallel for private(jDIM,index,j,k,u,v,w,compute_it) reduction(+:aggregate,histogrammy)  
  for (i=1; i<DIM-1; i++) {
    jDIM = DIM;
    for (j=1; j<DIM-1; j++) {
      index = i*DIM2+jDIM;
      for (k=1; k<DIM-1; k++) {
        compute_it = old[index+k] * func;
        aggregate+= compute_it / gimmie;

        u=(new[index+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;

        new[index+k]=0;
	int uDIM2 = -1*DIM2;
        for (u=-1; u<=1; u++) {
	  int vDIM = -1*DIM;
          for (v=-1; v<=1; v++) {
            for (w=-1; w<=1; w++) {
               new[index+k]+=old[uDIM2+vDIM+(k+w)+index];
            }
	    vDIM += DIM;
          }
	  uDIM2 += DIM2;
        }
        new[index+k]/=27;
      }
      jDIM+=DIM;
    }

   
  }

  printf("AGGR:%ld\n",aggregate);

}
