/* Copyright 2022 mohoyt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "typehud.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _BASE,    
    _NUM,
    _NAV,
    //_TAP
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
      SC_LSPO, KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, SC_RSPC,
      KC_LCTL, KC_LGUI, KC_LALT, LT(_NUM, KC_SPC), MO(_NAV) , LT(_NUM, KC_SPC), KC_RALT, KC_RGUI, KC_RCTL, KC_MPLY, KC_MUTE ),

//  [_TAP] = LAYOUT_all(
//      KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,  
//      KC_TAB, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G, KC_H, RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_ENT,
//      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_C,
//      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, TG(_TAP)),

  [_NUM] = LAYOUT_all(
  	  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
  	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_UP, KC_MINS, KC_EQL, KC_QUOT, KC_ENT,
  	  KC_TRNS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_EQL, KC_SLSH, KC_TRNS,
  	  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, QK_BOOT ),
 
  [_NAV] = LAYOUT_all(
      KC_TRNS, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO  , KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD,KC_TRNS, KC_TRNS, KC_NO  , KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_BSLS, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_UP,
      AG_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS )
};

//Encoder map
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [2] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    //[3] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

bool oled_task_user(void) {
    //typehud_render();


  oled_write_P(PSTR(" "), false);
  oled_write_P(_BASE, false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("Layer"), false);
  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_ln_P(PSTR(" BAS"), false);
      break;
    //case _TAP:
    //  oled_write_ln_P(PSTR(" TAP"), false);
    //  break;
    case _NUM:
      oled_write_ln_P(PSTR(" NUM"), false);
      break;
    case _NAV:
      oled_write_ln_P(PSTR(" NAV"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR(" UND"), false);
  }


  // oled_write_ln_P(PSTR("-----"), false);
  // oled_write_ln_P(PSTR("Stats"), false);

  oled_write_P(PSTR("BASE: "), false);
  if(layer_state_is(_BASE))
    oled_write_P(PSTR("ON  "), false);
  else
    oled_write_P(PSTR("OFF "), false);

  // oled_write_ln_P(PSTR(" "), false);

  oled_write_P(PSTR("NUM: "), false);
  if(layer_state_is(_NUM))
    oled_write_P(PSTR("ON  "), false);
  else
    oled_write_P(PSTR("OFF "), false);

  oled_write_ln_P(PSTR(""), false);

  oled_write_P(PSTR("NAV: "), false);
  if(layer_state_is(_NAV))
    oled_write_P(PSTR("ON  "), false);
  else
    oled_write_P(PSTR("OFF "), false);

  // oled_write_ln_P(PSTR(""), false);

  //oled_write_P(PSTR("TAP: "), false);
  //if(layer_state_is(_TAP))
  //  oled_write_ln_P(PSTR("ON"), false);
  //else
  //  oled_write_ln_P(PSTR("OFF"), false);

  oled_write_ln_P(PSTR(""), false);

  return false;
}
 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //typehud_process_record(record);

       // Host Keyboard Layer Status
 

    return true;
}
