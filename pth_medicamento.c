#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

typedef struct medicacao {
   char nome[50];
   int intervalo;
   int total;
} medicacao_t;

void *consumirMedicacao(void* medicacao);

int main(int argc, char* argv[]) {
   medicacao_t medicacao1 = {
      "Dorflex", 6, 10
   };
   
   medicacao_t medicacao2 = {
      "Paracetamol", 8, 12
   };
   
   medicacao_t medicacao3 = {
      "PILA", 24, 6
   };
   
   pthread_t t1, t2, t3;
   
   pthread_create(&t1, NULL, consumirMedicacao, (void*) &medicacao1);  
   pthread_create(&t2, NULL, consumirMedicacao, (void*) &medicacao2);  
   pthread_create(&t3, NULL, consumirMedicacao, (void*) &medicacao3);  
 
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 
   pthread_join(t3, NULL); 

   return 0;
}

void *consumirMedicacao(void* param_medicacao) {
   medicacao_t medicacao = *(medicacao_t*) param_medicacao;
   
   while (medicacao.total--) {
      printf("Tomou o remédio %s | ", medicacao.nome);
      if (medicacao.total) {
         printf("Faltam %d pílulas.\n", medicacao.total);
      } else {
         printf("Acabou fi!\n");
      }
      sleep(medicacao.intervalo);
   }
   
   return NULL;
}