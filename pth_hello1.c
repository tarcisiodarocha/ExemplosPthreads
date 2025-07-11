/*
 * Arquivo:    pth_hello1.c
 * Propósito:  Exemplo simples de criação de threads com pthreads
 *             Mostra a execução simultânea de duas threads junto com a thread principal
 *
 * Como compilar: gcc -o pth_hello1 pth_hello1.c -lpthread
 * Como executar: ./pth_hello1
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Funções que as threads irão executar */
void *Hello1(void* param);
void *Hello2(void* param);

int main() {
   pthread_t t1, t2;
   
   /* Cria duas threads */
   pthread_create(&t1, NULL, Hello1, (void*)10);  /* Thread 1 faz 10 iterações */
   pthread_create(&t2, NULL, Hello2, (void*)15);  /* Thread 2 faz 15 iterações */
   
   /* Thread principal imprime 5 vezes */
   for (int i = 0; i < 5; i++) {
      printf("Principal %d\n", i);
      sleep(1);
   }
   
   /* Espera as threads terminarem */
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);
   
   return 0;
}

/* Thread 1 imprime "Hello1" 10 vezes */
void *Hello1(void* param) {
   int vezes = (int)param;
   for (int i = 0; i < vezes; i++) {
      printf("Hello1 %d\n", i);
      sleep(1);
   }
   return NULL;
}

/* Thread 2 imprime "Hello2" 15 vezes */
void *Hello2(void* param) {
   int vezes = (int)param;
   for (int i = 0; i < vezes; i++) {
      printf("Hello2 %d\n", i);
      sleep(1);
   }
   return NULL;
}