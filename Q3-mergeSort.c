#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

  //recursive function
  void mergeSort(int a[], int l, int h) 
{ 
    int i, len=(h-l+1); 
  
   
  
    pid_t lpid,rpid; 
    lpid = fork(); 
    if (lpid<0) 
    { 
        // Left child process not created 
        perror("Left Child Process not created\n"); 
        _exit(-1); 
    } 
       //Left child process created
    else if (lpid==0) 
    { 
        mergeSort(a,l,l+((len/2)-1)); 
        _exit(0); 
    } 
    else
    { 
        rpid = fork(); 
        if (rpid<0) 
        { 
            // Right child process not created 
            perror("Right Child Process not created\n"); 
            _exit(-1); 
        } 
	//Right child process created
        else if(rpid==0) 
        { 
            mergeSort(a,l+len/2,h); 
            _exit(0); 
        } 
    } 
  
    int status; 
  
    // Wait for child processes to finish 
    waitpid(lpid, &status, 0); 
    waitpid(rpid, &status, 0); 
  
    // Merge the sorted subarrays(right and left) 
    merge(a, l, l+((len/2)-1), h); 
} 
