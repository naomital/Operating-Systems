#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int ppid [5];
int befor = 3;
void sigCathcher(int sigin){
printf("PID %d caught one\n",getpid());
if(befor>=0){
kill(ppid[befor],SIGTERM);
}
befor--;
exit(0);
}
int main() 
{ 
    for(int i=0;i<5;i++) // loop will run n times (n=5) 
    { 
    int temp =fork();
    //printf("%d\n", temp);
        if( temp == 0) 
        { 
            printf("PID %d ready\n",getpid()); 
          if(signal(SIGTERM, sigCathcher)== SIG_ERR){
             printf("signal error");
         }
                      pause();
        }
     ppid[i]=temp;
    } 
       sleep(1);
      kill(ppid[4],SIGTERM);
      sleep(1);
if(getpid!=0){
for(int i=0;i<5;i++){
     sleep(1);
    kill(ppid[i],SIGKILL);
    printf("%d is dead\n",ppid[i]);
}
}

    return 0;
      
};
