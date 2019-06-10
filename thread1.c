/*
=====================================================================
Thread 1
---------------------------------------------------------------------
Δημιουργεί ένα thread το οποίο τυπώνει τους αριθμούς από το 1 ως το
20.
Δοκιμάστε να βάλετε σε σχόλιο την sleep της main
=====================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *tfunc1 (void *);

int main (int argc, char **argv)
{
    pthread_t thr1;
    int r;
    r = pthread_create (&thr1, NULL, tfunc1, NULL);
    if (r)
    {
        printf ("Πρόβλημα κατά τη δημιουργία thread\n");
        exit (1);
    }
    else
        printf ("Δημιουργήθηκε thread με ID: %lu\n", thr1);
    
    sleep (30);
    
}

void *tfunc1 (void *p)
{
    int i;
    for (i = 1; i <= 20; i++)
    {
        printf ("%d\n", i);
        sleep (1);
    }
}
    