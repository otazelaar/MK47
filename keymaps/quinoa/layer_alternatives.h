
// This file is used to define the different layouts for operating systems

#pragma once

// MacOS
#define QUINOA_ALTERNATIVES_DEF_MAC \
KC_Q,      KC_W,      KC_F,      KC_P,     KC_B,     XXXXXXX, XXXXXXX,   KC_J,      KC_L,     KC_U,      KC_Y,      KC_QUES, \
KC_A,      KC_R,      KC_S,      KC_T,     KC_G,     XXXXXXX, XXXXXXX,   KC_M,      KC_N,     KC_E,      KC_I,      KC_O, \
KC_Z,      KC_X,      KC_C,      KC_D,     KC_V,     XXXXXXX, XXXXXXX,   KC_K,      KC_H,     KC_SLSH,   KC_COMM,   KC_DOT, \
KC_MCTL,   KC_LPAD,   QK_REP,    LA_NAV,   OS_SHFT,        SPOTL,        LA_R_NAV,  LA_SYM,   LA_MEDIA,  XXXXXXX,   TD(TD_SEARCH)

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

#define QUINOA_ALTERNATIVES_SYM_MAC \
KC_BSLS,  KC_LBRC,  KC_LPRN,  KC_LCBR,   KC_ESC,   XXXXXXX, XXXXXXX,  KC_CIRC,  KC_RCBR,  KC_RPRN,  KC_RBRC,   KC_DQT, \
KC_EXLM,  KC_QUOT,  KC_COLN,  KC_UNDS,   KC_TILD,  XXXXXXX, XXXXXXX,  KC_HASH,  OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT, \
KC_DLR,   KC_AMPR,  KC_PLUS,  KC_MINS,   KC_PERC,  XXXXXXX, XXXXXXX,  KC_PIPE,  KC_AT,    KC_SCLN,  KC_EQL,    LT(LA_NAV, KC_Y), \
XXXXXXX,  XXXXXXX,  _______,  _______,   _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,   XXXXXXX

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

#define QUINOA_ALTERNATIVES_NAV_MAC \
KC_ESC,            SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, XXXXXXX,  QK_BOOT,  HOME,     KC_UP,     END,       DEL_WORD, \
OS_SHFT,           OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC, \
LT(LA_SYM, KC_Y),  XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT, \
XXXXXXX,           XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX

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

#define QUINOA_ALTERNATIVES_NUM_MAC \
KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX, XXXXXXX,  KC_COMM,   KC_7,     KC_8,      KC_9,     KC_DLR, \
KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,  KC_0,      KC_4,     KC_5,      KC_6,     KC_BSPC, \
KC_TAB,    CW_TOGG,   KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,  KC_DOT,    KC_1,     KC_2,      KC_3,     KC_ENT, \
XXXXXXX,  XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX

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

#define QUINOA_ALTERNATIVES_MED_MAC \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  KC_VOLD,  XXXXXXX,  KC_VOLU,  XXXXXXX, \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_MRWD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MFFD, \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
XXXXXXX,  XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX

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


// Windows

#define QUINOA_ALTERNATIVES_DEF_WIN \
KC_Z,      KC_W,      KC_F,      KC_P,     KC_B,     XXXXXXX, XXXXXXX,   KC_J,      KC_L,     KC_U,      KC_Y,      KC_QUES, \
KC_A,      KC_R,      KC_S,      KC_T,     KC_G,     XXXXXXX, XXXXXXX,   KC_M,      KC_N,     KC_E,      KC_I,      KC_O, \
KC_Z,      KC_X,      KC_C,      KC_D,     KC_V,     XXXXXXX, XXXXXXX,   KC_K,      KC_H,     KC_SLSH,   KC_COMM,   KC_DOT, \
KC_MCTL,   KC_LPAD,   QK_REP,    LA_NAV,   OS_SHFT,        SPOTL,        LA_R_NAV,  LA_SYM,   LA_MEDIA,  XXXXXXX,   TD(TD_SEARCH)

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

#define QUINOA_ALTERNATIVES_SYM_WIN \
KC_BSLS,  KC_LBRC,  KC_LPRN,  KC_LCBR,   KC_ESC,   XXXXXXX, XXXXXXX,  KC_CIRC,  KC_RCBR,  KC_RPRN,  KC_RBRC,   KC_DQT, \
KC_EXLM,  KC_QUOT,  KC_COLN,  KC_UNDS,   KC_TILD,  XXXXXXX, XXXXXXX,  KC_HASH,  OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT, \
KC_DLR,   KC_AMPR,  KC_PLUS,  KC_MINS,   KC_PERC,  XXXXXXX, XXXXXXX,  KC_PIPE,  KC_AT,    KC_SCLN,  KC_EQL,    LT(LA_NAV, KC_Y), \
XXXXXXX,  XXXXXXX,  _______,  _______,   _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,   XXXXXXX

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

#define QUINOA_ALTERNATIVES_NAV_WIN \
KC_ESC,            SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, XXXXXXX,  QK_BOOT,  HOME,     KC_UP,     END,       DEL_WORD, \
OS_SHFT,           OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC, \
LT(LA_SYM, KC_Y),  XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT, \
XXXXXXX,           XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX

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

#define QUINOA_ALTERNATIVES_NUM_WIN \
KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX, XXXXXXX,  KC_COMM,   KC_7,     KC_8,      KC_9,     KC_DLR, \
KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,  KC_0,      KC_4,     KC_5,      KC_6,     KC_BSPC, \
KC_TAB,    CW_TOGG,   KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,  KC_DOT,    KC_1,     KC_2,      KC_3,     KC_ENT, \
XXXXXXX,   XXXXXXX,   _______,   _______,   _______,        SPOTL,       _______,   _______,  _______,   XXXXXXX,  XXXXXXX

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

#define QUINOA_ALTERNATIVES_MED_WIN \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  KC_VOLD,  XXXXXXX,  KC_VOLU,  XXXXXXX, \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_MRWD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MFFD, \
XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
XXXXXXX,  XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX

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