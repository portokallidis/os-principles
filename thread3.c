/*
=====================================================================
Thread 3
---------------------------------------------------------------------
Δημιουργεί 3 threads μέσω των οποίων αυξάνεται η τιμή κάθε θέσης 
ενός πίνακα ακεραίων κατά 5. Κάθε thread αυξάνει ένα τμήμα του πίνακα.
Η εργασία ολοκληρώνεται γρηγορότερα με τα threads; 
=====================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

clock_t start, end;
double cpu_time_used;

struct ThreadData
{
    int ID;
    int *Mat;
    int From;
    int To;
};

void *tfunc1 (void *);
void CheckResult ();

int main (int argc, char **argv)
{

    start = clock();

    pthread_t thr1, thr2, thr3;
    struct ThreadData Dat1, Dat2, Dat3;
    int *Matrix;
    int r;
    Matrix = (int *) malloc (300000000 * sizeof (int));
    for (r = 0; r < 300000000; r++) 
        Matrix [r] = 0;
    Dat1.ID = 1;
    Dat1.Mat = Matrix;
    Dat1.From = 0;
    Dat1.To = 99999999;
    Dat2.ID = 2;
    Dat2.Mat = Matrix;
    Dat2.From = 100000000;
    Dat2.To = 199999999;
    Dat3.ID = 3;
    Dat3.Mat = Matrix;
    Dat3.From = 200000000;
    Dat3.To = 299999999;
    r = pthread_create (&thr1, NULL, tfunc1, &Dat1);
    r = pthread_create (&thr2, NULL, tfunc1, &Dat2);
    r = pthread_create (&thr3, NULL, tfunc1, &Dat3);
    pthread_join (thr1, NULL);
    pthread_join (thr2, NULL);
    pthread_join (thr3, NULL);

    int j;
    // for (r = 0; r < 300000000; r++) {
    //     for (j = 1; j <= 5; j++)
    //         Matrix [r] ++;

    // }

    CheckResult (Matrix);
}

void *tfunc1 (void *p)
{
    struct ThreadData *t;
    int i, j;
    t = (struct ThreadData *) p;
    for (i = t->From; i <= t->To; i++)
    {
        for (j = 1; j <= 5; j++)
            t->Mat[i] ++;
    }
}

void CheckResult (int *M)
{
    int i;
    for (i = 0; i <300000000; i++)
        if (M[i] != 5)
        {
            printf ("Error in Matrix Data: M[%d] = %d\n",i,M[i]);
            return ;
        }
    printf ("Matrix Ok!\n");

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("timing: %f \n",cpu_time_used);
}
    