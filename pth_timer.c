/* File:  
 *    pth_pool.c
 *
 * Purpose:
 *    Exemplificar o uso de variáveis de condição para uma tread Timer
 *    sinalizar outra Thread Alarm que é hora de soar um alarme.
 *
 *
 * Compile:  gcc -g -Wall -o pth_timer pth_timer.c -lpthread -lrt
 * Usage:    ./pth_hello
 */
 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
int timer_done = 0;

void* timer(void* arg) {
    printf("Timer started. Waiting for 5 seconds...\n");
    sleep(5); // Simula o tempo do timer
    pthread_mutex_lock(&mutex);
    timer_done = 1;
    pthread_cond_signal(&cond_var); // Sinaliza que o timer terminou
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* alarm(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!timer_done) {
        pthread_cond_wait(&cond_var, &mutex); // Espera até que o timer sinalize
    }
    printf("Timer done! Alarm ringing!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t timer_thread, alarm_thread;

    // Inicializa o mutex e a variável de condição
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Cria as threads
    pthread_create(&timer_thread, NULL, timer, NULL);
    pthread_create(&alarm_thread, NULL, alarm, NULL);

    // Espera que as threads terminem
    pthread_join(timer_thread, NULL);
    pthread_join(alarm_thread, NULL);

    // Destroi o mutex e a variável de condição
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
