#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define filename "hw3-input"

clock_t start, end;
double cpu_time_used;

int main (int argc, char **argv)
{
    FILE * fp;
    int* cf;
    int p;
    unsigned long i = 0;
    unsigned long n = 0;
    unsigned long sum = 0;
    
    /* open the file for writing*/
    fp = fopen (filename,"r");

    fscanf(fp, "%d", &p);
    fscanf(fp, "%lu", &n);
    
    cf = malloc(n*sizeof(int));

    printf("p threads: %d, n coefficients: %lu \n",p,n);

    for(i = 0; i < n;i++){
        fscanf(fp,"%d",&cf[i]);
    }


    start = clock();
    // do sum
    for(i = 0; i < n;i++){
        sum+=cf[i]*cf[i];
    }
    // end of sum

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("timing: %f \n",cpu_time_used);

    printf("Total sum: %lu\n",sum);
    
    /* close the file*/  
    fclose (fp);
    return 0;

}
            