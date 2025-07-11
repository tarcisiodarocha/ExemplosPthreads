/*
 * Arquivo:    pth_semaphore2.c
 * Propósito:  Demonstrar o uso de semáforo como mutex binário para proteger
 *             uma variável compartilhada entre threads
 *
 * Descrição:  O programa cria 4 threads que incrementam uma variável compartilhada
 *             100.000 vezes cada, usando um semáforo como mecanismo de exclusão mútua
 *             para evitar condições de corrida (race conditions)
 *
 * Compilar:   gcc -Wall -o pth_semaphore2 pth_semaphore2.c -lpthread
 * Executar:   ./pth_semaphore2
 *
 * Funcionamento:
 *   1. Inicializa um semáforo com valor 1 (funciona como mutex)
 *   2. Cria 4 threads que incrementam uma variável compartilhada
 *   3. Cada thread faz 100.000 incrementos protegidos pelo semáforo
 *   4. Mostra o valor final da variável (esperado: 400.000)
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int publico = 0;          // Variável compartilhada
sem_t semaforo;           // Semáforo usado como mutex

/* Incrementa a variável compartilhada de forma segura */
void incPublico() {
    sem_wait(&semaforo);  // Entrada na seção crítica
    publico++;
    sem_post(&semaforo);  // Saída da seção crítica
}

/* Função executada por cada thread */
void *execute(void *arg) {
    for (int i = 0; i < 100000; i++) {
        incPublico();
    }
    return NULL;
}

int main() {
    pthread_t threads[4];  // Array para armazenar os IDs das threads

    // Inicializa o semáforo como mutex binário (valor inicial 1)
    sem_init(&semaforo, 0, 1);

    // Cria as 4 threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, execute, NULL);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mostra o resultado final
    printf("Público final: %d (esperado: 400000)\n", publico);

    // Libera recursos do semáforo
    sem_destroy(&semaforo);

    return 0;
}
