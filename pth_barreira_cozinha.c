/*
 * Arquivo:    pth_barreira_cozinha.c
 * Propósito:  Demonstrar o uso de barreiras para sincronizar threads em um cenário
 *             realístico de cozinha profissional, onde cozinheiros precisam
 *             completar etapas simultaneamente antes de avançar para a próxima fase
 *
 * Input:      Nenhum
 * Output:     Mensagens mostrando o progresso sincronizado dos cozinheiros
 *
 * Compilar:   gcc -Wall -o pth_barreira_cozinha pth_barreira_cozinha.c -lpthread
 * Executar:   ./pth_barreira_cozinha
 *
 * Funcionamento:
 *   1. Cria 4 threads (cozinheiros) que realizam 3 etapas de preparo
 *   2. Cada etapa é sincronizada por uma barreira
 *   3. Apenas uma thread imprime a mensagem de conclusão de cada etapa
 *   4. Mostra o tempo gasto em cada fase
 *
 * Observações:
 *   - Demonstra a utilidade de barreiras em algoritmos paralelos multi-fase
 *   - Ilustra como sincronizar threads em pontos específicos do processamento
 *   - Mostra o comportamento determinístico mesmo com tempos de execução variáveis
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COZINHEIROS 4
#define NUM_ETAPAS 3

pthread_barrier_t barreira;
const char* etapas[NUM_ETAPAS] = {"CORTAR INGREDIENTES", "COZINHAR", "MONTAR O PRATO"};

void* cozinheiro(void* arg) {
    int id = *(int*)arg;
    srand(time(NULL) + id);

    for (int etapa = 0; etapa < NUM_ETAPAS; etapa++) {
        int tempo_etapa = 1 + rand() % 3;
        printf("Cozinheiro %d: %s (%ds)\n", id, etapas[etapa], tempo_etapa);
        sleep(tempo_etapa);

        int ret = pthread_barrier_wait(&barreira);
        if (ret == PTHREAD_BARRIER_SERIAL_THREAD) {
            printf("\n--- TODOS TERMINARAM: %s ---\n\n", etapas[etapa]);
        }
    }
    return NULL;
}

int main() {
    pthread_t cozinheiros[NUM_COZINHEIROS];
    int ids[NUM_COZINHEIROS];
    struct timespec inicio, fim;
    
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    pthread_barrier_init(&barreira, NULL, NUM_COZINHEIROS);

    for (int i = 0; i < NUM_COZINHEIROS; i++) {
        ids[i] = i + 1;
        pthread_create(&cozinheiros[i], NULL, cozinheiro, &ids[i]);
    }

    for (int i = 0; i < NUM_COZINHEIROS; i++) {
        pthread_join(cozinheiros[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_total = (fim.tv_sec - inicio.tv_sec) + 
                        (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    pthread_barrier_destroy(&barreira);
    printf("Prato finalizado em %.2f segundos!\n", tempo_total);
    return 0;
}
