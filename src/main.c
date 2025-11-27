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
uint16_t mat[NUMBER_OF_POSITIONS];
uint8_t end_of_string = 0;

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

  // This is the format used in answers in UART communication
  char clock_format_str[16] = "hh:mm:ss\n";

  // Activating global interrupts
  sei();

  // Sending a first string
  uart_send_string("\n\nReady!\n", &tx_buffer);

  // Creating the initial clock matrix
  merge_matrices(mat, &cv);

  // Main loop
  while (1) {
    /*
     * Creating the datastreak
     */
    uint32_t angle = get_current_angle();
    // Getting the hours and minutes digits
    if (angle < 360)
      datastreak = mat[angle / (360 / NUMBER_OF_POSITIONS)];
    else
      datastreak = 0;

    // Putting the seconds as the outer led ring
    uint8_t s = clock_get_seconds(&cv);
    if (angle > 180) {
      if (s < (angle - 180) / 6) {
        datastreak &= ~(0b0000000000000001);
      } else {
        datastreak |= 0b0000000000000001;
      }
    } else {
      if (s > 30) {
        if ((s - 30) < angle / 6) {
          datastreak &= ~(0b0000000000000001);
        } else {
          datastreak |= 0b0000000000000001;
        }
      }
    }

    // Writing the datastreak
    write_datastreak(datastreak);

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
    case SET_HOUR:
      ring_buffer_update_clock(&rx_buffer, &cv);
      merge_matrices(mat, &cv);
      // Feedback to the user
      clock_to_string(&cv, clock_format_str);
      uart_send_string("Clock set to: ", &tx_buffer);
      uart_send_string(clock_format_str, &tx_buffer);
      break;
      // Or getting the time
    case GET_HOUR:
      clock_to_string(&cv, clock_format_str);
      uart_send_string("Current clock: ", &tx_buffer);
      uart_send_string(clock_format_str, &tx_buffer);
      break;
    default:
      break;
    }

    /*
     * Updating the clock values
     */
    uint8_t clock_updated = clock_update(&cv);
    if (clock_updated)
      merge_matrices(mat, &cv);
  }

  return 1;
}
