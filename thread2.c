/*
=====================================================================
Thread 2
---------------------------------------------------------------------
Δημιουργεί τρία threads (με το ίδιο κώδικα) τα οποία τυπώνουν τους 
αριθμούς από το 1 ως το 250.
Προσθέστε ένα μήνυμα μετά την κάθε pthread_join. Με ποια σειρά 
τελειώνουν τα threads; Γιατί το sleep στην tfunc1 φαίνεται να
συγχρονίζει τα threads
=====================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *tfunc1 (void *);

int main (int argc, char **argv)
{
    pthread_t thr1, thr2, thr3;
    int r;
    int val1, val2, val3;
    val1 = 1;
    val2 = 2;
    val3 = 3;
    r = pthread_create (&thr1, NULL, tfunc1, &val1);
    r = pthread_create (&thr2, NULL, tfunc1, &val2);
    r = pthread_create (&thr3, NULL, tfunc1, &val3);
    pthread_join (thr1, NULL);
    pthread_join (thr2, NULL);
    pthread_join (thr3, NULL);
    
}

void *tfunc1 (void *p)
{
    int id;
    int i;
    id = * (int *) p;
    for (i = 1; i <= 250; i++)
    {
        printf ("Thread %d: %d\n", id, i);
        sleep (1);
    }
}
    