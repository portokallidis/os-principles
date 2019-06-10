
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>


void *thread_worker (void *);

#define N (3)
#define TOTAL (30)

int next;


pthread_mutex_t mutex;
pthread_cond_t cond_var;

int main (int argc, char **argv)
{
    next = 0;
    pthread_t ids[N];

    pthread_cond_init(&cond_var,NULL);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N; i++)  {
        pthread_create (&ids[i], NULL, thread_worker,(void *) (intptr_t) i);
    }
    for (int i = 0; i < N; i++)  {
        if(pthread_join (ids[i], NULL)) {
            fprintf(stderr, "A thread failed to join\n");
        }
    }
        
    return 0;
}


const char * showMessage (int i){
    switch (i)
    {
    case 1:
        return "<ONE>";
        break;
    
    case 2:
        return "<TWO>";
        break;
    
    case 3:
        return "<THREE>";
        break;
    
    default:
        return "<ERROR>";
        break;
    }
}

void *thread_worker (void * param)
{   int id = (intptr_t) param;
    int flag = 0;
    do
    {

        pthread_mutex_lock(&mutex);
        while ( id!=next%N && next < TOTAL) {
            // fprintf (stderr,"!! %d# => Thread (%d): %s\n",next, id+1, showMessage(id+1));
            pthread_cond_wait(&cond_var,&mutex);
            pthread_cond_signal(&cond_var);
        }

        if(next < TOTAL) {
            fprintf (stderr,"%d# => Thread (%d): %s\n",next, id+1, showMessage(id+1));
            next++;
        }
        else {
            flag = 1;
            fprintf (stderr,"Thread (%d) finished\n",id+1);
        } 

        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);

    }
    while (!flag);
    return (void*)0;
}