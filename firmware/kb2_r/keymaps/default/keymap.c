#include QMK_KEYBOARD_H

// ---------------------------------------------------------------------
// R-hand unit: carries the three layer/modifier keys L-Sy / L-No / L-Op,
// and now also Shift (swapped with Ctrl, which moved to the L-hand unit).
// Putting Shift here means "L-No + Shift + <numbered key>" can finally be
// detected locally via get_mods() - previously Shift lived on the other,
// electrically independent USB keyboard and this wasn't possible.
// ---------------------------------------------------------------------

enum custom_keycodes {
    LY_SY = SAFE_RANGE,
    LY_NO,
    LY_OP,
    K_U, K_Y, K_N, K_A, K_H, K_G, K_P, K_L, K_C, K_V, K_Z, K_O, K_M,
};

static bool ls_held = false;  // L-Sy
static bool ln_held = false;  // L-No
static bool lo_held = false;  // L-Op

typedef struct {
    uint16_t plain;         // top legend - always used as the fallback
    uint16_t no_symbol;     // L-No alone                  (KC_NO = undefined -> fallback to plain)
    uint16_t no_shift_sym;  // L-No + Shift (numbered key)  (KC_NO = undefined -> fallback to plain)
    uint16_t sy_nav;        // L-Sy alone                  (KC_NO = undefined -> fallback to plain)
    uint16_t sy_shift;      // L-Sy + Shift                (KC_NO = undefined -> fallback to plain)
    uint16_t fn_key;        // L-No + L-Op together        (KC_NO = undefined -> fallback to plain)
} key_combo_t;

// Order must match the enum list above (K_U .. K_M).
static const key_combo_t combo_table[] = {
    /* K_U */ { KC_U, KC_LCBR, KC_AMPR, KC_NO,   KC_LBRC, KC_F7  },
    /* K_Y */ { KC_Y, KC_RCBR, KC_ASTR, KC_NO,   KC_RBRC, KC_F8  },
    /* K_N */ { KC_N, KC_COLN, KC_LPRN, KC_NO,   KC_SCLN, KC_F9  },
    /* K_A */ { KC_A, KC_COMM, KC_DLR,  KC_LALT, KC_LT,   KC_F4  },
    /* K_H */ { KC_H, KC_DOT,  KC_PERC, KC_UP,   KC_GT,   KC_F5  },
    /* K_G */ { KC_G, KC_DQT,  KC_CIRC, KC_ESC,  KC_QUOT, KC_F6  },
    /* K_P */ { KC_P, KC_NO,   KC_NO,   KC_HOME, KC_BSLS, KC_NO  }, // no L-No symbol, no Fn number (confirmed)
    /* K_L */ { KC_L, KC_PLUS, KC_EXLM, KC_LEFT, KC_EQL,  KC_F1  },
    /* K_C */ { KC_C, KC_UNDS, KC_AT,   KC_DOWN, KC_MINS, KC_F2  },
    /* K_V */ { KC_V, KC_TILD, KC_HASH, KC_RGHT, KC_QUOT, KC_F3  },
    /* K_Z */ { KC_Z, KC_NO,   KC_NO,   KC_END,  KC_SLSH, KC_NO  }, // no L-No symbol, no Fn number (confirmed)
    /* K_O */ { KC_O, KC_NO,   KC_NO,   KC_LGUI, KC_NO,   KC_F12 },
    /* K_M */ { KC_M, KC_NO,   KC_RPRN, KC_TAB,  KC_NO,   KC_F10 }, // "0" read as the 10th digit -> F10 (assumption, please confirm)
};

static uint16_t or_fallback(uint16_t code, uint16_t fallback) {
    return (code == KC_NO) ? fallback : code;
}

static void handle_combo_key(const key_combo_t *k, bool shift_held) {
    if (ln_held && lo_held) {
        tap_code16(or_fallback(k->fn_key, k->plain));
        return;
    }
    if (ln_held && shift_held) {
        tap_code16(or_fallback(k->no_shift_sym, k->plain));
        return;
    }
    if (ln_held) {
        tap_code16(or_fallback(k->no_symbol, k->plain));
        return;
    }
    if (ls_held) {
        tap_code16(or_fallback(shift_held ? k->sy_shift : k->sy_nav, k->plain));
        return;
    }
    tap_code16(k->plain);
}

// fires once, at the moment a layer key press makes a qualifying
// layer-key-only combo newly true
static void check_layer_key_combo(void) {
    if (ls_held && ln_held && lo_held) {
        tap_code(KC_LNG5);               // 全角/半角 toggle (JIS Zenkaku/Hankaku key)
    } else if (ls_held && lo_held && !ln_held) {
        tap_code(KC_COMM);              // "," (IME renders as "、" in full-width mode)
    } else if (ls_held && ln_held && !lo_held) {
        tap_code(KC_DOT);               // "." (IME renders as "。" in full-width mode)
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shift_held = (get_mods() & MOD_MASK_SHIFT) != 0;  // Shift is local to this board now

    switch (keycode) {
        case LY_SY:
            ls_held = record->event.pressed;
            if (record->event.pressed) check_layer_key_combo();
            return false;
        case LY_NO:
            ln_held = record->event.pressed;
            if (record->event.pressed) check_layer_key_combo();
            return false;
        case LY_OP:
            lo_held = record->event.pressed;
            if (record->event.pressed) check_layer_key_combo();
            return false;
    }

    if (keycode >= K_U && keycode <= K_M) {
        if (record->event.pressed) {
            handle_combo_key(&combo_table[keycode - K_U], shift_held);
        }
        return false; // tap_code16 above already sends a full press+release
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_LSFT, K_N,  K_Y,  K_U,  K_O,
        K_P,     K_G,  K_H,  K_A,  K_M,
        K_Z,     K_V,  K_C,  K_L,  LY_NO, LY_SY, LY_OP
    )
};
