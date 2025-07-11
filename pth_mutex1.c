/*
 * Arquivo:    pth_mutex1.c
 * Propósito:  Demonstrar o uso de mutex para proteger uma variável compartilhada
 *             entre múltiplas threads, evitando condições de corrida (race conditions)
 *
 * Input:      Nenhum
 * Output:     Valor final da variável compartilhada após todas as threads completarem
 *
 * Compilar:   gcc -Wall -o pth_mutex1 pth_mutex1.c -lpthread
 * Executar:   ./pth_mutex1
 *
 * Funcionamento:
 *   1. Cria 4 threads que incrementam uma variável compartilhada
 *   2. Cada thread faz 200.000 incrementos
 *   3. Usa mutex para proteger o acesso à variável compartilhada
 *   4. Mostra o valor final esperado (800.000)
 *
 * Observações:
 *   - Sem o mutex, o valor final seria incorreto devido a race conditions
 *   - Demonstra a necessidade de sincronização em programas multi-threaded
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int publico = 0;                // Variável compartilhada
pthread_mutex_t mutex;          // Mutex para controle de acesso

void incPublico() {
    pthread_mutex_lock(&mutex); // Bloqueia o acesso
    publico++;                 // Incrementa a variável
    pthread_mutex_unlock(&mutex); // Libera o acesso
}

void *execute(void *arg) {
    for (int i = 0; i < 200000; i++) {
        incPublico();
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    // Inicializa o mutex
    pthread_mutex_init(&mutex, NULL);

    // Cria 4 threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, execute, NULL);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mostra o resultado final
    printf("Público final: %d (esperado: 800000)\n", publico);

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

