//
// CPSC 8810 High-Performance Computing for Power System Modeling and Simulation
// Name: Haotian Deng
// Date: Feb 7, 2020
// Assignment 1
//


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include <time.h>

void main(int argc, char *argv[])
{
     int i, count, nthreads, threshold_omp;
     double x, y;
     int samples;
     double pi,start;
     unsigned int seedp;
    

      threshold_omp=100;
      count=0;
      samples = atoi(argv[1]);
      //samples =100;
      nthreads = atoi(argv[2]);
      //nthreads =16;
      printf("samples size=%d, nthread=%d\n", samples, nthreads);
      omp_set_num_threads(nthreads);
      start = omp_get_wtime();
    
    #pragma omp parallel if (samples > threshold_omp) default(none) shared(samples) private(i,seedp,x,y) reduction(+:count)
    {
      
      seedp= 4*(omp_get_thread_num()+1)+199;
      printf("seedp=%d\n",seedp);
      
    #pragma omp for
        for (i = 0; i < samples; i++){
         //srand ((unsigned) time (NULL));
         //seedp = (unsigned) time (NULL);
         x = (double) rand_r(&seedp) / RAND_MAX;
         y = (double) rand_r(&seedp) / RAND_MAX;
         //srand(i+1);
         //x = (double) rand() / RAND_MAX;
         //y = (double) rand() / RAND_MAX;
         if (x*x + y*y <= 1)
         count= count+1;
       }
    } 

     double end = omp_get_wtime();
     printf("elapsed time: %.16g\n", end - start);

     pi = 4.0 * (double) count/(double)samples;
     printf("Count = %d, Samples = %d, Estimate of pi = %7.5f\n", count, samples, pi); 
    
 }
