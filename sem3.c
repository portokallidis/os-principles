/*
=====================================================================
Semaphores 3
---------------------------------------------------------------------
Δύο παίκτες (ανεξάρτητα threads) παίζουν σκάκι. Κάθε παίκτης παιζει
με τη σειρά του. Πρώτα πρέπει να παίξει ο λευκός. Το παιχνίδι πρέπει
να τελειώσει μόλις ολοκληρωθεί και η 50η κίνηση.
Ο συγχρονισμός γίνεται με σημαφόρους.
Μπορείτε να το επεκτείνετε για Ν παίκτες;;; 
=====================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>


void *playerFunc (void *);

//--------------------------------------------------------------
//Ολικές Μεταβλητές
//Κακή προγραμματιστική τακτική, αλλά βοηθάει στην κατανόηση
//του παραδείγματος μειώνοντας τους... περίεργους pointers
//--------------------------------------------------------------

int NextMove;
int NextPlayer;

#define N (10)

sem_t mutex;
int hasPlayed[N];

int main (int argc, char **argv)
{
    NextMove = 1;
    NextPlayer = 0;
    pthread_t ids[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)  {
        pthread_create (&ids[i], NULL, playerFunc,(void *) (intptr_t) i);

        hasPlayed[i] = 0;
    }
    for (int i = 0; i < N; i++)  {
        pthread_join (ids[i], NULL);
    }
        
    printf ("Το παιχνίδι ολοκληρώθηκε....\n");
    return 0;
}

void *playerFunc (void * param)
{   int id = (intptr_t) param;
    int flag = 0;
    do
    {
        sem_wait (&mutex);
            if (NextMove <= 50)
            {
                if(id==NextPlayer%N) {
                    printf ("Player (%d): I made my move (%d)\n", id+1, NextMove);
                    NextMove++;
                    NextPlayer++;
                }
            }
            else
                flag = 1;

        sem_post (&mutex);

    }
    while (!flag);
}
