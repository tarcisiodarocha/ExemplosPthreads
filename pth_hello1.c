#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

void *Hello(void* param);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long t1_param = 1;
   pthread_t t1;
   
   printf("Hello da thread principal!\n");
   
   pthread_create(&t1, NULL, Hello, (void*) t1_param);  
   pthread_join(t1, NULL); 

   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* param) {
   long my_id = (long) param;  /* Use long in case of 64-bit system */ 

   printf("Hello da thread %ld\n", my_id);
   return NULL;
}  /* Hello */

