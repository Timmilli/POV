#include "constants.h"

#include "hall_sensor.h"
#include "clock_module.h"
#include "led_com.h"

#include <avr/io.h>
#include <util/delay.h>

uint16_t  draw_fork(uint32_t angle,uint32_t location, uint8_t length){
  //Angle in 6 degrees
  uint16_t res = ~0b0;
    if(angle == location){
      res = ~(res >> length);
      return res;
    }else{
      return 0b0;
    }
}

uint16_t draw_cadran(uint32_t angle){
  //Angle in 6 degrees
  uint16_t res = 0b001;
  float angle12 = angle % 5;
  float angle4 = angle % 15;

  if(angle12 == 0 || angle12 == 5){
    res |= 0b011;
  }
  if(angle4 == 0 || angle4 == 15){
    res|= 0b0111;
  }
  return res;

}

uint16_t draw_clock(uint32_t angle){
  //Angle in 6 degrees
  uint16_t datastreak = draw_cadran(angle);
  datastreak |= draw_fork(angle,60-clock_get_seconds(),14);
  datastreak |= draw_fork(angle,60-clock_get_minutes(),10);
  datastreak |= draw_fork(angle,60-(clock_get_hours()%12)*5,6);
  return datastreak;
}

int display_main(){
  uint8_t alternator = 0;
  srand(time(NULL));
  setup_hall_sensor();
  setup_led_driver_com();
  uint16_t datastreak = 0b00000001;
  clock_set_time(0,30,4);

  while (1) { // Main loop
    clock_update();
    uint32_t angle = (get_current_angle()/6 + 0.5);
    if(alternator){
      datastreak = draw_clock(angle) | 0b1000000;
    }else{
      datastreak = draw_clock(angle);
    }
    alternator = ~alternator;

    write_datastreak(datastreak);
  }
  return 1;
}
