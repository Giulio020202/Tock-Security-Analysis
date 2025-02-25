#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This file contains a test for arbitrary execution trough the use of a dangling pointer

//function we want to force execution of
void critical_function() {
    printf("successful arbitrary exec\n");
}

void harmless_function() {
    printf("Harmless function executed.\n");
}

void dangling_pointer_test() {
    void (*func_ptr)() = harmless_function;
    char *buffer = malloc(16);

    void **ptr_in_heap = malloc(sizeof(void *));
    *ptr_in_heap = func_ptr;

    printf("Pointer before corruption: %p\n", *ptr_in_heap);

    free(buffer);

    // overwrite with dangling pointer
    strcpy(buffer, (char *)&critical_function);

    func_ptr = *ptr_in_heap;
    func_ptr();
}


int main() {
    dangling_pointer_test();
    return 0;
}
