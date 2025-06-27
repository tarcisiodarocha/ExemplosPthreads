/*
 * Arquivo:    pth_lembrete.c
 * Propósito:  Sistema de gerenciamento de medicamentos com lembretes periódicos
 *             usando threads. Cada medicamento é gerenciado por uma thread separada
 *             que emite alertas no horário correto.
 *
 * Entrada:    Nenhuma (dados dos medicamentos estão hardcoded no programa)
 * Saída:      Mensagens de lembrete para cada medicamento no intervalo especificado
 *
 * Compilar:   gcc -Wall -o pth_lembrete pth_lembrete.c -lpthread
 * Executar:   ./pth_lembrete
 *
 * Funcionamento:
 *   1. Cria uma thread para cada medicamento
 *   2. Cada thread imprime lembretes no intervalo especificado
 *   3. Mostra o horário exato de cada alerta
 *   4. Finaliza após completar todos os lembretes de cada medicamento
 *
 * Estrutura:
 *   - Cada medicamento tem nome, intervalo entre doses e total de doses
 *   - Threads executam concorrentemente
 *   - Uso de time() para mostrar horários reais
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <time.h>

typedef struct {
    char nome[50];
    int intervalo;
    int total;
} Medicacao;

void *Lembrete(void* medicacao);

int main() {
    printf("Sistema de Lembretes Iniciado\n");
    printf("=============================\n");

    pthread_t threads[4];
    Medicacao meds[4] = {
        {"Paracetamol", 8, 10},
        {"Dorflex", 6, 12},
        {"Cataflan", 12, 8},
        {"Vitamina B12", 24, 6}
    };

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, Lembrete, &meds[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n=============================\n");
    printf("Todos os lembretes concluídos!\n");
    return 0;
}

void *Lembrete(void* medicacao) {
    Medicacao *med = (Medicacao*)medicacao;
    time_t t;
    struct tm *tm_info;
    
    for (int i = 1; i <= med->total; i++) {
        time(&t);
        tm_info = localtime(&t);
        printf("[%02d:%02d:%02d] Tome %s (%d/%d)\n", 
               tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec,
               med->nome, i, med->total);
        
        sleep(med->intervalo);
    }
    
    printf("--> %s finalizado\n", med->nome);
    return NULL;
}
