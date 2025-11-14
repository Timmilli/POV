#include "constants.h"

#include "led_com.h"
#include "uart_com.h"
#include <avr/io.h>
#include <util/delay.h>

void uart_send_byte(uint8_t data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void uart_send_string(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    uart_send_byte(str[i++]);
  }
}

int uart_send_main(void) {
  uart_init(MYUBRR);

  setup_led_driver_com();
  int8_t i = 0;

  while (1) {
    uart_send_string("bla bli blou");
    pwm(500);
    write_datastreak(i++);
    //_delay_ms(1000);
  }

  return 1;
}
