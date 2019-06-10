
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <string.h>


void *playerFunc (void *);

//--------------------------------------------------------------
//Ολικές Μεταβλητές
//Κακή προγραμματιστική τακτική, αλλά βοηθάει στην κατανόηση
//του παραδείγματος μειώνοντας τους... περίεργους pointers
//--------------------------------------------------------------

int NextMove;
int NextThread;

#define N (3)
#define TOTAL (30)

sem_t mutex;
int hasPlayed[N];

int main (int argc, char **argv)
{
    NextMove = 1;
    NextThread = 0;
    pthread_t ids[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)  {
        pthread_create (&ids[i], NULL, playerFunc,(void *) (intptr_t) i);

        hasPlayed[i] = 0;
    }
    for (int i = 0; i < N; i++)  {
        pthread_join (ids[i], NULL);
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

void *playerFunc (void * param)
{   int id = (intptr_t) param;
    int flag = 0;
    do
    {
        sem_wait (&mutex);
            if (NextMove <= TOTAL)
            {
                if(id==NextThread%N) {
                    printf ("%d# => Thread (%d): %s\n",NextMove, id+1, showMessage(id+1));
                    NextMove++;
                    NextThread++;
                }
            }
            else
                flag = 1;

        sem_post (&mutex);

    }
    while (!flag);
}