#include "constants.h"

#include "buffer.h"
#include "clock_module.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "merge_matrices.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

ring_buffer_t tx_buffer;
ring_buffer_t rx_buffer;
clock_values_t cv;
uint16_t datastreak = 0;
uint16_t mat[NUMBER_OF_POSITIONS] = {};

/**
 * Receiving interrupt function
 */
ISR(USART_RX_vect) {
  if (!ring_buffer_is_full(&rx_buffer))
    uart_read_byte(&rx_buffer);
}

/**
 * Sending interrupt function
 */
ISR(USART_UDRE_vect) {
  if (ring_buffer_available_bytes(&tx_buffer) > 0)
    uart_send_byte(&tx_buffer);
  else
    UDRIE_INTERRUPT_OFF;
}

int main(void) {
  setup_led_driver_com();
  uart_init(MYUBRR);
  setup_hall_sensor();

  ring_buffer_init(&tx_buffer);
  ring_buffer_init(&rx_buffer);
  clock_init(&cv);

  uint8_t i = 0;
  char str[16] = "hh:mm:ss\n";

  sei(); // activate interrupts

  uart_send_string("\n\nReady!\n", &tx_buffer);

  merge_matrices(mat, &cv, &tx_buffer);

  while (1) {
    uint32_t angle = get_current_angle(); // degré
    if (angle < 360)
      datastreak = mat[angle / 3];
    else
      datastreak = 0;

    if (clock_get_seconds(&cv) < angle / 6) {
      datastreak &= ~(0b0000000000000001);
    } else {
      datastreak |= 0b0000000000000001;
    }

    write_datastreak(datastreak);

    process_action_e val = NONE;

    if (ring_buffer_available_bytes(&rx_buffer) > 0)
      val = process_ring_buffer(&rx_buffer);

    switch (val) {
    case SET_HOUR:
      ring_buffer_update_clock(&rx_buffer, &cv);
      uart_send_string("Clock set to: ", &tx_buffer);
      clock_to_string(&cv, str);
      uart_send_string(str, &tx_buffer);
      break;
    case GET_HOUR:
      clock_to_string(&cv, str);
      uart_send_string("Current clock: ", &tx_buffer);
      uart_send_string(str, &tx_buffer);
    default:
      break;
    }

    clock_update(&cv);
  }
  return 1;
}
