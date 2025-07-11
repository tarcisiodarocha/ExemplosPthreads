/* Arquivo:  
 *    pth_condition_variable.c
 *
 * Propósito:
 *    Demonstrar o uso de variáveis de condição (condition variables) para
 *    sincronização entre threads, ilustrando o padrão produtor-consumidor
 *    básico com wait/signal.
 *
 * Input:
 *    Nenhum - o comportamento é determinado pelo código fixo
 *
 * Output:
 *    Mensagens que mostram o fluxo de execução:
 *    1. A primeira thread entra em espera (wait)
 *    2. A segunda thread envia o sinal (signal)
 *    3. A primeira thread é liberada
 *
 * Compile:  gcc -g -Wall -o pth_condition_variable pth_condition_variable.c -lpthread
 * Usage:    ./pth_condition_variable 
 *
 * Observações:
 *    1. Usa mutex junto com condition variable (boas práticas)
 *    2. Demonstra o padrão básico wait/signal
 *    3. Inclui sleep(5) para garantir ordenação didática das mensagens
 *    4. Variável 'done' controla o estado da sincronização
 *    5. A thread 1 espera, thread 2 sinaliza
 *
 * Referências:
 *    POSIX Threads Programming
 *    pthread_cond_wait(3) manual page
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
// Variáveis de sincronização
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int done = 1;  // Flag de controle
 
void* execute()
{
    pthread_mutex_lock(&lock);
    
    if (done == 1) {
        // Thread1 entra aqui
        done = 2;
        // Está dormindo esperando um signal de cond1  
        printf("Thread %ld: Esperando por cond1...\n", pthread_self());
    }
    else {
        // Thread 2 entra aqui
        // A Thread2 envia um signal de cond1 -> Acorda a Thread1
        printf("Thread %ld: Sinalizando cond1...\n", pthread_self());
        pthread_cond_signal(&cond1);
    }
 
    pthread_mutex_unlock(&lock);
    printf("Thread %ld: Finalizando execução\n", pthread_self());
    return NULL;
}
 
int main()
{
    pthread_t tid1, tid2;

    printf("Main: Criando thread 1\n");
    pthread_create(&tid1, NULL, execute, NULL);
 
    sleep(5);  // Pausa didática para garantir a ordem inicial
 
    printf("Main: Criando thread 2 após 5 segundos\n");
    pthread_create(&tid2, NULL, execute, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    printf("Main: Todas threads finalizadas\n");
    return 0;
}