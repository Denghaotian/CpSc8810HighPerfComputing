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
    printf("ThreadEntry_num:%ld\n",myid);
    const int workloops = 5;
    int i;
    for ( i=0; i<workloops; i++)
    {
        sleep(1);
       printf("sleep:%d\n",i);
    }
    printf("mutex_state_entry_before_lock:%d\n",mutex);
    pthread_mutex_lock(&mutex); //lock mutex

    printf("mutex_state_entry_after_lock:%d\n",mutex);
   
     done ++;
    printf("done:%d\n",done);

    pthread_cond_signal(&cond);
    printf("after_cond_signal,cond:%d mutex:%d\n",cond,mutex);
    pthread_mutex_unlock(&mutex);  //unlock mutex

    printf("after_mutex_unlock,cond:%d mutex:%d\n",cond,mutex);
    return NULL;
}

int main (int argc, char** argv)
{
    printf("-----------start--------------------\n");
    
    pthread_t threads[NUMTHREADS]; // declare threads ID
    printf("number of threads:%d\n",NUMTHREADS);
    
    int t;
    for(t=0; t<NUMTHREADS; t++)
    { 
      printf("create_num_threads:%d\n",t); 
      pthread_create( &threads[t],NULL,ThreadEntry,(void*)(long)t );
    }
    pthread_mutex_lock( &mutex );
    printf("mutex_state_mainfunction:%d\n",mutex);     

    while( done < NUMTHREADS )
    {
       printf("state_before_cond_waitfunction cond:%d mutex:%d\n",cond,mutex);
       pthread_cond_wait (& cond, & mutex );
       printf("state_after_cond_wait_function:cond:%d mutex:%d\n",cond,mutex);
    }

    pthread_mutex_unlock( &mutex );

    return 0;
}
