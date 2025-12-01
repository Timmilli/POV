#include "constants.h"

#include "buffer.h"
#include "clock_module.h"
#include "display_digital_clock.h"
#include "display_image.h"
#include "display_standard_clock.h"
#include "display_text_clock.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

ring_buffer_t tx_buffer;
ring_buffer_t rx_buffer;
clock_values_t cv;
uint16_t mat[NUMBER_OF_POSITIONS];
uint8_t end_of_string = 0;
uint8_t clock_updated = 1;

typedef enum {
  STD_CLOCK = 0, // Standard Clock mode
  DIG_CLOCK = 1, // Digital Clock mode
  IMG = 2,       // Image mode
  TEXT = 3,      // Text mode
} display_mode_e;

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

display_mode_e current_mode = TEXT;

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

  // Initiate flag to induce immediate redraw
  uint8_t need_redraw = 1;

  // Main loop
  while (1) {
    /*
     * Render display according to current mode
     */
    switch (current_mode) {
    case STD_CLOCK: {
      display_standard_clock(mat, &cv, need_redraw);
      break;
    }
    case DIG_CLOCK: {
      display_digital_clock(mat, &cv, need_redraw);
      break;
    }
    case IMG: {
      display_image();
      break;
    }
    case TEXT: {
      display_text_clock(mat, &cv, need_redraw);
      break;
    }
    default:
      break;
    }
    need_redraw = 0;
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
      // Setting mode to standard clock
    case CHANGE_MODE_STD_CLOCK: {
      current_mode = STD_CLOCK;
      uart_send_string("Mode changed!", &tx_buffer);
      need_redraw = 1;
      break;
    }
      // Setting mode to digital clock
    case CHANGE_MODE_DIG_CLOCK: {
      current_mode = DIG_CLOCK;
      uart_send_string("Mode changed!", &tx_buffer);
      need_redraw = 1;
      break;
    }
      // Setting mode to image
    case CHANGE_MODE_IMAGE: {
      current_mode = IMG;
      uart_send_string("Mode changed!", &tx_buffer);
      break;
    }
      // Setting mode to image
    case CHANGE_MODE_TEXT: {
      current_mode = TEXT;
      uart_send_string("Mode changed!", &tx_buffer);
      break;
    }
    default:
      break;
    }
  }

  return 1;
}
