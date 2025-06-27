/*
 * Arquivo:    pth_hello2.c
 * Propósito:  Exemplo de criação múltipla de threads com pthreads
 *             Mostra a execução concorrente de várias threads
 *
 * Como compilar: gcc -Wall -o pth_hello2 pth_hello2.c -lpthread
 * Como executar: ./pth_hello2
 *
 * Funcionamento:
 *   1. Cria 40 threads que imprimem mensagens
 *   2. Cada thread executa por aproximadamente 2 segundos
 *   3. A thread principal aguarda todas terminarem
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Variável global compartilhada */
int thread_count = 40;  /* Número total de threads */

/* Função executada por cada thread */
void *Hello(void* rank);

int main() {
   pthread_t* thread_handles;
   
   /* Aloca espaço para os identificadores das threads */
   thread_handles = malloc(thread_count * sizeof(pthread_t));
   
   /* Cria todas as threads */
   for (long thread = 0; thread < thread_count; thread++) {
      pthread_create(&thread_handles[thread], NULL, Hello, (void*)thread);
   }
   
   printf("Thread principal criou todas as threads\n");
   
   /* Aguarda todas as threads terminarem */
   for (long thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
      printf("Thread %ld finalizada\n", thread);
   }
   
   free(thread_handles);
   printf("Programa encerrado\n");
   
   return 0;
}

/* Função que cada thread executa */
void *Hello(void* rank) {
   long my_rank = (long)rank;
   
   printf("Thread %ld iniciada (de %d)\n", my_rank, thread_count);
   sleep(2);  /* Simula trabalho */
   printf("Thread %ld terminando\n", my_rank);
   
   return NULL;
}