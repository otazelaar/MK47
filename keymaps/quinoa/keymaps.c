// keymaps.c

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

const uint16_t PROGMEM; keymaps_windows[][MATRIX_ROWS][MATRIX_COLS] = {
    // Define keymaps for Windows

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
};

const uint16_t PROGMEM keymaps_macos[][MATRIX_ROWS][MATRIX_COLS] = {
    // Define keymaps for MacOS

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
};
