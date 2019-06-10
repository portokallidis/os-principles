//################################################################################
//fork3.c
//1o Παράδειγμα με Fork και wait. 
//--------------------------------------------------------------------------------
//Η αρχική διεργασία δημιουργεί τρεις διεργασίες παιδιά. 
//Περιμένει να τελειώσουν και οι τρεις διεργασίες και στη συνέχεια 
//μετατρέπεται σε εντολή ls (ls -l). Κάθε παιδί καθυστερεί (μέσω sleep) για ένα
//τυχαίο χρονικό διάστημα.
//Μπορείτε να ορίσετε τον χρόνο που θα κοιμηθεί κάθε ένα από τα παιδιά;
//================================================================================
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void DoChild ();
void DoFather ();


int main (int argc, char **argv)
{
    int id;
    int InitPID;
    int i;
    
    InitPID = getpid ();
    for (i = 0; i < 3; i++)
    {
        fork ();
        if (getpid () != InitPID )
            break;
    }
    if (getpid () != InitPID)
        DoChild ();
    else
        DoFather ();
}

void DoChild ()
{
    srand (getpid ());
    int R = rand () % 11;
    printf ("I am child with pid: %d and i will sleep for %d seconds\n", getpid (), R);
    sleep (R);
    printf ("Child with pid: %d terminated\n", getpid ());
}

void DoFather ()
{
    int i;
    int t;
    printf ("Father: Waiting children to terminate...\n");
    for (i = 0; i < 3; i++)
    {
        t = wait (NULL);
        printf ("Father: Child with id %d terminated.\n", t);
    }
    printf ("Father: All Children terminated. Let us list directory files");
    execlp ("ps", "ps" ,"-o" ,"s", NULL);
}