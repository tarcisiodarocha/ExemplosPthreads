/*
 * Arquivo:    pth_race_condition2.c
 * Propósito:  Demonstrar condição de corrida (race condition) em um sistema
 *             de reservas de cinema com múltiplos caixas
 *
 * Descrição:  Simula dois caixas reservando assentos simultaneamente sem
 *             sincronização, resultando em inconsistência nos assentos disponíveis
 *
 * Compilar:   gcc -Wall -o pth_race_condition2 pth_race_condition2.c -lpthread
 * Executar:   ./pth_race_condition2
 *
 * Funcionamento:
 *   1. Cinema com 100 assentos disponíveis
 *   2. Dois caixas tentam reservar 60 assentos cada
 *   3. Sem sincronização, ambos podem achar que há assentos suficientes
 *   4. Resultado final incorreto (assentos negativos)
 *
 * Observações:
 *   - Código contém race condition intencional para fins didáticos
 *   - Solução requer mutex ou outro mecanismo de sincronização
 *   - sleep(1) torna a race condition mais visível
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL_ASSENTOS 100

int assentos_disponiveis = TOTAL_ASSENTOS;  // Variável compartilhada

/* Função de reserva com race condition */
void* reservar_assentos(void* arg) {
    int quantidade = *((int*)arg);
    
    // Verificação não sincronizada
    if (quantidade <= assentos_disponiveis) {
        printf("Processando reserva de %d assentos...\n", quantidade);
        
        // Simula tempo de processamento (torna race condition mais evidente)
        sleep(1);
        
        // Atualização não segura da variável compartilhada
        assentos_disponiveis -= quantidade;
        printf("Reserva confirmada. Assentos restantes: %d\n", assentos_disponiveis);
    } else {
        printf("Reserva negada. Requeridos: %d, Disponíveis: %d\n", 
               quantidade, assentos_disponiveis);
    }
    
    return NULL;
}

int main() {
    pthread_t caixa1, caixa2;
    int reservas[] = {60, 60};  // Cada caixa tenta reservar 60 assentos
    
    printf("Iniciando sistema de reservas (%d assentos disponíveis)\n", TOTAL_ASSENTOS);
    
    // Cria threads para os dois caixas
    pthread_create(&caixa1, NULL, reservar_assentos, &reservas[0]);
    pthread_create(&caixa2, NULL, reservar_assentos, &reservas[1]);
    
    // Aguarda finalização das threads
    pthread_join(caixa1, NULL);
    pthread_join(caixa2, NULL);
    
    // Mostra resultado final (potencialmente incorreto)
    printf("\nAssentos finais disponíveis: %d (deveria ser %d)\n", 
           assentos_disponiveis, TOTAL_ASSENTOS - reservas[0] - reservas[1]);
    
    return 0;
}