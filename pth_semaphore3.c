/*
 * Arquivo:    pth_semaphore3.c
 * Propósito:  Demonstrar o uso de semáforos para limitar a quantidade
 *             de threads em execução simultânea
 *
 * Descrição:  Cria 40 threads mas limita a 4 threads concorrentes
 *             usando um semáforo contador. Cada thread executa por
 *             um tempo aleatório entre 2-6 segundos.
 *
 * Compilar:   gcc -Wall -o pth_semaphore3 pth_semaphore3.c -lpthread
 * Executar:   ./pth_semaphore3
 *
 * Funcionamento:
 *   1. Inicializa semáforo com valor 4 (limite de threads concorrentes)
 *   2. Cria 40 threads, mas apenas 4 podem executar simultaneamente
 *   3. Cada thread executa por tempo aleatório (2-6 segundos)
 *   4. Thread principal aguarda término de todas as threads
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define MAX_THREADS 40
#define MAX_CONCURRENT 4

sem_t semaphore;  // Semáforo para controle de concorrência

/* Função executada por cada thread */
void *execute(void *args) {
   long id = (long)args;
   int sleep_time = (rand() % 5) + 2;  // Tempo aleatório 2-6 segundos
   
   printf("Thread %ld iniciada (executando por %ds)\n", id, sleep_time);
   sleep(sleep_time);
   printf("Thread %ld finalizada\n", id);
   
   sem_post(&semaphore);  // Libera uma vaga no semáforo
   return NULL;
}

int main() {
   pthread_t thread_handles[MAX_THREADS];
   
   // Inicializa gerador de números aleatórios
   srand(time(NULL));
   
   // Inicializa semáforo permitindo MAX_CONCURRENT threads concorrentes
   sem_init(&semaphore, 0, MAX_CONCURRENT);
   
   // Cria todas as threads
   for (long thread = 0; thread < MAX_THREADS; thread++) {
      sem_wait(&semaphore);  // Aguarda vaga disponível
      pthread_create(&thread_handles[thread], NULL, execute, (void*)thread);
   }
   
   printf("Thread principal: todas as threads criadas\n");
   
   // Aguarda término de todas as threads
   for (long thread = 0; thread < MAX_THREADS; thread++) {
      pthread_join(thread_handles[thread], NULL);
      printf("Thread %ld finalizada e liberada\n", thread);
   }
   
   // Libera recursos
   sem_destroy(&semaphore);
   printf("Thread principal: programa encerrado\n");
   
   return 0;
}

