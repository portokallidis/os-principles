#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define filename "hw3-input"

clock_t start, end;
double cpu_time_used;

pthread_mutex_t mutex1;

typedef struct {
  unsigned long i;
  unsigned long start_index;
  unsigned long end_index;
} tw_input;

// global vars for simplicity
unsigned long sum = 0;
int *cf;

void *thread_worker( void *param)
{
    unsigned long partial_sum = 0;
    /* Cast the args into a meaningful pointer type that we can use */
    tw_input *s = (tw_input *) param;

    for (unsigned long i=s->start_index; i<s->end_index; i++) {
        partial_sum +=  cf[i]*cf[i]; 
    }
    // printf("Thread %d (%d - %d) => %d\n",s->i,s->start_index,s->end_index,partial_sum);

    // critical area - update sum variable
    pthread_mutex_lock(&mutex1);
    sum += partial_sum;
    pthread_mutex_unlock(&mutex1);
    return 0;
}

int main (int argc, char **argv)
{
    FILE * fp;
    int p;
    unsigned long n,i;

    /* open the file for writing*/
    fp = fopen (filename,"r");

    fscanf(fp, "%d", &p);
    fscanf(fp, "%lu", &n);
    
    cf = (int *) malloc(n*sizeof(int));
    if(cf == NULL)
    {
        printf("Memory allocation failed");
        exit(1); // exit the program
    }

    printf("p threads: %d, n coefficients: %lu \n",p,n);

    for(i = 0; i < n;i++){
        fscanf(fp,"%d",&cf[i]);
    }
    start = clock();

    // cf[n] is loaded with the coefficients 
    pthread_mutex_init(&mutex1, NULL);
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*p); 
    tw_input *thread_input = (tw_input*)malloc(sizeof(tw_input)*p); 
    // calculate thread start-end indices
    int a,b;
    for (i = 0; i < p ; i++) {
        a = i*(n/p);
        b = i+1==p?n:(i+1)*(n/p);
        (thread_input+i)->i = i;
        (thread_input+i)->start_index = a;
        (thread_input+i)->end_index = b;
        pthread_create((threads+i) , NULL, thread_worker, (void*)(thread_input+i));
        // pthread_create(&threads[i] , NULL, thread_worker, (void*)(thread_input+i));
    }

    for (i = 0; i < p ; i++) {
        pthread_join(threads[i] , NULL);
    }



    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("timing: %f \n",cpu_time_used);

    printf("Total sum: %lu\n",sum);
    
    /* close the file*/  
    fclose (fp);
    return 0;

}
            