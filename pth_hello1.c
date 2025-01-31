#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

void *Hello(void* param);  /* Thread function */
void *Hello2(void* param);  /* Thread function */
/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long t1_param = 10;
   long t2_param = 15;
   pthread_t t1;
   pthread_t t2;
   
   pthread_create(&t1, NULL, Hello, (void*) t1_param);  
   pthread_create(&t2, NULL, Hello2, (void*) t2_param);  
 
   int i = 0;
   for (i = 0; i < 5; i++){
      printf("Principal %d\n", i);
      sleep(1);
   }   
 
   pthread_join(t1, NULL); 
   pthread_join(t2, NULL); 

   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* param) {
   long my_id = (long) param;  /* Use long in case of 64-bit system */ 
   int i = 0;
   for (i = 0; i < my_id; i++){
      printf("Hello %d\n", i);
      sleep(1);
   }   
   return NULL;
}  /* Hello */

void *Hello2(void* param) {
   long my_id = (long) param;  /* Use long in case of 64-bit system */ 
   int i = 0;
   for (i = 0; i < my_id; i++){
      printf("Hello2 %d\n", i);
      sleep(1);
   }   
   return NULL;
}  /* Hello */
