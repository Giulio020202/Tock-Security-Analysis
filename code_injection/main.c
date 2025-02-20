#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione "critica" che vogliamo eseguire sfruttando un overflow
void critical_function() {
    printf("Critical function executed!\n");
}

// Funzione innocua di default
void harmless_function() {
    printf("Harmless function executed.\n");
}

void dangling_pointer_test() {
    void (*func_ptr)() = harmless_function;
    char *buffer = malloc(16);

    // Forza l'allocazione del puntatore a funzione nello heap
    void **ptr_in_heap = malloc(sizeof(void *));
    *ptr_in_heap = func_ptr;

    printf("Pointer before corruption: %p\n", *ptr_in_heap);

    free(buffer);

    // Sovrascrive l'area con il dangling pointer
    strcpy(buffer, (char *)&critical_function);

    // Recupera il valore corrotto
    func_ptr = *ptr_in_heap;
    func_ptr();
}


int main() {
    dangling_pointer_test();
    return 0;
}
