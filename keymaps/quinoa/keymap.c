#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPCL A(G(KC_LEFT))
#define SPC_R A(G(KC_RGHT))
#define DEL_WORD C(KC_BSPC)
#define LA_SYM MO(SYM)
#define LA_NAV LT(NAV, KC_SPC)
#define OS_LSFT OSM(MOD_LSFT)
#define TAB KC_TAB

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    MED,
};

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
};

enum tap_dance_indexes {
  TD_SEARCH,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  DEFAULT LAYER
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   "   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               |  OSM  |       |       |       |       | 
 * |       |       |       |  NAV  |  SPC  |      ALT      |  LSFT |  SYM  |  TAB  |       |SEARCH |
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
 * 
*/

    [DEF] = LAYOUT(
        KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,     XXXXXXX, XXXXXXX,   KC_J,        KC_L,     KC_U,      KC_Y,      KC_QUOT,
        KC_A,      KC_R,      KC_S,      KC_T,      KC_G,     XXXXXXX, XXXXXXX,   KC_M,        KC_N,     KC_E,      KC_I,      KC_O,
        KC_Z,      KC_X,      KC_C,      KC_D,      KC_V,     XXXXXXX, XXXXXXX,   KC_K,        KC_H,     KC_COMM,   KC_DOT,    KC_SLSH,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   LA_NAV,    KC_SPC,        ALT_TAB,       OS_LSFT,     LA_SYM,   TAB,    XXXXXXX,   TD(TD_SEARCH)
    ),

/*  SYMBOLS LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  ESC  |   [   |   {   |   (   |   ~   |       |       |   ^   |   )   |   }   |   ]   |   `   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |   -   |   *   |   =   |   _   |   $   |       |       |   #   |  CMD  |  ALT  |  CTL  |  SHFT |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |   +   |   |   |   @   |   \   |   %   |       |       |       |   &   |   ;   |   :   |   !   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |       |       |       |  NAV  |  SPC  |      ALT      |  LSFT |  SYM  |       |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

    [SYM] = LAYOUT(
        KC_ESC,    KC_LBRC,   KC_LCBR,   KC_LPRN,   KC_TILD,  XXXXXXX, XXXXXXX,   KC_CIRC,  KC_RPRN,  KC_RCBR,   KC_RBRC,   KC_GRV,
        KC_MINS,   KC_ASTR,   KC_EQL,    KC_UNDS,   KC_DLR,   XXXXXXX, XXXXXXX,   KC_HASH,  OS_CMD,   OS_ALT,    OS_CTRL,   OS_SHFT,
        KC_PLUS,   KC_PIPE,   KC_AT,     KC_BSLS,   KC_PERC,  XXXXXXX, XXXXXXX,   KC_NO,    KC_AMPR,  KC_SCLN,   KC_COLN,   KC_EXLM,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   _______,       ALT_TAB,       _______,  _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

/*  NAVIGATION LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  TAB  |  SWIN |  TABL |  TABR |  VOLU |       |       |  BOOT |  HOME |   UP  |  END  |  DELW |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  SHFT |  CTRL |  ALT  |  CMD  |  VOLD |       |       |  TOGG |  LEFT |  DOWN | RIGHT |  BSPC |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  SPCL |  SPCR |  BACK |  FWD  |  MPLY |       |       |       |  PGDN |  PGUP |       |  ENT  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |       |       |       |  NAV  |  SPC  |      ALT      |  LSFT |  SYM  |       |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

    [NAV] = LAYOUT(
        KC_TAB,    SW_WIN,    TABL,      TABR,      KC_VOLU,  XXXXXXX, XXXXXXX,   QK_BOOT,  HOME,     KC_UP,     END,       DEL_WORD,
        OS_SHFT,   OS_CTRL,   OS_ALT,    OS_CMD,    KC_VOLD,  XXXXXXX, XXXXXXX,   CW_TOGG,  KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
        SPCL,      SPC_R,     BACK,      FWD,       KC_MPLY,  XXXXXXX, XXXXXXX,   KC_NO,    KC_PGDN,  KC_PGUP,   XXXXXXX,   KC_ENT,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   _______,       ALT_TAB,       _______,  _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

/*  NUMPAD LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |   1   |   2   |   3   |   4   |   5   |       |       |   6   |   7   |   8   |   9   |   0   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  SHFT |  CTRL |  ALT  |  CMD  |  F11  |       |       |  F12  |  CMD  |  ALT  |  CTRL |  SHFT |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  F1   |  F2   |  F3   |  F4   |  F5   |       |       |  F6   |  F7   |  F8   |  F9   |  F10  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |       |       |       |  NAV  |  SPC  |      ALT      |  LSFT |  SYM  |       |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

    [NUM] = LAYOUT(
        KC_1,      KC_2,      KC_3,      KC_4,      KC_5,     XXXXXXX, XXXXXXX,   KC_6,     KC_7,     KC_8,      KC_9,      KC_0,
        OS_SHFT,   OS_CTRL,   OS_ALT,    OS_CMD,    KC_F11,   XXXXXXX, XXXXXXX,   KC_F12,   OS_CMD,   OS_ALT,    OS_CTRL,   OS_SHFT,
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,   KC_F6,    KC_F7,    KC_F8,     KC_F9,     KC_F10,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   _______,       ALT_TAB,       _______,  _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

/*  MEDIA LAYER
*/

    [MED] = LAYOUT(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  XXXXXXX, XXXXXXX,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  XXXXXXX, XXXXXXX,   KC_T,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  XXXXXXX, XXXXXXX,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   _______,       ALT_TAB,       _______,  _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

};

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

// ====================================================
// Callum One-Shot Modifiers
// ====================================================

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Alt-Tab
    switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_RALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }

    // Callum One-Shot Modifiers
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

// Timer for alt-tab
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 300) {
      unregister_code(KC_RALT);
      is_alt_tab_active = false;
    }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, SYM, OS_LSFT, NUM);
// }