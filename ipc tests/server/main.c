#include <stdio.h>
#include <string.h>

#include <libtock-sync/services/alarm.h>
#include <libtock/kernel/ipc.h>

  /*
  //----------------stack version
  int pointed = 10;
  int* ptr = &pointed;
  */

  //----------------heap version
  int* ptr;

static void ipc_callback(int pid, int len, int buf, __attribute__ ((unused)) void* ud) {
  int* buffer = (int*) buf;

  /* r/w pointer test
  //------------heap version
  ptr = malloc(sizeof(int));
  *ptr = 10;

  buffer[0] = (int)ptr;
  //printf("[test] size of int pointer: %d, sizeof int: %d, sizeof char: %d\n", sizeof(int*), sizeof(int), sizeof(char));
  printf("[server] pointer ptr : %p - %d, with value: %d\n",ptr,ptr,*ptr);

  printf("[server] buffer[0] written with pointer %p - %d, val : %d\n",(int*)buffer[0], buffer[0], *(int*)buffer[0]);
  //free(ptr);  //faults both with and without free, double free does nothing
  */

  buffer[0] = 0;
  printf("[server] buffer[0] = %d\n", buffer[0]);
  
  // Signal done.
  ipc_notify_client(pid);
}

int main(void) {
  // Register the IPC service for this app. It is identified by the PACKAGE_NAME
  // of this app.
  ipc_register_service_callback("org.tockos.tutorials.ipc.server", ipc_callback,
                                NULL);

  while (1) {
    yield();
  }
}
