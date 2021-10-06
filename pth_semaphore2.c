/* Arquivo:  
 *    pth_semaphore2.c
 *
 * Propósito:
 *    Exemplificar o uso de semáforo como mutex.
 *
 *
 * Compile:  gcc -g -Wall -o pth_semaphore2 pth_semaphore2.c -lpthread -lrt
 * Usage:    ./pth_semaphore2 
 *
 */
#include <stdio.h>
#include <pthread.h> 
#include <semaphore.h>

int publico = 0;

sem_t semaphore; 

void incPublico(){
   sem_wait(&semaphore);
   publico++;
   sem_post(&semaphore);
}

void *execute() {
   int i;

   for  (i = 1; i <= 100000; i++){
      incPublico();
   }
   return NULL;
} 


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_t t1, t2, t3, t4; 
   
   sem_init(&semaphore, 0, 1);

   // Criação e execução das threads
   pthread_create(&t1, NULL, execute, NULL);  
   pthread_create(&t2, NULL, execute, NULL);  
   pthread_create(&t3, NULL, execute, NULL);  
   pthread_create(&t4, NULL, execute, NULL);  
   
   // Espera pela finalização das threads
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 
   pthread_join(t3, NULL); 
   pthread_join(t4, NULL); 

   printf("Público final: %d\n", publico);

   sem_destroy(&semaphore);

   return 0;
}  /* main */


