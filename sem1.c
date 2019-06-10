/*
=====================================================================
Semaphores 1
---------------------------------------------------------------------
Δύο παίκτες (ανεξάρτητα threads) παίζουν σκάκι. Κάθε παίκτης παιζει
με τη σειρά του. Πρώτα πρέπει να παίξει ο λευκός. Ο συγχρονισμός
γίνεται με σημαφόρους.
Δουλεύει σωστά σε όλες τις περιπτώσεις;;;; Αν ναι δουλεύει αποδοτικά;;;; 
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
int NextMove;


int main (int argc, char **argv)
{
    pthread_t WhiteP, BlackP;
    NextMove = 1;
    sem_init (&Sem1, 0, 1);
    pthread_create (&WhiteP, NULL, WhiteFunc, NULL);
    pthread_create (&BlackP, NULL, BlackFunc, NULL);
    pthread_join (WhiteP, NULL);
    pthread_join (BlackP, NULL);
    printf ("Το παιχνίδι ολοκληρώθηκε....\n");
    return 0;
}

void *WhiteFunc (void * D)
{
    while (NextMove <= 500)
    {
        sem_wait (&Sem1);
        //if (NextMove % 2 == 1)
        //{
            printf ("White: I made my move (%d)\n", NextMove);
            NextMove ++;
        //}
        //else
        //    printf ("White: Not My turn (%d)\n", NextMove);
        sem_post (&Sem1);
    }
}

void *BlackFunc (void * D)
{
    while (NextMove <= 500)
    {
        sem_wait (&Sem1);
        //if (NextMove % 2 == 0)
        //{
            printf ("Black: I made my move (%d)\n", NextMove);
            NextMove ++;
        //}
        //else
        //    printf ("Black: Not My turn (%d)\n", NextMove);
        sem_post (&Sem1);
    }
}
    