#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <libtock/tock.h>

/*FROM: MPU RAM End
===============

This test checks whether an application can read the last byte in its RAM
allocation and whether it can read the byte immediately after. Usually a
process cannot read the last byte in its RAM allocation because it is taken up by grants.
*/



int main(void) {

  uint8_t* memory_start = tock_app_memory_begins_at();
  uint8_t* memory_end   = tock_app_memory_ends_at();
  uint8_t* flash_start  = tock_app_flash_begins_at();
  uint8_t* flash_end    = tock_app_flash_ends_at();
  uint8_t* memory_limit = sbrk(0);

  printf("\n[TEST] MPU Walk Regions-----------------\n");
  putchar('\n');

  printf("  app_memory:            %p-%p\n", memory_start, memory_end);
  printf("  app_memory_accessible: %p-%p\n", memory_start, memory_limit);
  printf("  app_flash:             %p-%p\n", flash_start, flash_end);
  printf("-----------------------------------------------\n\n");
  
  //from here to next comment its cut and paste from mpu_ram_end

  /*
  printf("[TEST] MPU RAM End\n");

  uint8_t* ram_end = tock_app_memory_ends_at();

  printf("Reading last byte in RAM, address %p\n", ram_end - 1);
  */
  
  /* --uncommenting this section will indeed fault the app

  printf("This should fault if there is a grant region.\n");
  uint8_t last_byte = *(ram_end - 1);
  printf("Address: %p, value: %02x\n", (ram_end - 1), last_byte);

  */

  //end of mpu_ram_end -------------------------------------------

  /*attempting to read last-byte trough printf format string vulnerability
  //ATTEMPT FAILED :)
  
  uint8_t last_byte = *(ram_end - 1);
  printf("address ram end -2: %p, val: %02x, trying to read ram end -1: \n",(ram_end-1),last_byte);
  printf("if this shows app hasnt faulted\n");
  */

  printf("trying to read from last accessible memory address: %p, val:%02x \n", memory_limit, *memory_limit);
  printf("trying to read past that normally, this should fault!\n");
  printf("addr: %p, val: %02x\n",memory_limit+1, *(memory_limit+1)); //Didnt fault, is it because grants dont start yet?
  printf("trying to writ to memory_limit+1\n");
  *(memory_limit+1) = 0;
  printf("if you can read this write wass successful\n");
  printf("addr: %p, val: %02x\n",memory_limit+1, *(memory_limit+1)); //Didnt fault, is it because grants dont start yet?


  //uncomment to walk untill grant starts, addr should be less than memory_end 
  
  printf("starting walking till fault:\n");
  int walk = 1;
  
  //walk untill walk = 1924 (limit before faulting) trying not to fault
  //this does not fault
  /*
  for(walk; walk < 1920; walk++){
    printf("addr: %p, val: %02x\n",memory_limit+walk, *(memory_limit+walk));
    printf("walked %d times\n", walk);

  //attempting to read past limit using printf exploit
    if(walk == 1919){
      printf("addr1: %p, val: %02x, something: %x, %x,%x,%x,%x,%x,%x,%x,%x,%x,\n",memory_limit+walk, *(memory_limit+walk));
    }

  }
  */

  /*
  //------------- walk untill fault-----------------
  while (1)
  {
    printf("addr: %p, val: %02x\n",memory_limit+walk, *(memory_limit+walk));
    printf("walked %d times\n", walk);
    walk++;
  }
  */
  // faults at 0x2005dff - when walk getso to 1923

  //we descovered last readable addr is 0x2005dff - 0x33578495, lets try to read directly there
  //https://cs155.stanford.edu/papers/formatstring-1.2.pdf
  //https://github.com/hackerschoice/THC-Archive/blob/master/Papers/overflow.txt
 
  //This actually faults for memory_end and memory_end-1, probably in grant
  /*
  printf("attempting to read memory end (should fault): \n");
  printf("memory_end: %p,",memory_end);
  printf(" val: %02x\n",*(memory_end)); //this line faults
  printf("shouldnt be able to read this, if so it has not faulted\n\n");
  */

 


  return 0;
}
