#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

void* Publico(void* param);  /* Thread function */

long contador_publico = 0;

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_t t1, t2, t3, t4;
   
   pthread_create(&t1, NULL, Publico, NULL);  
   pthread_create(&t2, NULL, Publico, NULL);
   pthread_create(&t3, NULL, Publico, NULL);  
   pthread_create(&t4, NULL, Publico, NULL);
 
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 
   pthread_join(t3, NULL); 
   pthread_join(t4, NULL); 
   
   printf("Quantidade total: %ld\n", contador_publico);
   
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void* Publico(void* param) {
   for (int i = 0; i < 100000; i++){
      contador_publico++;
   }   
   return NULL;
}