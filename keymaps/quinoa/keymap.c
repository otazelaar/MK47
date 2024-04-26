#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"
#include "keymaps.h"

#define HOME G(KC_UP)
#define END G(KC_DOWN)
#define BACK G(KC_LBRC)
#define FORWD G(KC_RBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define DEL_WORD A(KC_BSPC)
#define DEL_LINE G(KC_BSPC)
#define SPOTL G(KC_SPC)
#define LA_SYM OSL(SYM)
#define LA_NAV LT(NAV, KC_SPC)
#define LA_R_NAV LT(NAV, KC_TAB)
#define LA_MEDIA OSL(MED)
#define LA_NUM MO(NUM)
#define UNDO G(KC_Z)
#define REDO LSFT(G(KC_Z))

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    MED,
};

enum custom_keycodes {
    REPEAT = SAFE_RANGE,
    SELWORD,
};

enum tap_dance_indexes {
    TD_SEARCH,
};

enum combo_events {
    // Left Side
    COMBO_SHIFT_LEFT,
    COMBO_TAB,
    COMBO_UNDO,
    COMBO_REDO,

    // Right Side
    COMBO_SHIFT_RIGHT,
    COMBO_ENTER,
    LA_COMBO_NAV_TO_SYM,
    LA_COMBO_SYM_TO_NAV,
    COMBO_BSPC,
    COMBO_DELETE,
    COMBO_DELETE_LINE,
    COMBO_COUNT,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
};

// Left Side
const uint16_t PROGMEM shift_left_combo[] = {KC_A, KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM redo_combo[] = {KC_Z, KC_X, KC_C, KC_D, COMBO_END};

// Right Side
const uint16_t PROGMEM shift_right_combo[] = {KC_N, KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM nav_to_sym_combo[] = {KC_TAB, LA_SYM, COMBO_END};
const uint16_t PROGMEM sym_to_nav_combo[] = {KC_ASTR, LA_NAV, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM delete_line_combo[] = {KC_L, KC_U, KC_Y, KC_QUOT, COMBO_END};

const uint16_t (*keymaps)[MATRIX_ROWS][MATRIX_COLS];

bool process_detected_host_os_kb(os_variant_t detected_os) {
    printf("Using MacOS keymap\n"); // Debug print statement

    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
    case OS_MACOS:
        // keymap_os_mac();
        // keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
        // keymap_config.swap_backslash_backspace = true;
        keymaps.config
        keymaps = keymaps_macos;
        printf("Using MacOS keymap\n"); // Debug print statement
        break;
    case OS_IOS:
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
        break;
    case OS_WINDOWS:
        // keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
        // keymap_config.swap_escape_capslock = true;
        keymaps = keymaps_windows;


        break;
    case OS_LINUX:
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
        break;
    case OS_UNSURE:
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
        break;
    }
    return true;
}

// Keymap
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// #define QUINOA_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(QUINOA_LAYERMAPPING_##LAYER, QUINOA_LAYER_##LAYER),
// QUINOA_LAYER_LIST
// #undef QUINOA_X
// };

// Tap Dance Definitions
void tap_dance_search(tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) {
                // Open new tab an start search with "reddit"
                SEND_STRING(SS_LCTL("t"));
                SEND_STRING("reddit ");
        } else if (state->count == 2) {
                // Send the URL for Gmail and press Enter
                SEND_STRING(SS_LCTL("t"));
                SEND_STRING("https://mail.google.com\n");
        } else if (state->count == 3) {
                // add archive string to cursor location for free articles
                SEND_STRING("archive.is/");
        }
}

tap_dance_action_t tap_dance_actions[] = {
        [TD_SEARCH] = ACTION_TAP_DANCE_FN(tap_dance_search),
};

// Callum One-Shot Modifiers
bool is_oneshot_cancel_key(uint16_t keycode) {
        switch (keycode) {
        // Cancel unused modifiers by tapping nav or sym.
        case LA_SYM:
        case LA_NAV:
                return true;
        default:
                return false;
        }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
        switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
                return true;
        default:
                return false;
        }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool sw_win_active = false;

bool process_oneshot(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);
    return true;
}

bool process_update_sw_win(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_oneshot(keycode, record)) return false;
    if (!process_update_sw_win(keycode, record)) return false;
    return true;
}

// void process_platform_combo(uint16_t keycode, keyrecord_t *record) {
//     uint8_t host_os = guess_host_os();
//     uint16_t keycode_to_press = KC_NO;

//     if (host_os == OS_MACOS || host_os == OS_IOS) {
//         switch (keycode) {
//         case USR_COPY:
//             keycode_to_press = G(KC_C);
//             break;
//         case USR_PASTE:
//             keycode_to_press = G(KC_V);
//             break;
//         }
//     } else {
//         switch (keycode) {
//         case USR_COPY:
//             keycode_to_press = C(KC_C);
//             break;
//         case USR_PASTE:
//             keycode_to_press = C(KC_V);
//             break;
//         }
//     }
//     if (record->event.pressed) {
//         register_code16(keycode_to_press);
//     } else {
//         unregister_code16(keycode_to_press);
//     }
// }

void process_combo_event(uint16_t combo_index, bool pressed) {

    switch(combo_index) {
        case COMBO_SHIFT_LEFT:
            if (pressed) {
                layer_on(1);
            } else {
                layer_off(1);
            }
            break;
    }

    switch(combo_index) {
        case LA_COMBO_NAV_TO_SYM:
            if (pressed) {
                layer_on(3);
            } else {
                layer_off(3);
            }
            break;
    }

    switch(combo_index) {
        case LA_COMBO_SYM_TO_NAV:
            if (pressed) {
                layer_on(3);
            } else {
                layer_off(3);
            }
            break;
    }

    switch(combo_index) {
        case COMBO_ENTER:
            if (pressed) {
                layer_on(3);
            } else {
                layer_off(3);
            }
            break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
    return update_tri_layer_state(state, NAV, SYM, NUM);
}

combo_t key_combos[COMBO_COUNT] = {
    // Left Side
    [COMBO_SHIFT_LEFT] = COMBO(shift_left_combo, OS_SHFT),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_UNDO] = COMBO(undo_combo, UNDO),
    [COMBO_REDO] = COMBO(redo_combo, REDO),

    // Right Side
    [COMBO_SHIFT_RIGHT] = COMBO(shift_right_combo, OS_SHFT),
    [COMBO_ENTER] = COMBO(enter_combo, KC_ENT),
    [LA_COMBO_NAV_TO_SYM] = COMBO(nav_to_sym_combo, LA_NAV),
    [LA_COMBO_SYM_TO_NAV] = COMBO(sym_to_nav_combo, LA_SYM),
    [COMBO_BSPC] = COMBO(bspc_combo, KC_BSPC),
    [COMBO_DELETE] = COMBO(delete_combo, DEL_WORD),
    [COMBO_DELETE_LINE] = COMBO(delete_line_combo, DEL_LINE),
};
