#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD		0      

int main()
{
    sem_t * elephant_mice;   
    sem_t * dog_cats;       
    sem_t * cat_parrots; 
    sem_t * mouse_parrots; 
    sem_t * cat_mice;        
  
    int pid;	
    int i;		
    int N;		
    int status;  
    int type;           

    if ((elephant_mice = sem_open("/elephant_mice_sem", O_CREAT, 0644, 1)) == SEM_FAILED) 
    {
      perror("Failed to open/initialize semphore for elephant_mice.");
      exit(-1);
    }
  
    if ((dog_cats = sem_open("/dog_cat_sem", O_CREAT, 0644, 1)) == SEM_FAILED) 
    {
      perror("Failed to open/initialize semphore for dog_cat.");
      exit(-1);
    }
	
    if ((cat_parrots = sem_open("/cat_parrot_sem", O_CREAT, 0644, 1)) == SEM_FAILED) 
    {
      perror("Failed to open/initialize semphore for cat_parrot.");
      exit(-1);
    }
	
    if ((mouse_parrots = sem_open("/mouse_parrot_sempahore", O_CREAT, 0644, 1)) == SEM_FAILED) 
    {
      perror("Failed to open/initialize semphore for mouse_parrot.");
      exit(-1);
    }
  
    if ((cat_mice = sem_open("/cat_mice_sempahore", O_CREAT, 0644, 1)) == SEM_FAILED) 
    {
      perror("Failed to open/initialize semphore for cat_mice.");
      exit(-1);
    }
     
    printf("How many requests to be processed: \n");
    scanf("%d",&N);

    for (i=1; i<=N; i++) 
    {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) 
        {
	        perror("fork");
	        exit(1);
        }
        
        if (pid == CHILD) 
        {
          pid = getpid();
          switch (type) 
          {
            case 1: 
                        printf("     Elephant process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(elephant_mice);
                        printf("     Elephant process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Elephant process with pid %d is out.\n",pid);
                        fflush(stdout); 
                        sem_post(elephant_mice);
                        break;

            case 2:  
                        printf("     Dog process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(dog_cats);
                        printf("     Dog process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Dog process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(dog_cats);
                        break;

            case 3: 
                        printf("     Cat process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(dog_cats);
                        sem_wait(cat_parrots);
                        sem_wait(cat_mice);
                        printf("     Cat process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Cat process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(dog_cats);
                        sem_post(cat_parrots);
                        sem_post(cat_mice);
                        break;

            case 4: 
                        printf("     Mouse process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(mouse_parrots);
                        sem_wait(elephant_mice);
                        sem_wait(cat_mice);
                        printf("     Mouse process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Mouse process with pid %d is out.\n",pid);
                        fflush(stdout); 
                        sem_post(mouse_parrots);
                        sem_post(elephant_mice);
                        sem_post(cat_mice);
                        break;

            case 5: 
                        printf("     Parrot process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(mouse_parrots);
                        sem_wait(cat_parrots);
                        printf("     Parrot process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Parrot process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(mouse_parrots);
                        sem_post(cat_parrots);
                        break;
          }
          exit(0);
       }
    }
    
    for (i=1; i<=N; i++) 
    {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}
