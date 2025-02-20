#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//successfull testing of dangling pointers
//will be used over ipc?

int main(void) {

  printf("[dangling] starting dangling_pointer_test\n");

  uint8_t* ptr = malloc(sizeof(uint8_t));
  *ptr = 10;
  printf("[dangling] ptr: %p, val: %d\n",ptr,*ptr);
  free(ptr);

  printf("[dangling] printing ptr after free:\n\t\tptr: %p, val: %d\n", ptr, *ptr);

  printf("[dangling] malloc-ing second pointer\n");
  uint8_t* second = malloc(sizeof(uint8_t));
  *second = 20;
  printf("[dangling] second: %p, val: %d\n",second,*second);

  printf("[dangling] writing ptr after free\n");
  *ptr = 77;
  //this will successfully write over second value
  printf("[dangling] ptr: %p, val: %d\n",ptr,*ptr);  
  printf("[dangling] second: %p, val: %d\n",second,*second);
  free(second);

  return 0;
}
