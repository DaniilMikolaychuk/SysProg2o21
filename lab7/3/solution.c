#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


sig_atomic_t Exit = 0;


void Handler(int sigNum)
{
    static int count[2] = { 0 };
    if(sigNum == SIGUSR1)
    {
        count[0]++;
    }
    else if(sigNum == SIGUSR2)
    {
        count[1]++;
    }
    else if(SIGTERM)
    {
        printf("%d %d\n", count[0], count[1]);
        Exit = 1;
    } 
}


int main () 
{
   signal(SIGUSR1, Handler);
   signal(SIGUSR2, Handler);
   signal(SIGTERM, Handler);
   
   while(Exit == 0)
   {
      sleep(100);
   }
   return(0);
}
