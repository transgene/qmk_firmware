// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif 

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance declarations
enum {
    TD_ML_FNAV_EN,      // 0x5700
    TD_NOP_DF_NORMIE,   // 0x5701
    TD_NOP_DF_HOMEROW   // 0x5702
};

// Layers' aliases
#define HOMEROW_LAYER 0
#define NORMIE_LAYER 1
#define FUNC_NAV_LAYER 2
#define DYN_TAP_LAYER 3

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Layer mods
#define ML_FNAV_EN TD(TD_ML_FNAV_EN)
#define NOP_DF_NORM TD(TD_NOP_DF_NORMIE)
#define NOP_DF_HROW TD(TD_NOP_DF_HOMEROW)
#define SPC_ML_DT LT(DYN_TAP_LAYER, KC_SPC)

// One-shot keys
#define OSM_LSFT OSM(MOD_LSFT)

// Other keys
#define MIC_MUTE SGUI(KC_A) // Configured in PowerToys

  

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │Spc│Mut│   │   |Spc|Alt│App│Ctl│   │Mo1|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */

    [HOMEROW_LAYER] = LAYOUT_all(
        QK_GESC,       KC_1,       KC_2,      KC_3,       KC_4,        KC_5,       KC_6,       KC_7,       KC_8,     KC_9,         KC_0,    KC_MINS,     KC_EQL,    KC_BSPC, 
         KC_TAB,       KC_Q,       KC_W,      KC_E,       KC_R,        KC_T,       KC_Y,       KC_U,       KC_I,     KC_O,         KC_P,    KC_LBRC,    KC_RBRC,    KC_BSLS, 
     ML_FNAV_EN,      GUI_A,      ALT_S,     CTL_D,      SFT_F,        KC_G,       KC_H,      SFT_J,      CTL_K,    ALT_L,     GUI_SCLN,    KC_QUOT,                 KC_ENT, 
          KC_NO,       KC_Z,       KC_X,      KC_C,       KC_V,        KC_B,       KC_N,       KC_M,    KC_COMM,   KC_DOT,      KC_SLSH,                KC_LSFT, 
          KC_NO,      KC_NO,      KC_NO,                KC_SPC,      KC_SPC,    KC_MPLY,              SPC_ML_DT,    KC_NO,        KC_NO,      KC_NO,            NOP_DF_NORM
    ),

    [NORMIE_LAYER] = LAYOUT_all(
        QK_GESC,       KC_1,       KC_2,      KC_3,       KC_4,        KC_5,       KC_6,       KC_7,       KC_8,     KC_9,         KC_0,        KC_MINS,     KC_EQL,    KC_BSPC, 
         KC_TAB,       KC_Q,       KC_W,      KC_E,       KC_R,        KC_T,       KC_Y,       KC_U,       KC_I,     KC_O,         KC_P,        KC_LBRC,    KC_RBRC,    KC_BSLS, 
     ML_FNAV_EN,       KC_A,      KC_S,       KC_D,       KC_F,        KC_G,       KC_H,       KC_J,       KC_K,     KC_L,      KC_SCLN,        KC_QUOT,                 KC_ENT, 
        KC_LSFT,       KC_Z,       KC_X,      KC_C,       KC_V,        KC_B,       KC_N,       KC_M,    KC_COMM,   KC_DOT,      KC_SLSH,                    KC_RSFT, 
        KC_LCTL,    KC_LGUI,    KC_LALT,                KC_SPC,      KC_SPC,    KC_MPLY,                 KC_SPC,  KC_RALT,       KC_APP,    NOP_DF_HROW,                KC_RCTL
    ),

    [FUNC_NAV_LAYER] = LAYOUT_all(
        KC_TRNS,      KC_F1,      KC_F2,      KC_F3,        KC_F4,        KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,     KC_F10,     KC_F11,     KC_F12,    KC_DEL, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    LSA(KC_2),    LSA(KC_3),    KC_TRNS,    KC_HOME,    KC_PGUP,    KC_PGDN,     KC_DEL,    KC_BSPC,     KC_INS,   KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_LEFT,    KC_DOWN,      KC_UP,    KC_RGHT,     KC_END,    KC_PSCR,               KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,                   KC_SPC,       KC_SPC,   MIC_MUTE,                 KC_SPC,    KC_TRNS,    KC_TRNS,    KC_TRNS,               KC_TRNS
    ),

    [DYN_TAP_LAYER] = LAYOUT_all(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    DT_DOWN,      DT_UP,   DT_PRNT, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,               KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS, 
        KC_TRNS,    KC_TRNS,    KC_TRNS,                  KC_TRNS,      KC_MRWD,    KC_TRNS,                KC_MFFD,    KC_TRNS,    KC_TRNS,    KC_TRNS,               KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [3] = { ENCODER_CCW_CW(KC_MRWD, KC_MFFD) }
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Indicate Caps Word is on
    if ((led_min <= 41 || led_max >= 52) && is_caps_word_on()) { 
        rgb_matrix_set_color(41, RGB_WHITE); // Left Shift
        rgb_matrix_set_color(52, RGB_WHITE); // Right Shift
    }

    // Indicate that the "normal" layer is on
    if (get_highest_layer(default_layer_state) == NORMIE_LAYER) {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0x99, 0x00, 0x00);
    }

    // Highlight aux layers
    if (IS_LAYER_ON(FUNC_NAV_LAYER)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0x00, 0xFF, 0x00);
    }
    if (IS_LAYER_ON(DYN_TAP_LAYER)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 0xFF, 0xD9, 0x00);
    }

    return true;
}

// TODO: refactor and add comments (https://docs.qmk.fm/features/tap_dance#example-6) - START
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            layer_on(FUNC_NAV_LAYER);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LSA(KC_1));        
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(FUNC_NAV_LAYER);
    }
    ql_tap_state.state = TD_NONE;
}

void dance_to_normie_layer(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set(0x00000002);
        reset_tap_dance(state);
    }
}

void dance_to_homerow_layer(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set(0x00000001);
        reset_tap_dance(state);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ML_FNAV_EN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset), // Hold to turn on func-and-nav layer, twice for English layout
    [TD_NOP_DF_NORMIE] = ACTION_TAP_DANCE_FN(dance_to_normie_layer),
    [TD_NOP_DF_HOMEROW] = ACTION_TAP_DANCE_FN(dance_to_homerow_layer),
};
// TODO - END

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ML_FNAV_EN:
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_A:
        case ALT_S:
        case CTL_D:
        case SFT_F:
        case SFT_J:
        case CTL_K:
        case ALT_L:
        case GUI_SCLN:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t command = data[0];
    switch (command) {
        case 0x30:
            uprintf("Turning RGB off\n");
            rgb_matrix_sethsv(21, 255, 1);
            break;
        case 0x31:
            uprintf("Turning RGB on\n");
            rgb_matrix_sethsv(21, 255, 150);
            break;
        default:
            uprintf("Unknown command: 0x%02X\n", command);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    uprintf("Default layer is: %u\n", get_highest_layer(default_layer_state));
#endif 
  return true;
}
