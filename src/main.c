#include "constants.h"

#include "buffer.h"
#include "classic_clock.h"
#include "clock_module.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "merge_matrices.h"
#include "straight_clock.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

ring_buffer_t tx_buffer;
ring_buffer_t rx_buffer;
clock_values_t cv;
uint16_t datastreak = 0;
uint16_t mat[NUMBER_OF_POSITIONS];
uint8_t end_of_string = 0;
display_mode_e mode = STRAIGHT_CLOCK;
uint8_t clock_updated = 1;

/**
 * Receiving interrupt function
 */
ISR(USART_RX_vect) {
  if (!ring_buffer_is_full(&rx_buffer))
    end_of_string = uart_read_byte(&rx_buffer);
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
  /*
   * Initializing everything
   */
  setup_led_driver_com();
  uart_init();
  setup_hall_sensor();

  ring_buffer_init(&tx_buffer);
  ring_buffer_init(&rx_buffer);

  clock_init(&cv);

  // This is the format used in answers in UART communication for the clock
  char clock_format_str[16] = "hh:mm:ss\n";

  // Blank format used in other answers in UART communication. Basically used as
  // a buffer.
  char blank_format_str[16] = "\n";

  // Activating global interrupts
  sei();

  // Sending a first string
  uart_send_string("\n\nReady!\n", &tx_buffer);

  // Main loop
  while (1) {
    /*
     * Processing the UART communication
     */
    process_action_e val = NONE;
    // If a full string has been received
    if (end_of_string == 1) {
      // Process the buffer
      val = process_ring_buffer(&rx_buffer);
      end_of_string = 0;
    }

    // According to the parsing
    switch (val) {
      // Setting another time
    case SET_HOUR: {
      ring_buffer_update_clock(&rx_buffer, &cv);
      clock_updated = 1;
      // Feedback to the user
      clock_to_string(&cv, clock_format_str);
      uart_send_string("Clock set to: ", &tx_buffer);
      uart_send_string(clock_format_str, &tx_buffer);
      break;
    }
      // Or getting the time
    case GET_HOUR: {
      clock_to_string(&cv, clock_format_str);
      uart_send_string("Current clock: ", &tx_buffer);
      uart_send_string(clock_format_str, &tx_buffer);
      break;
    }
      // Or getting the speed
    case GET_SPEED: {
      uint16_t speed = get_turning_speed();
      uart_send_string("Turning speed: ", &tx_buffer);
      sprintf(blank_format_str, "%d\n", speed);
      uart_send_string(blank_format_str, &tx_buffer);
      break;
    }
      // Or changing the mode
    case CHANGE_MODE: {
      mode = ring_buffer_update_mode(&rx_buffer);
      // Feedback to the user
      uart_send_string("Current mode: ", &tx_buffer);
      sprintf(blank_format_str, "%d\n", mode);
      uart_send_string(blank_format_str, &tx_buffer);
      break;
    }
    default:
      break;
    }

    /*
     * Updating the datastreak according to the mode selected
     */
    if (mode == CLASSIC_CLOCK)
      datastreak = 0;
    else if (mode == STRAIGHT_CLOCK)
      datastreak = straight_clock_main(mat, &cv, clock_updated);
    else if (mode == IMAGE)
      datastreak = 1;

    // Writing the datastreak
    write_datastreak(datastreak);

    /*
     * Updating the clock values
     */
    clock_updated = clock_update(&cv);
  }

  return 1;
}
