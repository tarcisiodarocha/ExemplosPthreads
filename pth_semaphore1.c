/*
 * Arquivo:    pth_semaphore1.c
 * Propósito:  Demonstrar operações básicas de semáforo (wait/post) sem threads
 *             Mostra o controle de acesso a recursos limitados usando semáforos
 *
 * Compilar:   gcc -Wall -o pth_semaphore1 pth_semaphore1.c -lpthread
 * Executar:   ./pth_semaphore1
 *
 * Funcionamento:
 *   1. Inicializa semáforo com valor 2 (permite 2 acessos simultâneos)
 *   2. Demonstra sequência de operações wait/post
 *   3. Mostra o comportamento quando o semáforo atinge zero
 *   4. Inclui sem_post para liberar recursos e evitar deadlock
 */

#include <stdio.h>
#include <semaphore.h>

sem_t semaphore;

int main() {
    // Inicializa semáforo permitindo 2 acessos concorrentes
    sem_init(&semaphore, 0, 2);
    printf("Semáforo inicializado (valor=2)\n\n");

    // Primeiro acesso - permitido (valor->1)
    printf("[1] sem_wait...\n");
    sem_wait(&semaphore);
    printf("[1] PASS (valor=1)\n\n");

    // Segundo acesso - permitido (valor->0)
    printf("[2] sem_wait...\n");
    sem_wait(&semaphore);
    printf("[2] PASS (valor=0)\n\n");

    // Terceiro acesso - bloquearia (valor=0), mas vamos liberar primeiro
    printf("[3] sem_post (liberando 1 acesso)\n");
    sem_post(&semaphore);  // Valor volta para 1
    printf("[3] sem_wait...\n");
    sem_wait(&semaphore);
    printf("[3] PASS (valor=0)\n\n");

    // Quarto acesso - ainda bloquearia
    printf("[4] sem_post (liberando mais 1 acesso)\n");
    sem_post(&semaphore);  // Valor volta para 1
    printf("[4] sem_wait...\n");
    sem_wait(&semaphore);
    printf("[4] PASS (valor=0)\n\n");

    // Liberação final
    printf("Liberando todos os acessos...\n");
    sem_post(&semaphore);
    sem_post(&semaphore);

    sem_destroy(&semaphore);
    printf("Semáforo destruído\n");
    
    return 0;
}
