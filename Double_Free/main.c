#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_function() {
    printf("Secret function executed!\n");
    // In a real exploit, malicious code would execute here.
}

void vulnerable_function(char *input) {
    char *a, *b;

    // Allocate two buffers
    a = malloc(32);
    b = malloc(32);

    strcpy(a, "This is safe");
    strcpy(b, "This is also safe");

    free(a); 
    free(a); // Double free

    // Allocate again
    char *c = malloc(32);
    strcpy(c, input); 

    
    void (*func_ptr)();
    func_ptr = (void (*)())b; 
    func_ptr();
}

int main() {
    char malicious_input[32];

    //*(void **)(malicious_input) = (void *)secret_function;

    //vulnerable_function(malicious_input);
char *a, *b;

    // Allocate two buffers
    a = malloc(32);
    b = malloc(32);

    strcpy(a, "This is safe");
    strcpy(b, "This is also safe");

    free(a); 
    free(a); 
    free(b);

    return 0;
}
