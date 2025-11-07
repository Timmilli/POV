#include "constants.h"
#include "led_com.h"
#include "hall_sensor.h"

#include <avr/io.h>
#include <stdlib.h>
#include <time.h>
#include <util/delay.h>

int display_main(){
  srand(time(NULL));

  setup_hall_sensor();
  setup_led_driver_com();
  
  uint16_t datastreak = ~(0b1111110000111111);
  while (1) { // Main loop
    write_datastreak(datastreak);
    if(hall_is_triggered()){
      pass_magnet_callback();
    };
  }
  return 1;
}

void pass_magnet_callback(void){
  write_datastreak(0b1111110001111111);
  _delay_ms(100);
}