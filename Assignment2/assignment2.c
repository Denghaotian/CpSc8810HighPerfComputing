#include <pthread.h>
#include <stdio.h>
#include <assert.h>

const size_t NUMTHREADS = 3; //nubmer of threads

int done =0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex signal
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;    

void* ThreadEntry(void* id)   //aceess threads
{
    const int myid = (long)id;

    const int workloops = 5;
    int i;
    for ( i=0; i<workloops; i++)
    {
        sleep(1);
    }

    pthread_mutex_lock(&mutex); //lock mutex

    done ++;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);  //unlock mutex

    return NULL;
}

int main (int argc, char** argc)
{
    pthread_t threads[NUMTHREADS]; // declare threads ID

    int t;
    for(t=0; t<NUMTHREADS; t++)
      pthread_create( &threads[t],NULL,ThreadEntry,(void*)(long)t );

    pthread_mutex_lock( &mutex );

    while( done < NUMTHREADS )
    {
        pthread_cond_wait (& cond, & mutex );
    }

    pthread_mutex_unlock( &mutex );

    return 0;
}
