/* File:  
 *    pth_pool.c
 *
 * Purpose:
 *    Implementação de um pool de threads
 *
 *
 * Compile:  gcc -g -Wall -o pth_pool pth_pool.c -lpthread -lrt
 * Usage:    ./pth_hello
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define THREAD_NUM 4    // Tamanho do pool de threads
#define BUFFER_SIZE 256 // Númermo máximo de tarefas enfileiradas

typedef struct Task{
   int a, b;
}Task;

Task taskQueue[BUFFER_SIZE];
int taskCount = 0;

pthread_mutex_t mutex;

pthread_cond_t condFull;
pthread_cond_t condEmpty;

void executeTask(Task* task, int id){
   int result = task->a + task->b;
   printf("(Thread %d) Sum of %d and %d is %d\n", id, task->a, task->b, result);
}

Task getTask(){
   pthread_mutex_lock(&mutex);
   
   while (taskCount == 0){
      pthread_cond_wait(&condEmpty, &mutex);
   }
   
   Task task = taskQueue[0];
   int i;
   for (i = 0; i < taskCount - 1; i++){
      taskQueue[i] = taskQueue[i+1];
   }
   taskCount--;
   
   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&condFull);
   return task;
}

void submitTask(Task task){
   pthread_mutex_lock(&mutex);

   while (taskCount == BUFFER_SIZE){
      pthread_cond_wait(&condFull, &mutex);
   }

   taskQueue[taskCount] = task;
   taskCount++;

   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&condEmpty);
}

void *startThread(void* args);  

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_mutex_init(&mutex, NULL);
   
   pthread_cond_init(&condEmpty, NULL);
   pthread_cond_init(&condFull, NULL);

   pthread_t thread[THREAD_NUM]; 
   long i;
   for (i = 0; i < THREAD_NUM; i++){  
      if (pthread_create(&thread[i], NULL, &startThread, (void*) i) != 0) {
         perror("Failed to create the thread");
      }  
   }
   
   srand(time(NULL));
   for (i = 0; i < 500; i++){
      Task t = {
         .a = rand() % 100,
         .b = rand() % 100
      };
      submitTask(t);
   }
   
   for (i = 0; i < THREAD_NUM; i++){  
      if (pthread_join(thread[i], NULL) != 0) {
         perror("Failed to join the thread");
      }  
   }
   
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&condEmpty);
   pthread_cond_destroy(&condFull);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *startThread(void* args) {
   long id = (long) args; 
   while (1){ 
      Task task = getTask();
      executeTask(&task, id);
      sleep(rand()%5);
   }
   return NULL;
} 

