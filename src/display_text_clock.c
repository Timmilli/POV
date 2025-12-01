

void display_string(float offset, char[8] str){

    return
}

void display_text_clock(uint16_t mat[NUMBER_OF_POSITIONS],
                            clock_values_t *cv, uint8_t force_redraw) {
  uint16_t datastreak = 0b0;
  uint8_t need_redraw = clock_update(cv) || force_redraw;
  if (need_redraw) {
    draw_clock_to_buffer(mat, cv);
  }
  uint32_t angle = get_current_angle(); // degree
  if (angle < 360)
    datastreak = mat[angle / (360 / NUMBER_OF_POSITIONS)];
  else
    datastreak = 0b1;
  write_datastreak(datastreak);
}
