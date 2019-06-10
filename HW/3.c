#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void father ();
void child2 ();
void child2Children ();

int main (int argc, char **argv)
{
    int pid1,pid2;
    int i,id,chIds[3];
    int p0 = getpid();
    printf ("Main with pid: %d \n", p0);
    pid1 = fork ();
    if (pid1 > 0)
    {   
        // Child 1
        pid2 = fork();
        if(pid2>0) {
            // father
            father(pid2);            
        }
        else {
            printf("Child2 with pid: %d and ppid: %d\n", getpid(), p0);
            child2();
        }
    } else {
        printf("Child1 with pid: %d and ppid: %d\n",getpid(), p0);
    } 
    
}


void father(int childPid){
    waitpid(childPid,NULL,0);
    execlp("ps","ps",NULL);
}

void child2 () {
    int pid2 = getpid();
    int chIds[3];
    // create 3 children
    for (int i = 0; i < 3; i++)
    {
        int id = fork ();
        if (id == 0) {
            child2Children(pid2,i);
            break;
        }
        chIds[i] = id;
    }
    if(getpid()==pid2) {
        wait(NULL);
    }
}

void child2Children(int ppid, int i){
    printf("Child #%d of Child2 with pid: %d and ppid: %d\n",i, getpid(),ppid);
}