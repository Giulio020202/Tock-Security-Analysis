#include <stdio.h>
#include <string.h>

#include <libtock-sync/services/alarm.h>
#include <libtock/kernel/ipc.h>


size_t _server = -1;
int _buf[16] __attribute__((aligned(16)));


bool _done = false;

// For this simple example, the callback only need set the yield variable.
static void ipc_callback(__attribute__ ((unused)) int   pid,
                         __attribute__ ((unused)) int   len,
                         __attribute__ ((unused)) int   arg2,
                         __attribute__ ((unused)) void* ud) {
  _done = true;
}



// Use the server service to get pointer
static int get_pointer(void) {
  _done       = false;
  ipc_notify_service(_server);
  yield_for(&_done);

  return _buf[0];
}

static int write_buffer(void){

  _done = false;

  /*
  int counter = _buf[0];
  printf("[client] writing on buffer[%d]\n", counter);
  if(counter < 16){
    _buf[0] = _buf[0] + 1;
  }
  */

  
  ipc_notify_service(_server);
  yield_for(&_done);

  return 1;
}

int main(void) {
  int ret;


  // Retrieve a handle to the server service.
  ret = ipc_discover("org.tockos.tutorials.ipc.server", &_server);
  if (ret != RETURNCODE_SUCCESS) {
    printf("No server service\n");
    return -1;
  }
  printf("[client] server discovered\n");

  // Setup IPC for server service
  ipc_register_client_callback(_server, ipc_callback, NULL);
  ipc_share(_server, _buf, 16);

  /*--------test for r/w on external pointer

  printf("[client] trying to retrive pointer\n");
  int* ptr = (int*)get_pointer();
  printf("[client] ptr: %p\n",ptr);
  printf("[client]trying to read pointer: ");
  printf("val: %d",*ptr);   //this will fault
  */

  while(write_buffer() == 1){
    libtocksync_alarm_delay_ms(500);
  }


  return 0;
}
