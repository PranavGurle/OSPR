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










//4th nd practical 


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t fork_sem[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);

    sem_wait(&room);

    sem_wait(&fork_sem[id]);
    printf("Philosopher %d picked left fork\n", id);

    sem_wait(&fork_sem[(id + 1) % N]);
    printf("Philosopher %d picked right fork\n", id);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&fork_sem[id]);
    sem_post(&fork_sem[(id + 1) % N]);

    sem_post(&room);

    printf("Philosopher %d finished eating\n", id);

    return NULL;
}

int main()
{
    pthread_t t[N];
    int id[N];

    sem_init(&room, 0, N - 1);

    for(int i = 0; i < N; i++)
        sem_init(&fork_sem[i], 0, 1);

    for(int i = 0; i < N; i++)
    {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    for(int i = 0; i < N; i++)
        sem_destroy(&fork_sem[i]);

    sem_destroy(&room);

    return 0;
}



//7th practical 

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int p1[2], p2[2];
    char filename[100];
    char buffer[100];
    int fd, n;
    pid_t pid;

    pipe(p1);
    pipe(p2);

    pid = fork();

    if(pid > 0)
    {
        // P

        close(p1[0]);
        close(p2[1]);

        printf("Enter file name: ");
        scanf("%99s", filename);

        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        printf("\nFile contents received from child:\n");

        while((n = read(p2[0], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(p2[0]);

        wait(NULL);
    }
    else if(pid == 0)
    {
        // C

        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));
        close(p1[0]);

        fd = open(filename, O_RDONLY);

        if(fd < 0)
        {
            char msg[] = "File not found!\n";
            write(p2[1], msg, strlen(msg));
        }
        else
        {
            while((n = read(fd, buffer, sizeof(buffer))) > 0)
            {
                write(p2[1], buffer, n);
            }

            close(fd);
        }

        close(p2[1]);
    }
    else
    {
        printf("Fork failed!\n");
    }

    return 0;
}




        
    
        
