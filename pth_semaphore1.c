/* Arquivo:  
 *    pth_semaphore1.c
 *
 * Propósito:
 *    Experimentar as funções básicas de um semáforo sem o uso de threads
 *
 * Compile:  gcc -g -Wall -o pth_semaphore1 pth_semaphore.c -lpthread -lrt
 * Usage:    ./pth_semaphore1
 *
 */
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h> 


sem_t semaphore;


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   sem_init(&semaphore, 0, 0);

   //sem_post(&semaphore);
   
   printf("Waiting...\n");
   sem_wait(&semaphore);
   printf("PASS\n\n");

   sem_destroy(&semaphore);
   return 0;
}  /* main */


