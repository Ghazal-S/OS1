#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include<time.h>

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
/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) 
{ 
   int i, key, j; 
   for (i = 1; i < n; i++) 
   { 
       key = arr[i]; 
       j = i-1; 
  
       /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
       } 
       arr[j+1] = key; 
   } 
} 

// creating random array of size len

void arrayCreator(int a[] , int len) 
{ 
   
    int i; 
    for (i=0; i<len; i++) 
        a[i] = rand(); 
    return; 
} 
  //recursive function
  void mergeSort(int a[],int l, int h , int m) 
{ 
    int i;
    int len=(h-l+1); 
  
   // Using insertion sort for small sized array 
    if (len<=m) 
    { 
        insertionSort(a+l, len); 
        return; 
    } 
  
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
        mergeSort(a,l,l+len/2-1,m); 
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
            mergeSort(a,l+len/2,h,m); 
            _exit(0); 
        } 
    } 
  
    int status; 
  
    // Wait for child processes to finish 
    waitpid(left, &status, 0); 
    waitpid(right, &status, 0); 
  
    // Merge the sorted subarrays(right and left) 
    merge(a, l, l+len/2-1, h); 
}


int main() 
{ 

int length = 1000;
int shmid; 
    key_t key = IPC_PRIVATE; 
    int *shm_array; 

    // Calculate segment length 
    size_t SHM_SIZE = sizeof(int)*length; 
  
    // Create the segment. 
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) 
    { 
        perror("shmget"); 
        _exit(1); 
    } 
  
    // Now we attach the segment to our data space. 
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1) 
    { 
        perror("shmat"); 
        _exit(1); 
    } 
  
    // Create a random array of given length 
    srand(time(NULL)); 
    arrayCreator(shm_array, length); 
	double total_time;
	clock_t start, end;
	start = clock();
	mergeSort(shm_array , 0 , 999 , 30);
	end = clock();
	total_time = ((double) (end - start)) /  CLOCKS_PER_SEC;
	printf("run_time :  %f \n", total_time);
	int i; 
	printf("Sorted Array : \n");
	    for (i=0; i<length; i++) 
	    { 
		     
		     printf("%d \n ", shm_array[i]);
	    }
	

return 0;
}
