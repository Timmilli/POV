#include "constants.h"

#include "buffer.h"
#include "display.h"
#include "led_com.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

ring_buffer_t tx_buffer;
ring_buffer_t rx_buffer;
uint16_t datastreak = 0b1111100000011111;

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
  ring_buffer_init(&tx_buffer);
  ring_buffer_init(&rx_buffer);

  sei(); // activate interrupts

  uart_send_string("Ready!", &tx_buffer);

  while (1) {
    process_action_e val = process_ring_buffer(&rx_buffer);

    switch (val) {
    case SET_HOUR:
      uart_send_string("SetHour!\n", &tx_buffer);
      datastreak = ~datastreak;
      write_datastreak(datastreak);
      break;
    default:
      break;
    }

    pwm(5);
  }
  return 1;
}
