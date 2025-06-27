/* Arquivo:  
 *    pth_semaphore2.c
 *
 * Propósito:
 *    Exemplificar o uso de semáforo como limitador do número
 *    de threads que executa paralelamente.
 *
 *
 * Compile:  gcc -g -Wall -o pth_semaphore3 pth_semaphore3.c -lpthread -lrt
 * Usage:    ./pth_semaphore3 
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define CAPACIDADE_MAX 20
#define TOTAL_PESSOAS 50

sem_t semaforo_capacidade;
pthread_mutex_t mutex_contador = PTHREAD_MUTEX_INITIALIZER;
int pessoas_no_camarote = 0;

typedef struct {
    int id;
    int tempo_permanencia;
} Pessoa;

void* pessoa_no_camarote(void* arg) {
    Pessoa* p = (Pessoa*)arg;
    
    // Tenta entrar no camarote
    sem_wait(&semaforo_capacidade);
    
    // Atualiza contador
    pthread_mutex_lock(&mutex_contador);
    pessoas_no_camarote++;
    printf("Pessoa %d entrou. Total: %d\n", p->id, pessoas_no_camarote);
    if(pessoas_no_camarote == CAPACIDADE_MAX) {
        printf("--- CAMAROTE LOTADO (%d pessoas) ---\n", CAPACIDADE_MAX);
    }
    pthread_mutex_unlock(&mutex_contador);
    
    // Tempo de permanência no camarote
    sleep(p->tempo_permanencia);
    
    // Sai do camarote
    pthread_mutex_lock(&mutex_contador);
    pessoas_no_camarote--;
    printf("Pessoa %d saiu. Total: %d\n", p->id, pessoas_no_camarote);
    pthread_mutex_unlock(&mutex_contador);
    
    sem_post(&semaforo_capacidade);
    
    free(p);
    return NULL;
}

int main() {
    pthread_t pessoas[TOTAL_PESSOAS];
    sem_init(&semaforo_capacidade, 0, CAPACIDADE_MAX);
    
    // Cria threads para cada pessoa
    for (int i = 0; i < TOTAL_PESSOAS; i++) {
        Pessoa* p = malloc(sizeof(Pessoa));
        p->id = i + 1;
        p->tempo_permanencia = 10 + rand() % 10; // 2-6 segundos
        
        // Intervalo aleatório entre chegadas (0-1 segundos)
        usleep(rand() % 1000000);
        
        pthread_create(&pessoas[i], NULL, pessoa_no_camarote, p);
    }
    
    // Espera todas as threads terminarem
    for (int i = 0; i < TOTAL_PESSOAS; i++) {
        pthread_join(pessoas[i], NULL);
    }
    
    sem_destroy(&semaforo_capacidade);
    pthread_mutex_destroy(&mutex_contador);
    
    printf("Evento encerrado. Pessoas restantes: %d\n", pessoas_no_camarote);
    return 0;
}