#pragma once

// NOTE: this UID is a placeholder. Generate a real random one before flashing
// (e.g. `python3 -c "import secrets; print([hex(b) for b in secrets.token_bytes(8)])"`)
// and make sure it differs from the R-hand unit's UID.
#define VIAL_KEYBOARD_UID {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}

// Unlock combo: hold Ctrl (row0,col0) + Enter (row2,col6) to unlock Vial.
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 6 }
