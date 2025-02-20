#include <stdio.h>
#include <string.h>

#include <libtock-sync/services/alarm.h>
#include <libtock/kernel/ipc.h>

// Every 500 ms use the RNG service to randomly select an LED to turn on or
// off and then use the LED service to control that LED.

size_t _rng_service = -1;
char _rng_buf[64] __attribute__((aligned(64)));

uint8_t _number_of_leds = 0;

bool _done = false;

// For this simple example, the callback only need set the yield variable.
static void ipc_callback(__attribute__ ((unused)) int   pid,
                         __attribute__ ((unused)) int   len,
                         __attribute__ ((unused)) int   arg2,
                         __attribute__ ((unused)) void* ud) {
  _done = true;
}



// Use the RNG service to get two random bytes.
static uint16_t increase_counter(void) {
  _done       = false;
  ipc_notify_service(_rng_service);
  yield_for(&_done);
}

int main(void) {
  int ret;

  // Retrieve a handle to the RNG service.
  ret = ipc_discover("org.tockos.tutorials.ipc.rng", &_rng_service);
  if (ret != RETURNCODE_SUCCESS) {
    printf("No rng service\n");
    return -1;
  }

  // Setup IPC for RNG service
  ipc_register_client_callback(_rng_service, ipc_callback, NULL);
  ipc_share(_rng_service, _rng_buf, 64);

  // Then randomly turn on and off LEDs using the two services.
  while (1) {
    
    printf("[logic] counter : %d", _rng_buf[0]);

    libtocksync_alarm_delay_ms(500);
  }
  
  return 0;
}
