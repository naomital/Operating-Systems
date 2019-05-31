// C program to demonstrate use of fork() and pipe()  
//basit on https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include "md5.h"
# include <signal.h>
bool flag = false;
pid_t p; 
char concat_str[33]; 
void handle_sigint(int sig) {
    printf("is in ");
if(strlen(concat_str)==32){
    flag= true;

}else{
    printf("%zu  ",strlen(concat_str));  
}
}
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  // input number from user
    char input_str[20] =""; 
    printf("enter a number");
    for (size_t i = 0; i < 20; i++)
    {
       input_str[i]= getchar();
    }
    //char input_str[100]; 
    
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
          if(signal(SIGTERM, handle_sigint)== SIG_ERR){
             printf("signal error");
         }
  
        close(fd1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(fd2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close 
        // reading end. 
        read(fd2[0], concat_str, 32); 
                close(fd2[0]); 
                

        if(flag){
         printf("Concatenated string %s\n", concat_str); 
        kill(p, SIGKILL);       
         }
    } 
  
    // child process 
    else
    { 
         close(fd1[1]);  // Close writing end of first pipe 
  
         // Read a string using first pipe 
         char concat_str[20]; 
         read(fd1[0], concat_str, 20); 
         std::string str = md5(concat_str);
  
         // Close both reading ends 
        close(fd1[0]); 
         close(fd2[0]); 
  
         // Write concatenated string and close writing end 
         write(fd2[1], str.c_str(), 32); 
        close(fd2[1]); 
            sleep(10);
        kill(getppid(),SIGTERM);
       

  
        exit(0); 
    } 
}

