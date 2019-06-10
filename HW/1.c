#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int pid1,pid2,pid3,pid4;
    int p0;
    char sp0[10];
    p0 = getpid();
    sprintf(sp0,"%d",p0);
    printf ("Hello. I am the Father. My Id Number is : %d \n", p0);
    pid1 = fork ();
    if (pid1 > 0)
    {
        pid2 = fork();
        pid3 = fork();
        if(pid2>0 && pid3>0) {
            printf ("Father: My children are : %d,%d, %d \n",pid1,pid2,pid3);
            sleep(1);
        }
    }
    else
    {
        printf ("Hello. I am the pid1 child. My Id Number is : %d \n", getpid ());
        printf ("I will create one child:\n");
        pid4=fork();
        if(pid4>0) {
            printf("My child is %d\n",pid4);
            execlp("pstree","pstree","-p",sp0,NULL);
        }
    }
    
}