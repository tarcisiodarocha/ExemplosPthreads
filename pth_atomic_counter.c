/* Arquivo:  
 *    pth_atomic_counter.c
 *
 * Propósito:
 *    Demonstrar o uso de operações atômicas para implementar
 *    um contador thread-safe sem necessidade de mutex ou semáforos.
 *    Ilustra como operações atômicas do C11 garantem segurança
 *    em acessos concorrentes a variáveis compartilhadas.
 *
 * Input:
 *    Nenhum - o número de threads e iterações é fixo no código
 *
 * Output:
 *    Valor final do contador após todas as threads completarem
 *    suas operações (deveria ser 800000 se tudo funcionar corretamente)
 *
 * Compile:  gcc -g -Wall -o pth_atomic_counter pth_atomic_counter.c -lpthread
 * Usage:    ./pth_atomic_counter
 *
 * Observações:
 *    1. Usa atomic_int do C11 para garantir atomicidade nas operações
 *    2. Não há contenção por bloqueios (lock-free)
 *    3. Ilustra a eficiência de operações atômicas vs mutex
 *    4. Cada thread incrementa o contador 200000 vezes
 *    5. Versão atualizada substituindo o semáforo por atomic operations
 *
 * Referências:
 *    Padrão C11 - <stdatomic.h>
 *    Documentação pthread
 */
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

atomic_int publico = 0;  // Contador atômico compartilhado

void *execute() {
    for(int i = 1; i <= 200000; i++) {
        atomic_fetch_add(&publico, 1);  // Incremento atômico
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    
    // Criação das threads
    pthread_create(&t1, NULL, execute, NULL);
    pthread_create(&t2, NULL, execute, NULL);
    pthread_create(&t3, NULL, execute, NULL);
    pthread_create(&t4, NULL, execute, NULL);
    
    // Espera todas as threads completarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("Público final: %d\n", (int)publico);  // Imprime resultado final
    return 0;
}