#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tock.h>



void function(){
  printf("you should not be able to read this\n");
}

int max(int n1, int n2){
  if(n1 > n2){return n1;} else {return n2;}
}

int main(void) {


  volatile int (*fp)();
  char buffer[8];
  printf("uninitialized fp: %d\n",fp);
  fp = max(0, 0); //this is useless but makes the compiler evaluate fp instead of assigning fixed value
  printf("initialized fp: %d\n",fp);



//strcpy and gets don't work (when copying over buffer limit), but this does
  for(int i = 0; i < 34; i++){
    buffer[i] = '\x00\x24\x00\x01';
    if(i == 10){buffer[i] = '\x00\x24\x00\x01';}
  }

  printf("buffer: %s\n", buffer);
  //strcpy(buffer,"bufferbuffer"); //*** buffer overflow detected ***: terminated
  if (fp != 0){
    printf("function pointer: 0x%08x\n",fp);
    fp();
  } 

  printf("fp : %d\n",fp);

  

  return 0;
}
