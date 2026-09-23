// !!! DO NOT ADD #pragma once !!! //

RGB_MATRIX_EFFECT(custom_colors)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern bool caps_lock_active;

// Custom color layout + Caps Lock animcation
static bool custom_colors(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  uint8_t v_val = rgb_matrix_get_val();

  HSV hsv_green       = { .h = 85,  .s = 255, .v = v_val };
  HSV hsv_red         = { .h = 0,   .s = 255, .v = v_val };
  HSV hsv_blue        = { .h = 170, .s = 255, .v = v_val };
  HSV hsv_soft_pink   = { .h = 235, .s = 180, .v = v_val };
  HSV hsv_soft_orange = { .h = 22,  .s = 180, .v = v_val };
  HSV hsv_white       = { .h = 0,   .s = 0,   .v = v_val };
  HSV hsv_teal        = { .h = 128, .s = 255, .v = v_val };

  RGB rgb_green       = hsv_to_rgb(hsv_green);
  RGB rgb_red         = hsv_to_rgb(hsv_red);
  RGB rgb_blue        = hsv_to_rgb(hsv_blue);
  RGB rgb_soft_pink   = hsv_to_rgb(hsv_soft_pink);
  RGB rgb_soft_orange = hsv_to_rgb(hsv_soft_orange);
  RGB rgb_white       = hsv_to_rgb(hsv_white);
  RGB rgb_teal        = hsv_to_rgb(hsv_teal);
  RGB rgb_off         = { .r = 0, .g = 0, .b = 0 };


  for (uint8_t i = led_min; i < led_max; i++) {
    RGB rgb;

    switch (i) {
      // ESC -> Green
      case 0:
        rgb = rgb_green;
        break;

      // Enter -> Red
      case 47:
        rgb = rgb_red;
        break;

      // Caps Lock -> Blue (Flickers on/off every 500ms when Caps Lock is enabled)
      case 59:
        if (caps_lock_active) {
          bool flicker_state = (timer_read() / 500) % 2 == 0;
          rgb = flicker_state ? rgb_blue : rgb_off;
        } else {
          rgb = rgb_blue;
        }
        break;

      // Both Alts, Both Ctrls, Both Shifts, Backspace, Tab -> Blue
      case 17: // Backspace
      case 31: // Tab
      case 60: // Left Shift
      case 71: // Right Shift
      case 77: // Right Ctrl
      case 79: // Right Alt
      case 81: // Left Alt
      case 83: // Left Ctrl
        rgb = rgb_teal;
        break;

      // Arrow Keys (Up, Right, Down, Left) -> Soft Orange
      case 72: // Up Arrow
      case 74: // Right Arrow
      case 75: // Down Arrow
      case 76: // Left Arrow
        rgb = rgb_soft_orange;
        break;

      // Number keys (1 through 0, -, =) -> Soft Pink
      case 18 ... 29:
        rgb = rgb_soft_pink;
        break;

      // Letters & Symbol keys + Spacebar -> White
      case 30:        // `~
      case 32 ... 44: // Q..P, [{, ]}, \|
      case 48 ... 49: // "' and ;:
      case 50 ... 58: // A..L
      case 61 ... 70: // Z..M, <,, >., ?/
      case 80:        // Spacebar
        rgb = rgb_white;
        break;

      // F-keys (F1–F12), Nav keys (PgUp/PgDn/Home/End), Fn, KC_LGUI (LED 81), Side LED -> Teal
      default:
        rgb = rgb_blue;
        break;
    }

    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}




#endif
