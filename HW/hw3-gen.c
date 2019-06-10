#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define filename "hw3-input"
#define cf_upper_limit 100

int main (int argc, char **argv)
{
    FILE * fp;
    int p,n,i;

    if (argc != 3)
    {
        printf ("Syntax: hw3-gen <p: threads> <n: coefficients>\n");
        printf ("e.g hw3-gen 8 10000000\n");
        exit (1);
    }
    p = atoi (argv[1]);
    n = atoi (argv[2]);
    
    fp = fopen (filename,"w");
    
    fprintf(fp, "%d\n%d\n",p,n);

    for(i = 0; i < n;i++){
        fprintf (fp, "%d\n",(rand() % (cf_upper_limit)));
    }
    
    /* close the file*/  
    fclose (fp);
    return 0;

}
            