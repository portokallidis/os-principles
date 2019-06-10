//################################################################################
//fork2.c
//Δεύτερο Παράδειγμα με Fork. 
//--------------------------------------------------------------------------------
//Δημιουργεί μία διεργασία παιδί. 
//Οι δύο διεργασίες "κοιμούνται" για λίγα δευτερόλεπτα.
//Ο χρόνος που κοιμάται η κάθε διεργασία δίδεται παραμετρικά στη γραμμή εντολών.
//Με την χρήση της εντολής ps δείτε τι συμβαίνει όταν τελειώνει πρώτη η διεργαία
//"πατέρας" και όταν τελειώνει πρώτη η διεργασία "παιδί"
//================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int child;
    int t1, t2;
    if (argc != 3)
    {
        printf ("Syntax: fork2 <sleep time 1> <sleep time 2>\n");
        exit (1);
    }
    t1 = atoi (argv[1]);
    t2 = atoi (argv[2]);
    printf ("Hello. I am the Father. My Id Number is : %d \n", getpid ());
    child = fork ();
    if (child > 0)
    {
        printf ("Father: I will do something for %d seconds\n", t1);
        sleep (t1);
        printf ("Father: Bye Bye\n");
    }
    else
    {
        printf ("Hello. I am the Child. My Id Number is : %d \n", getpid ());
        printf ("Child: My Father's id is %d\n", getppid ());
        printf ("Child: I will do something for %d seconds\n", t2);
        sleep (t2);
        printf ("Child: Bye Bye\n");
    }
}
            