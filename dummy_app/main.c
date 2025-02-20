#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//control app that will be installed among others to see if other app's crash will affect it
  
int main(void) {

  uint8_t* memory_start = tock_app_memory_begins_at();
  uint8_t* memory_end   = tock_app_memory_ends_at();
  printf("[dummy] hi, I'm dummy app, my memory starts from %p and ends at %p\n\n",memory_start,memory_end);

  return 0;
}
