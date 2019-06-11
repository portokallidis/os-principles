//################################################################################
//Πρώτο Παράδειγμα με Fork
//--------------------------------------------------------------------------------
//Δημιουργεί μία διεργασία παιδί. 
//Οι δύο διεργασίες τελειώνουν μετά από λίγα δευτερόλεπτα.
//================================================================================
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int child;
    printf ("Hello. I am the Father. My Id Number is : %d \n", getpid ());
    child = fork ();
    if (child > 0)
    {
        printf ("Father: I will do something for 20 seconds\n");
        sleep (20);
        printf ("Father: Bye Bye\n");
    }
    else
    {
        printf ("Hello. I am the Child. My Id Number is : %d \n", getpid ());
        printf ("Child: My Father's id is %d\n", getppid ());
        printf ("Child: I will do something for 10 seconds\n");
        sleep (10);
        printf ("Child: Bye Bye\n");
    }
}