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
uint16_t datastreak = 0b1111100000011111;
uint16_t mat[NUMBER_OF_POSITIONS] = {};

/**
 * Receiving interrupt function
 */
ISR(USART_RX_vect) 
{
  if (!ring_buffer_is_full(&rx_buffer))
    uart_read_byte(&rx_buffer);
}

/**
 * Sending interrupt function
 */
ISR(USART_UDRE_vect) 
{
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

  merge_matrices(mat, &cv);

  sei(); // activate interrupts

  uart_send_string("\n\nReady!\n", &tx_buffer);

  while (1) {
    uint32_t angle = get_current_angle();
    datastreak = mat[angle % NUMBER_OF_POSITIONS];
    write_datastreak(datastreak);

    process_action_e val = process_ring_buffer(&rx_buffer);

    switch (val) {
    case SET_HOUR:
      datastreak = clock_get_seconds(&cv) + (clock_get_minutes(&cv) << 6) +
                   (clock_get_hours(&cv) << 12);
      write_datastreak(datastreak);
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
    pwm(1);
  }
  return 1;
}
