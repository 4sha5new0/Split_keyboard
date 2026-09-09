#include QMK_KEYBOARD_H

// L-hand unit: plain 17-key board (Ctrl now here, swapped with R-hand's
// Shift so that Shift lives on the same physical device as the L-Sy/L-No
// combo logic). All special L-Sy / L-No / L-Op layer logic lives on the
// R-hand unit (see kb2_r/keymaps/default/keymap.c).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_LCTL, KC_D, KC_R, KC_S, KC_I,
        KC_Q,    KC_K, KC_T, KC_E, KC_W,
        KC_X,    KC_B, KC_F, KC_J, KC_SPC, KC_BSPC, KC_ENT
    )
};
