#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"

#include <avr/io.h>
#include <util/delay.h>



int display_main(){
  srand(time(NULL));
  setup_hall_sensor();
  setup_led_driver_com();
  uint16_t datastreak = 0b00000001;
  
  while (1) { // Main loop
    long angle = get_current_angle();
    if(angle >= 90.0 && angle <= 180.0){
      write_datastreak(~datastreak);
    }else{
      write_datastreak(datastreak);
    }
  }
  return 1;
}

