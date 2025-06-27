/* Arquivo:  
 *    pth_race_condition.c
 *
 * Propósito:
 *    Implementar um contador de público .
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


int publico = 0;

void incPublico(){
   publico++; // Região crítica
}

void *execute() {
   int i;

   for  (i = 1; i <= 100000; i++){
      incPublico();
   }
   return NULL;
} 


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_t t1, t2, t3, t4; 
   
   
   // Criação e execução das threads
   pthread_create(&t1, NULL, execute, NULL);  
   pthread_create(&t2, NULL, execute, NULL);  
   pthread_create(&t3, NULL, execute, NULL);  
   pthread_create(&t4, NULL, execute, NULL);
   
   // Espera pela finalização das threads
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 
   pthread_join(t3, NULL);
   pthread_join(t4, NULL); 
   
   printf("Público final: %d\n", publico);


   return 0;
}  /* main */


