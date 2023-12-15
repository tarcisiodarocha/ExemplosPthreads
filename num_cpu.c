#include <stdio.h>
#include <unistd.h>

int main() {
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    
    if (nprocs < 1) {
        printf("Não foi possível determinar o número de núcleos.\n");
    } else {
        printf("Número de núcleos de CPU: %ld\n", nprocs);
    }

    return 0;
}
