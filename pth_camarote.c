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
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>

#define CAPACIDADE_VIP 20
#define PESSOAS 100

typedef struct Pessoa {
   int id;
   int tempo;
} pessoa_t;

sem_t semaphore;
pthread_mutex_t mutex;

int pessoas_na_vip = 0;

void incrementarVIP() {
   pthread_mutex_lock(&mutex);
   pessoas_na_vip++;
   pthread_mutex_unlock(&mutex);
}

void decrementarVIP() {
   pthread_mutex_lock(&mutex);
   pessoas_na_vip--;
   pthread_mutex_unlock(&mutex);
}

void *entrarNaVIP(void* param) {
   pessoa_t *pessoa = (pessoa_t*) param;
   
   sem_wait(&semaphore);
   incrementarVIP();
   printf("A pessoa %d ENTROU NA ÁREA VIP.\nPessoas na área VIP: %d\n", pessoa->id, pessoas_na_vip);
   
   sleep(pessoa->tempo);
   
   decrementarVIP();
   sem_post(&semaphore);
   printf("A pessoa %d SAIU DA ÁREA VIP.\nPessoas na área VIP: %d\n", pessoa->id, pessoas_na_vip);
   
   return NULL;
} 


int main(int argc, char* argv[]) {
   sem_init(&semaphore, 0, CAPACIDADE_VIP);
   pthread_mutex_init(&mutex, NULL);
   
   pthread_t* threads_handle = malloc(PESSOAS*sizeof(pthread_t));
   for (int i = 0; i < PESSOAS; i++) {
      pessoa_t *pessoa = malloc(sizeof(pessoa_t));
      pessoa->id = i;
      pessoa->tempo = rand() % 11 + 10;
      pthread_create(&threads_handle[i], NULL, entrarNaVIP, (void*) pessoa);  
   }
   
   for (int i = 0; i < PESSOAS; i++) {
      pthread_join(threads_handle[i], NULL);  
   }
   
   free(threads_handle);
   sem_destroy(&semaphore);
   pthread_mutex_destroy(&mutex);
   
   return 0;
}