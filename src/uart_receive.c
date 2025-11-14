#include "constants.h"

#include "led_com.h"
#include "uart_com.h"
#include "uart_receive.h"
#include "uart_send.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

uint8_t USART_Receive(uint8_t current_data) {
  uint8_t i = 0;
  char str[64];
  /* Wait for data to be received */
  while (!(UCSR0A & (1 << RXC0))) {
    if (i++ >= 10) {
      sprintf(str, "current_data=%d\n", current_data);
      uart_send_string(str);
    }
    pwm(1);
  }
  /* Get and return received data from buffer */
  return UDR0;
}

int uart_receive_main(void) {
  uart_init(MYUBRR);
  setup_led_driver_com();

  uart_send_string("Started.\n");

  uint8_t data = 1;
  write_datastreak(data);

  while (1) {
    data = USART_Receive(data);
    write_datastreak(data);
    uart_send_byte(data);
  }

  return 1;
}
