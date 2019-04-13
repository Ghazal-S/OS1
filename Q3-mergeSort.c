#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 


// creating random array of size 1000

void arrayCreator(int a[1000] , 1000) 
{ 
   
    int i; 
    for (i=0; i<1000; i++) 
        a[i] = rand(); 
    return; 
} 
  //recursive function
  void mergeSort(int a[], 0, 999) 
{ 
    int i, len=1000; 
  
   
  
    pid_t left,right; 
    left = fork(); 
    if (left<0) 
    { 
        // Left child process not created 
        perror("Left Child Process not created\n"); 
        _exit(-1); 
    } 
       //Left child process created
    else if (left==0) 
    { 
        mergeSort(a,0,499)); 
        _exit(0); 
    } 
    else
    { 
        right = fork(); 
        if (right<0) 
        { 
            // Right child process not created 
            perror("Right Child Process not created\n"); 
            _exit(-1); 
        } 
	//Right child process created
        else if(right==0) 
        { 
            mergeSort(a,500,999); 
            _exit(0); 
        } 
    } 
  
    int status; 
  
    // Wait for child processes to finish 
    waitpid(left, &status, 0); 
    waitpid(right, &status, 0); 
  
    // Merge the sorted subarrays(right and left) 
    merge(a, 0, 499, 999); 
}

// function for merging 2 sorted subarrays 
void merge(int a[], int l1, int h1, int h2) 
{ 
    
    int count=h2-l1+1; 
    int sorted[count]; 
    int i=l1, k=h1+1, m=0; 
    while (i<=h1 && k<=h2) 
    { 
        if (a[i]<a[k]) 
            sorted[m++]=a[i++]; 
        else if (a[k]<a[i]) 
            sorted[m++]=a[k++]; 
        else if (a[i]==a[k]) 
        { 
            sorted[m++]=a[i++]; 
            sorted[m++]=a[k++]; 
        } 
    } 
  
    while (i<=h1) 
        sorted[m++]=a[i++]; 
  
    while (k<=h2) 
        sorted[m++]=a[k++]; 
  
    int arr_count = l1; 
    for (i=0; i<count; i++,l1++) 
        a[l1] = sorted[i]; 
}  

int main() 
{ 
int length = 1000;
int array[1000];
arrayCreator(array , 1000);
mergesort(array , 0 , 999);
int i; 
printf("Sorted Array : \n");
    for (i=0; i<len; i++) 
    { 
             
             printf("%d\n ", array[i]);
            
     
    } 
return 0;
}
