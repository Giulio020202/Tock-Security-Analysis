#include <libtock-sync/peripherals/rng.h>
#include <libtock/kernel/ipc.h>
#include <libtock/tock.h>

// Random Number Generator Service
//
// This application waits for IPC notifications and returns random bytes
// in the buffer shared with it from the requesting application.
//
// Interface
// =========
//
// The first byte of the shared buffer is the number of random bytes the
// calling application wants. This service will fill the buffer with that
// many random bytes (starting with index 0 and overwriting the number
// requested). This service will then notify the client.
//
// If the buffer is not long enough to hold the number of requested bytes
// the service will stop processing the request and not notify the client.

static void ipc_callback(int pid, int len, int buf, __attribute__ ((unused)) void* ud) {
  uint8_t* buffer = (uint8_t*) buf;
  uint8_t* rng;

  uint8_t counter = buffer[0];
  printf("[RNG] counter: %d -> %d\n", counter, counter+1);

  buffer[0] = buffer[0] + 1;

  // Signal done.
  ipc_notify_client(pid);
}

int main(void) {
  // Register the IPC service for this app. It is identified by the PACKAGE_NAME
  // of this app.
  ipc_register_service_callback("org.tockos.tutorials.ipc.rng", ipc_callback,
                                NULL);

  while (1) {
    yield();
  }
}
