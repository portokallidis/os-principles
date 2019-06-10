#include <pthread.h>
#include <semaphore.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
  int n;
  int count;
  sem_t mutex;
  sem_t turnstile;
  sem_t turnstile2;
} barrier_t;

void init_barrier(barrier_t *barrier, int n)
{
  barrier->n = n;
  barrier->count = 0;
  sem_init(&barrier->mutex, 0, 1);
  sem_init(&barrier->turnstile, 0, 0);
  sem_init(&barrier->turnstile2, 0, 0);
}

void phase1_barrier(barrier_t *barrier)
{
  sem_wait(&barrier->mutex);
  if (++barrier->count == barrier->n) {
    int i;
    for (i = 0; i < barrier->n; i++) {
      sem_post(&barrier->turnstile);
    }
  }
  sem_post(&barrier->mutex);
  sem_wait(&barrier->turnstile);
}

void phase2_barrier(barrier_t *barrier)
{
  sem_wait(&barrier->mutex);
  if (--barrier->count == 0) {
    int i;
    for (i = 0; i < barrier->n; i++) {
      sem_post(&barrier->turnstile2);
    }
  }
  sem_post(&barrier->mutex);
  sem_wait(&barrier->turnstile2);
}

void wait_barrier(barrier_t *barrier)
{
  phase1_barrier(barrier);
  phase2_barrier(barrier);
}

#define NUM_THREADS 5

void *myThread(void *);

void *myThread(void *arg)
{
  barrier_t *barrier = arg;
  int i;
  int a;

  for (i = 0; i < 10; i++) {
    for (a = 0; a < 0.9*INT_MAX; a++);
    printf("this is %d iteration\n", i);
    wait_barrier(barrier);
  }

  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t threads[NUM_THREADS];
  barrier_t barrier;
  int i;

  init_barrier(&barrier, NUM_THREADS);

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, myThread, &barrier);
  }

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}