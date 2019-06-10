/*
=====================================================================
Semaphores 1
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

void *WhiteFunc (void *);
void *BlackFunc (void *);

//--------------------------------------------------------------
//Ολικές Μεταβλητές
//Κακή προγραμματιστική τακτική, αλλά βοηθάει στην κατανόηση
//του παραδείγματος μειώνοντας τους... περίεργους pointers
//--------------------------------------------------------------
sem_t Sem1;
sem_t Sem2;
int NextMove;


int main (int argc, char **argv)
{
    pthread_t WhiteP, BlackP;
    NextMove = 1;
    sem_init (&Sem1, 0, 1);
    sem_init (&Sem2, 0, 0);
    pthread_create (&WhiteP, NULL, WhiteFunc, NULL);
    pthread_create (&BlackP, NULL, BlackFunc, NULL);
    pthread_join (WhiteP, NULL);
    pthread_join (BlackP, NULL);
    printf ("Το παιχνίδι ολοκληρώθηκε....\n");
    return 0;
}

void *WhiteFunc (void * D)
{
    int flag = 0;
    do
    {
        sem_wait (&Sem1);
        if (NextMove <= 50)
        {
            printf ("White: I made my move (%d)\n", NextMove);
            NextMove ++;
        }
        else
            flag = 1;
        sem_post (&Sem2);
    }
    while (!flag);
}

void *BlackFunc (void * D)
{
    int flag = 0;
    do
    {
        sem_wait (&Sem2);
        if (NextMove <= 50)
        {
            printf ("Black: I made my move (%d)\n", NextMove);
            NextMove ++;
        }
        else
            flag = 1;
        sem_post (&Sem1);
    }
    while (!flag);
}