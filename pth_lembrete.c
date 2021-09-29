/* Arquivo:  
 *    pth_lembrete.c
 *
 * Propósito:
 *    Implementar um gerenciador de lembretes de medicamentos usando 
 *    pthreads. Cada thread fica responsável por lembrar o usuário de
 *    um único medicamento.
 *
 * Input:
 *    nenhum
 * Output:
 *    Mensagens de cada thread lembrando o usuário de tomar o medicamento.  
 *
 * Compile:  gcc -g -Wall -o pth_lembrete pth_lembrete.c -lpthread
 * Usage:    ./pth_lembrete 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <string.h>
#include <time.h>


struct Medicacao{
   char nome[50];
   int intervalo;
   int total;
}; 

void *Lembrete(void* medicacao);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   printf("Gerenciador de lembretes iniciado!!\n");
   printf("====================================\n");

   pthread_t t1, t2, t3; 
   struct Medicacao *m1, *m2, *m3;
   
   // Medicação 1
   m1 = malloc(sizeof(struct Medicacao));
   strcpy(m1->nome, "Paracetamol");
   m1->intervalo = 8;
   m1->total =  10;

   // Medicação 2
   m2 = malloc(sizeof(struct Medicacao));
   strcpy(m2->nome, "Dorflex");
   m2->intervalo = 6;
   m2->total = 12;

   // Medicação 3
   m3 = malloc(sizeof(struct Medicacao));
   strcpy(m3->nome, "Cataflan");
   m3->intervalo = 12;
   m3->total = 8;
   
   // Criação e execução das threads
   pthread_create(&t1, NULL, Lembrete, (void*) m1);  
   pthread_create(&t2, NULL, Lembrete, (void*) m2);  
   pthread_create(&t3, NULL, Lembrete, (void*) m3);  
   
   // Espera pela finalização das threads
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 
   pthread_join(t3, NULL); 

   printf("=====================================\n");
   printf("Gerenciador de lembretes finalizado!!\n");
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Lembrete(void* medicacao) {
   struct Medicacao *med = (struct Medicacao*) medicacao; 
   
   int i;
   time_t t;   
   
   for  (i = 1; i <= med->total; i++){
      time(&t);
      printf("Tomar %s %d/%d ## %s", med->nome, i, med->total, ctime(&t));
      sleep(med->intervalo);
   }
   printf("FIM: %s\n", med->nome);
   free(med);
   return NULL;
}  /* Lembrete */

