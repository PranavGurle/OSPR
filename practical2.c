#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int a[20], n, i, j, temp;
    pid_t pid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i<n; i++)
        {
            scanf("%d", &a[i]);
            
        }
    pid = fork();

    if(pid == 0){

        printf("\nChild process sorting in ascending order: \n");

        for(i=0; i<n; i++){
            for(j=0; j<n-i-1; j++){

                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1]= temp;
                }
            }
        }
        for(i =0; i<n; i++){
            printf("%d", a[i]);
        }
            printf("\nchild process completed:\n");
            
        
    }
        else if(pid > 0)
         {
        wait(NULL);

        printf("\nParent process sorting in descending order:\n");

        for(i = 0; i< n; i++){
            for(j=0; j<n-i-1; j++){
                if(a[j]<a[j+1])
                {
                    temp= a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                    
                }
            }
        }
        for(i = 0; i<n; i++){
            printf("%d", a[i]);
        }
            printf("\nParent process completed.\n");
            
        
         }
        else
    {
        printf("\nFork is failde\n");
    }

      return 0;

        
    }
        
    
        
