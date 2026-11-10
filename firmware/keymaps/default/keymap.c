// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    NEXT_LYR = SAFE_RANGE, //custom keycode for changing layers
};

enum layers {
    _BASE,
    _MATH,
    _ONSHAPE,
    LAYER_COUNT //variable for what layer it is on
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_ENCODERS] = { //just keycodes for rotary encoder
    [_BASE] = { KC_VOLU, KC_VOLD },
    [_MATH] = { KC_VOLU, KC_VOLD },
    [_ONSHAPE] = { KC_VOLU, KC_VOLD }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) { //function for layer key
    if (keycode == NEXT_LYR){
        if (record->event.pressed) { //when the button is pressed
            uint8_t now = get_highest_layer(layer_state); //see what the layer is rn
            uint8_t next = (now + 1) % LAYER_COUNT; //set the new layer number, and then if it's three it'll be 0
            layer_move(next); //actually make the layer that number
        }
        return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layerNumber = get_highest_layer(state);        // see what the layer is rn

    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);    
    rgblight_sethsv_noeeprom(HSV_OFF);                     // clears all LEDs
    rgblight_sethsv_at(HSV_GREEN, 0);                      // LED 0 is always green
    rgblight_sethsv_range(HSV_WHITE, 1, layerNumber + 2);  // layer 0 = 1 LED, 1 = 2 LED, 2 = 3 LED
    return state;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();                 // LEDs on, without saving
    layer_state_set_user(layer_state);          // draw the starting layer's LEDs
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */


     //C(KC) and C holds down control and then you put what you want after KC
     //S(KC) and S holds down shift and then you put what you want after KC
    //A(KC) and A holds down alt and then you put what you want after KC
    //refer to https://docs.qmk.fm/keycodes_basic for further keycodes

    //Each number in the brackets indicates what number layer it is

    [_BASE] = LAYOUT_ortho_2x3( //default layout

        //G is cmd, but C is ctrl, so use G

        NEXT_LYR, //next layer (obviously)
        //skeeo   cmd+w    new bowser search
        KC_SLEP, G(KC_W), KC_WWW_SEARCH,
        //%       launchpad      Raycast
        S(KC_5), KC_LAUNCHPAD, A(KC_SPACE)
    ),
    [_MATH] = LAYOUT_ortho_2x3( //math layout
        _______,
        KC_KP_PLUS,    KC_KP_ASTERISK,    KC_KP_SLASH,
        S(KC_COMMA),    S(KC_DOT),    S(KC_6)
    ),
    [_ONSHAPE] = LAYOUT_ortho_2x3(//onshape layout
        _______,
        S(KC_S),    KC_L,    KC_D,
        KC_E,    S(KC_M),    S(KC_W)
    )
};