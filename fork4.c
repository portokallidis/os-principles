//################################################################################
//fork4.c
//2o Παράδειγμα με Fork και wait. 
//--------------------------------------------------------------------------------
//Η αρχική διεργασία δημιουργεί πέντε διεργασίες παιδιά. 
//Περιμένει τον τερμιατισμό της κάθε διεργασίας παιδί με τη σειρά που τις 
//δημιούργησε. Στη συνέχεια μετατρέπεται σε εντολή ls (ls -l). 
//Κάθε παιδί καθυστερεί (μέσω sleep) για ένα τυχαίο χρονικό διάστημα.
//Θα μπορούσε κάθε διεργασία να τυπώσει το pid των... αδελφών της ή να ξέρει την
//σειρά της (αν δημιουργήθηκε ως 1ο ή 2ο ή... παιδί);
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
    int ChIds[5];
    
    InitPID = getpid ();
    for (i = 0; i < 5; i++)
    {
        id = fork ();
        if (id == 0)
            break;
        ChIds[i] = id;
    }
    if (getpid () != InitPID)
        DoChild ();
    else
        DoFather (ChIds);
}

void DoChild ()
{
    srand (getpid ());
    int R = rand () % 16 + 10;
    printf ("I am child with pid: %d and i will sleep for %d seconds\n", getpid (), R);
    sleep (R);
    printf ("Child with pid: %d terminated\n", getpid ());
}

void DoFather (int ChIds[])
{
    int i;
    int t;
    printf ("Father: I have the following kids: ");
    for (i = 0; i < 5; i++)
        printf ("%d, ", ChIds[i]);
    printf ("\n");
    for (i = 0; i < 5; i++)
    {
        t = waitpid (ChIds[i], NULL, 0);
        printf ("Father: Child %d with id %d terminated.\n", i + 1, t);
    }
    printf ("Father: All Children terminated. Let us list directory files");
    char *Par[3];
    Par[0] = "ls";
    Par[1] = "-l";
    Par[2] = NULL;
    execvp ("ls", Par);
}