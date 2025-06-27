/* Arquivo:  
 *    pth_reserva_cinema.c
 *
 * Propósito:
 *    Implementar um sistema de reservas de assentos para um cinema com múltiplos caixas,
 *    demonstrando uma condição de corrida (race condition) e a necessidade de sincronização.
 *
 * Input:
 *    nenhum (valores de reserva hardcoded no exemplo)
 * Output:
 *    Mensagens mostrando o processo de reserva e assentos disponíveis,
 *    demonstrando o problema da race condition quando não sincronizado.
 *
 * Compile:  gcc -g -Wall -o pth_reserva_cinema pth_reserva_cinema.c -lpthread
 * Usage:    ./pth_reserva_cinema 
 *
 * Observação:
 *    Este código intencionalmente contém uma race condition para fins didáticos.
 *    A solução com mutex deve ser implementada pelos alunos.
 */
#include <stdio.h>
#include <pthread.h>

#define TOTAL_ASSENTOS 100

int assentos_disponiveis = TOTAL_ASSENTOS;

void* reservar_assentos(void* arg) {
    int quantidade = *((int*)arg);
    
    if (quantidade <= assentos_disponiveis) {
        // Simula processamento da reserva
        sleep(1);
        
        printf("Reservando %d assentos...\n", quantidade);
        assentos_disponiveis -= quantidade;
        printf("Reserva concluída. Assentos restantes: %d\n", assentos_disponiveis);
    } else {
        printf("Não há assentos suficientes. Requeridos: %d, Disponíveis: %d\n", 
               quantidade, assentos_disponiveis);
    }
    
    return NULL;
}

int main() {
    pthread_t caixa1, caixa2;
    
    // Dois clientes tentando reservar 60 assentos cada
    int reserva1 = 60;
    int reserva2 = 60;
    
    pthread_create(&caixa1, NULL, reservar_assentos, &reserva1);
    pthread_create(&caixa2, NULL, reservar_assentos, &reserva2);
    
    pthread_join(caixa1, NULL);
    pthread_join(caixa2, NULL);
    
    printf("Assentos finais disponíveis: %d\n", assentos_disponiveis);
    
    return 0;
}