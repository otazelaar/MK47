#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"
#include "keymap.h"

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }   
    switch (detected_os) {
    case OS_MACOS:
        // keymap_os_mac();
        // keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
        // keymap_config.swap_backslash_backspace = true;

        /*  DEFAULT LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   ?   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |   <   |   >   |   ?   |
        * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |               |       |       |       |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SOTLT     |NAV-TAB|  SYM  | MEDIA |       |SEARCH |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [DEF] = LAYOUT(
            KC_Q,      KC_W,      KC_F,      KC_P,     KC_B,     XXXXXXX, XXXXXXX,   KC_J,      KC_L,     KC_U,      KC_Y,      KC_QUES,
            KC_A,      KC_R,      KC_S,      KC_T,     KC_G,     XXXXXXX, XXXXXXX,   KC_M,      KC_N,     KC_E,      KC_I,      KC_O,
            KC_Z,      KC_X,      KC_C,      KC_D,     KC_V,     XXXXXXX, XXXXXXX,   KC_K,      KC_H,     KC_SLSH,   KC_COMM,   KC_DOT,
            KC_MCTL,   KC_LPAD,   QK_REP,    LA_NAV,   OS_SHFT,        SPOTL,        LA_R_NAV,  LA_SYM,   LA_MEDIA,  XXXXXXX,   TD(TD_SEARCH)
        ),

        /*  SYMBOLS LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   \   |   [   |   (   |   {   |  ESC  |       |       |   ^   |   }   |   )   |   ]   |   "   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   !   |   '   |   :   |   _   |   ~   |       |       |   #   |  CMD  |  ALT  |  CTRL |  SHFT |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |   $   |   &   |   +   |   -   |   %   |       |       |   |   |   @   |   ;   |   =   |   *   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |  HOLD |       |       |       | 
        * |       |       |  REP  |  NAV  |  SHFT |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [SYM] = LAYOUT(
            KC_BSLS,  KC_LBRC,  KC_LPRN,  KC_LCBR,   KC_ESC,   XXXXXXX, XXXXXXX,  KC_CIRC,  KC_RCBR,  KC_RPRN,  KC_RBRC,   KC_DQT,
            KC_EXLM,  KC_QUOT,  KC_COLN,  KC_UNDS,   KC_TILD,  XXXXXXX, XXXXXXX,  KC_HASH,  OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT, 
            KC_DLR,   KC_AMPR,  KC_PLUS,  KC_MINS,   KC_PERC,  XXXXXXX, XXXXXXX,  KC_PIPE,  KC_AT,    KC_SCLN,  KC_EQL,    LT(LA_NAV, KC_Y),
            XXXXXXX,  XXXXXXX,  _______,  _______,   _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,   XXXXXXX
        ),

        /*  NAVIGATION LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------git +-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  ESC  | SW WIN| TABL  | TABR  |       |       |       |  BOOT |  HOME |   UP  |  END  |  DELW |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * | SHIFT |  CTRL |  ALT  |  CMD  |       |       |       | BACK  | LEFT  | DOWN  | RIGHT |  BSPC |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |       |       |       |  TAB  |       |       |       | FORWD | PG UP | PG DN |  SPC  |  ENT  |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| 
        * |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [NAV] = LAYOUT(
            KC_ESC,            SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, XXXXXXX,  QK_BOOT,  HOME,     KC_UP,     END,       DEL_WORD,
            OS_SHFT,           OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
            LT(LA_SYM, KC_Y),  XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT,
            XXXXXXX,           XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX
        ),

        /*  NUM LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  FN6  |  FN7  |  FN8  |  FN9  | FN10  |       |       |   ,   |   7   |   8   |   9   |   $   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  FN1  |  FN2  |  FN3  |  FN4  |  FN5  |       |       |   0   |   4   |   5   |   6   |  BSPC |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  TAB  | CWTOG | SHIFT |  SPC  |       |       |       |   .   |   1   |   2   |   3   |  ENT  |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       | HOLD  |       |       |       |       | HOLD  |       |       |       |
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [NUM] = LAYOUT(
            KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX, XXXXXXX,  KC_COMM,   KC_7,     KC_8,      KC_9,     KC_DLR,
            KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,  KC_0,      KC_4,     KC_5,      KC_6,     KC_BSPC,
            KC_TAB,    CW_TOGG,   KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,  KC_DOT,    KC_1,     KC_2,      KC_3,     KC_ENT,  
            XXXXXXX,   XXXXXXX,   _______,   _______,   _______,       SW_WIN,       _______,   _______,  _______,   XXXXXXX,  XXXXXXX
        ),

        /*  MEDIA LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |       | VOLD  |       | VOLU  |       |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |REWIND | PREV  | MPLY  | NEXT  |  FF   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| 
        * |       |       |       |       |       |       |       |       |       | HOLD  |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */ 
        
        [MED] = LAYOUT(
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  KC_VOLD,  XXXXXXX,  KC_VOLU,  XXXXXXX,
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_MRWD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MFFD,
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    
            XXXXXXX,  XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX
        ),
        break;
    case OS_IOS:
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
        break;
    case OS_WINDOWS:
        // keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
        // keymap_config.swap_escape_capslock = true;

        /*  DEFAULT LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   ?   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |   <   |   >   |   ?   |
        * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |               |       |       |       |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SOTLT     |NAV-TAB|  SYM  | MEDIA |       |SEARCH |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [DEF] = LAYOUT(
            KC_Q,      KC_W,      KC_F,      KC_P,     KC_B,     XXXXXXX, XXXXXXX,   KC_J,      KC_L,     KC_U,      KC_Y,      KC_QUES,
            KC_A,      KC_R,      KC_S,      KC_T,     KC_G,     XXXXXXX, XXXXXXX,   KC_M,      KC_N,     KC_E,      KC_I,      KC_O,
            KC_Z,      KC_X,      KC_C,      KC_D,     KC_V,     XXXXXXX, XXXXXXX,   KC_K,      KC_H,     KC_SLSH,   KC_COMM,   KC_DOT,
            KC_MCTL,   KC_LPAD,   QK_REP,    LA_NAV,   OS_SHFT,        SPOTL,        LA_R_NAV,  LA_SYM,   LA_MEDIA,  XXXXXXX,   TD(TD_SEARCH)
        ),

        /*  SYMBOLS LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   \   |   [   |   (   |   {   |  ESC  |       |       |   ^   |   }   |   )   |   ]   |   "   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |   !   |   '   |   :   |   _   |   ~   |       |       |   #   |  CMD  |  ALT  |  CTRL |  SHFT |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |   $   |   &   |   +   |   -   |   %   |       |       |   |   |   @   |   ;   |   =   |   *   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |  HOLD |       |       |       | 
        * |       |       |  REP  |  NAV  |  SHFT |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [SYM] = LAYOUT(
            KC_BSLS,  KC_LBRC,  KC_LPRN,  KC_LCBR,   KC_ESC,   XXXXXXX, XXXXXXX,  KC_CIRC,  KC_RCBR,  KC_RPRN,  KC_RBRC,   KC_DQT,
            KC_EXLM,  KC_QUOT,  KC_COLN,  KC_UNDS,   KC_TILD,  XXXXXXX, XXXXXXX,  KC_HASH,  OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT, 
            KC_DLR,   KC_AMPR,  KC_PLUS,  KC_MINS,   KC_PERC,  XXXXXXX, XXXXXXX,  KC_PIPE,  KC_AT,    KC_SCLN,  KC_EQL,    LT(LA_NAV, KC_Y),
            XXXXXXX,  XXXXXXX,  _______,  _______,   _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,   XXXXXXX
        ),

        /*  NAVIGATION LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------git +-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  ESC  | SW WIN| TABL  | TABR  |       |       |       |  BOOT |  HOME |   UP  |  END  |  DELW |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * | SHIFT |  CTRL |  ALT  |  CMD  |       |       |       | BACK  | LEFT  | DOWN  | RIGHT |  BSPC |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |       |       |       |  TAB  |       |       |       | FORWD | PG UP | PG DN |  SPC  |  ENT  |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| 
        * |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [NAV] = LAYOUT(
            KC_ESC,            SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, XXXXXXX,  QK_BOOT,  HOME,     KC_UP,     END,       DEL_WORD,
            OS_SHFT,           OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
            LT(LA_SYM, KC_Y),  XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT,
            XXXXXXX,           XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX
        ),

        /*  NUM LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  FN6  |  FN7  |  FN8  |  FN9  | FN10  |       |       |   ,   |   7   |   8   |   9   |   $   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  FN1  |  FN2  |  FN3  |  FN4  |  FN5  |       |       |   0   |   4   |   5   |   6   |  BSPC |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |  TAB  | CWTOG | SHIFT |  SPC  |       |       |       |   .   |   1   |   2   |   3   |  ENT  |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       | HOLD  |       |       |       |       | HOLD  |       |       |       |
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */

        [NUM] = LAYOUT(
            KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX, XXXXXXX,  KC_COMM,   KC_7,     KC_8,      KC_9,     KC_DLR,
            KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,  KC_0,      KC_4,     KC_5,      KC_6,     KC_BSPC,
            KC_TAB,    CW_TOGG,   KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,  KC_DOT,    KC_1,     KC_2,      KC_3,     KC_ENT,  
            XXXXXXX,   XXXXXXX,   _______,   _______,   _______,       SW_WIN,       _______,   _______,  _______,   XXXXXXX,  XXXXXXX
        ),

        /*  MEDIA LAYER
        * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |       | VOLD  |       | VOLU  |       |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |REWIND | PREV  | MPLY  | NEXT  |  FF   |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        * |       |       |       |       |       |       |       |       |       |       |       |       | 
        * |       |       |       |       |       |       |       |       |       |       |       |       |
        * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| 
        * |       |       |       |       |       |       |       |       |       | HOLD  |       |       | 
        * |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
        * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
        */ 
        
        [MED] = LAYOUT(
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  KC_VOLD,  XXXXXXX,  KC_VOLU,  XXXXXXX,
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_MRWD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MFFD,
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    
            XXXXXXX,  XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX
        ),
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