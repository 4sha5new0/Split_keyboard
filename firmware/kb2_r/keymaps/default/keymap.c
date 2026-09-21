#include QMK_KEYBOARD_H

// ---------------------------------------------------------------------
// R-hand unit. Layers now match the layout exported from Vial (r.vil):
// standard momentary layers (MO), not custom intercepted keycodes. QMK
// stacks momentary layers natively - holding two or three of L-No/L-Sy/
// L-Op at once already resolves correctly (highest active layer's
// non-KC_TRNS key wins, falling through to lower layers/base), so no
// extra process_record_user logic is needed for "layer key combos".
// Using plain layers also means Vial can keep editing this keymap live.
// ---------------------------------------------------------------------

enum layers {
    _BASE = 0,
    _L_NO,   // MO(1) - held on the L-No key (row2,col4)
    _L_SY,   // MO(2) - held on the L-Sy key (row2,col5)
    _L_OP,   // MO(3) - held on the L-Op key (row2,col6)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_LSFT, KC_N,   KC_Y,   KC_U,   KC_O,
        KC_P,    KC_G,   KC_H,   KC_A,   KC_M,
        KC_Z,    KC_V,   KC_C,   KC_L,   MO(_L_NO), MO(_L_SY), MO(_L_OP)
    ),

    [_L_NO] = LAYOUT(
        KC_LNG2, KC_9,    KC_8,    KC_7,    KC_0,
        KC_F12,  KC_6,    KC_5,    KC_4,    KC_TRNS,
        KC_TRNS, KC_3,    KC_2,    KC_1,    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_L_SY] = LAYOUT(
        KC_LNG1, KC_TRNS, KC_TRNS, KC_NUHS, KC_RBRC,
        KC_TRNS, KC_EQL,  KC_QUOT, KC_SCLN, KC_MINS,
        KC_LBRC, KC_INT3, KC_INT1, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_L_OP] = LAYOUT(
        KC_ESC,  KC_TRNS, KC_DOT,  KC_COMM, KC_LGUI,
        KC_HOME, KC_TRNS, KC_UP,   KC_LALT, KC_TAB,
        KC_END,  KC_RGHT, KC_DOWN, KC_LEFT, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
