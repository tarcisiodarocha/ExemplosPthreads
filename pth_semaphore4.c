/*
 * Arquivo:    pth_semaphore4.c
 * Propósito:  Demonstrar o uso de semáforos para controlar o acesso
 *             a um recurso limitado (capacidade do camarote)
 *
 * Descrição:  Simula o controle de acesso a um camarote com capacidade
 *             máxima, onde pessoas entram e saem após um tempo aleatório.
 *             Usa semáforo para limitar a capacidade e mutex para proteger
 *             a variável compartilhada de contagem.
 *
 * Input:      Nenhum (parâmetros definidos no código)
 * Output:     Mensagens mostrando a entrada/saída de pessoas e lotação atual
 *
 * Compilar:   gcc -Wall -o pth_semaphore4 pth_semaphore4.c -lpthread
 * Executar:   ./pth_semaphore4
 *
 * Funcionamento:
 *   1. Cria 100 threads representando pessoas tentando entrar no camarote
 *   2. Limita a capacidade máxima a 20 pessoas simultâneas usando semáforo
 *   3. Cada pessoa fica um tempo aleatório (2-12 segundos) no camarote
 *   4. Mostra mensagens de entrada/saída e lotação atual
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_MAX 20     // Lotação máxima do camarote
#define TOTAL_PESSOAS 100     // Total de pessoas que tentarão entrar

// Variáveis de sincronização
sem_t semaforo_capacidade;    // Controla o número de pessoas no camarote
pthread_mutex_t mutex_contador = PTHREAD_MUTEX_INITIALIZER;  // Protege o contador
int pessoas_no_camarote = 0;  // Contador compartilhado

typedef struct {
    int id;                   // Identificador da pessoa
    int tempo_permanencia;    // Tempo que ficará no camarote (segundos)
} Pessoa;

/* Função executada por cada thread (pessoa) */
void* pessoa_no_camarote(void* arg) {
    Pessoa* p = (Pessoa*)arg;
    
    // Espera por uma vaga no camarote
    sem_wait(&semaforo_capacidade);
    
    // Entra no camarote (região crítica)
    pthread_mutex_lock(&mutex_contador);
    pessoas_no_camarote++;
    printf("Pessoa %d entrou. Total: %d\n", p->id, pessoas_no_camarote);
    if(pessoas_no_camarote == CAPACIDADE_MAX) {
        printf("--- CAMAROTE LOTADO (%d pessoas) ---\n", CAPACIDADE_MAX);
    }
    pthread_mutex_unlock(&mutex_contador);
    
    // Fica no camarote (tempo aleatório)
    sleep(p->tempo_permanencia);
    
    // Sai do camarote (região crítica)
    pthread_mutex_lock(&mutex_contador);
    pessoas_no_camarote--;
    printf("Pessoa %d saiu. Total: %d\n", p->id, pessoas_no_camarote);
    pthread_mutex_unlock(&mutex_contador);
    
    // Libera uma vaga
    sem_post(&semaforo_capacidade);
    
    free(p);  // Libera a memória alocada para a pessoa
    return NULL;
}

int main() {
    pthread_t pessoas[TOTAL_PESSOAS];
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializa o semáforo com a capacidade máxima
    sem_init(&semaforo_capacidade, 0, CAPACIDADE_MAX);
    
    // Cria as threads (pessoas)
    for (int i = 0; i < TOTAL_PESSOAS; i++) {
        Pessoa* p = malloc(sizeof(Pessoa));
        p->id = i + 1;
        p->tempo_permanencia = 2 + rand() % 11;  // Tempo entre 2-12 segundos
        
        // Intervalo aleatório entre chegadas (0-1 segundo)
        usleep(rand() % 1000000);
        
        pthread_create(&pessoas[i], NULL, pessoa_no_camarote, p);
    }
    
    // Espera todas as threads terminarem
    for (int i = 0; i < TOTAL_PESSOAS; i++) {
        pthread_join(pessoas[i], NULL);
    }
    
    // Libera recursos
    sem_destroy(&semaforo_capacidade);
    pthread_mutex_destroy(&mutex_contador);
    
    printf("\nEvento encerrado. Pessoas restantes no camarote: %d\n", 
           pessoas_no_camarote);
    
    return 0;
}