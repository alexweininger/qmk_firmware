#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"
#include "util.h"


extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16
#define _ARROWS 5
#define _CODE 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  ARROWS,
  CODE
};

//Tap Dance Declarations
enum {
  TD_CAPS = 0,
  TD_HOMEEND,
  TD_UND,
  TD_EQL
};

//Tap ``Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for lsft, twice for Caps Lock
  [TD_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [TD_HOMEEND] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TD_UND] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
  [TD_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS)
// Other declarations would go here, separated by commas, if you have them
};

#define LOW MO(_LOWER)
#define RSE MO(_RAISE)
#define CODE MO(_CODE)
#define EISU MO(_ADJUST)
#define ADJ MO(_ADJUST)
#define ARR MO(_ARROWS)
#define LO_ENT LT(_LOWER, KC_ENT)
#define RA_ENT LT(_RAISE, KC_ENT)
#define TAB_ARR LT(_ARROWS, KC_TAB)
#define HHOME LSFT(KC_HOME)
#define HEND LSFT(KC_END)
#define HOMEEND TD(TD_HOMEEND)
#define SHIFCAP TD(TD_CAPS)
#define CPYDWN LSFT(LALT(KC_DOWN))
#define CPYUP LSFT(LALT(KC_UP))
#define CURSDWN LCTL(LALT(KC_DOWN))
#define CURSUP LCTL(LALT(KC_UP))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |    1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  | Home |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  `   |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | LAlt |                    | Space|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Shift| Ctrl | Bksp |||||||| Bksp | Space|LO/ENT|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , TD(TD_UND),                    TD(TD_EQL) , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, \
    KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_LBRC,                       KC_RBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_HOME, \
    TAB_ARR, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , HOMEEND,                       KC_BSPC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    ARR    , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LALT,                       CODE   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT , \
    KC_LCTL, KC_LGUI, KC_LALT, KC_LEAD,         KC_LCTL , SHIFCAP,  RSE,           KC_SPC, SHIFCAP, LOW  ,          KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   _  |                    |   +  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |   {  |                    |   }  |   ^  |  PT  |   Up |  NT  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |  Del |                    | Bksp | HHOME| Left | Down | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|  HEND|   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|      ||||||||      | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_UNDS,                      KC_PLUS, KC_F6  , KC_F7  , KC_F8  , KC_F9,   KC_F10,  KC_F12,  \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LCBR,                      KC_RCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_DEL ,                      KC_DEL ,  HHOME , KC_LEFT, KC_DOWN, KC_RGHT, KC_COLN, KC_DQT , \
    EISU,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SPC ,                      KC_ENT , HEND   , KC_M   , KC_LT  , KC_GT,   KC_QUES, KC_RSFT, \
    _______, KC_LGUI, _______, ADJ,              KC_LSFT, KC_SPC ,LCTL(KC_DEL), _______,KC_ENT , RAISE  ,          KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|      ||||||||      | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_F11,  LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),   KC_UNDS,                        KC_PLUS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LCBR,                        KC_RCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F1, \
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TAB ,                        KC_BSPC, KC_H,    KC_J,    KC_K,    KC_L,    KC_COLN, KC_DQT , \
    KC_LSFT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SPC ,                        KC_ENT , KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, LSFT(LCTL(KC_ENT)), \
    KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC ,LCTL(KC_BSPC),   KC_SPC,KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC, BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, VLK_TOG, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  ),


  [_ARROWS] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, LCTL(KC_PGUP), KC_UP  , LCTL(KC_PGDN), _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, LALT(KC_SPC),          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  ),
    [_CODE] = LAYOUT(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , TD(TD_UND),                    KC_EQL , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, \
    KC_GRV , KC_Q   , KC_W   , KC_E   , CURSUP   , CPYUP   , KC_LBRC,                       KC_RBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_HOME, \
    TAB_ARR, KC_A   , KC_S   , LCTL(LSFT(KC_K)), KC_F1  , CPYDWN   , HOMEEND,                       KC_BSPC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    ARR    , KC_Z   , KC_X   , KC_C   , CURSDWN   , KC_B   , KC_LALT,                       CODE   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, LSFT(LCTL(KC_ENT)) , \
    KC_LCTL, KC_LGUI, KC_LALT, KC_LEAD,         SHIFCAP, KC_LCTL, RSE,           KC_SPC, LOW    , SHIFCAP,          KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
  ),

    /* blank layout
  LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
  */
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

LEADER_EXTERNS(); // ! must come before matrix scan user

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Replace the sequence below with your own sequences.
    SEQ_ONE_KEY(KC_T) {
      // When I press KC_LEAD and then T, this sends CTRL + SHIFT + T
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
    }

    SEQ_ONE_KEY(KC_1) {
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
    }

    SEQ_ONE_KEY(KC_MINS) {
      SEND_STRING(SS_LSFT("-"));
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;

  // arrow layer
  case ARROWS:
      if (record->event.pressed) {
        layer_on(_ARROWS);
      } else {
        layer_off(_ARROWS);
      }
      return false;
      break;
  }
  return true;
}

/*
 * RGB Modes
 * 1 = Static
 * 2-5 = Breathing
 * 6-8 = Rainbow
 * 9-14 = Swirl
 * 15-20 = Snake
 * 21-24 = Nightrider
 * 25 = Christmas
 * 26-30 = Static Gradient
 */
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 10}; // Set the last one to 10ms for some speedy swirls

uint8_t prev = _QWERTY;
uint32_t check;
uint32_t desired = 9;

void matrix_init_user() {
    rgblight_mode(desired);
}

// function to change rgb modes based on layers
uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (prev!=_ADJUST) {
      switch (layer) {
        case _QWERTY:
          rgblight_mode(desired);
          break;

        case _LOWER: // If we're in swirl mode, then speed up the swirls, otherwise breathe
          check = rgblight_get_mode();
          if (check > 8 && check < 15) {
            rgblight_mode(14);
          } else {
            rgblight_mode(5);
          }
          break;

        case _RAISE: // Same as above but reverse direction, otherwise nightrider
          check = rgblight_get_mode();
          if (check > 8 && check < 15) {
            rgblight_mode(13);
          } else {
            rgblight_mode(23);
          }
          break;

        case _ARROWS: // set a specific led red
          rgblight_setrgb_at(0xff, 0x0, 0x0, 1);
          break;

        case _ADJUST:
          break;
      }
  } else {
      desired = rgblight_get_mode();
  }
  prev = layer;
  return state;
}
