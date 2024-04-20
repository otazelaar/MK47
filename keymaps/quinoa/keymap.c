#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"
#include "features/select_word.h"

#define HOME G(KC_UP)
#define END G(KC_DOWN)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define DEL_WORD A(KC_BSPC)
#define DEL_LINE G(KC_BSPC)
#define LA_SYM MO(SYM)
#define LA_NAV LT(NAV, KC_SPC)
#define LA_R_NAV LT(NAV, KC_TAB)
#define OS_LSFT OSM(MOD_LSFT)
#define UNDO G(KC_Z)
#define REDO LSFT(G(KC_Z))

bool is_alt_tab_active = false; 
uint16_t alt_tab_timer = 0;

enum layers {
    DEF,
    SYM,
    NAV,
    NUMPAD,
};

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    REPEAT,
    SELWORD,
};

enum tap_dance_indexes {
    TD_SEARCH,
};

enum combo_events {
    // Left Side
    COMBO_SHIFT,
    COMBO_TAB,
    COMBO_UNDO,
    COMBO_REDO,

    // Right Side    
    COMBO_ENTER,
    LA_COMBO_NAV,        
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
const uint16_t PROGMEM shift_combo[] = {KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM redo_combo[] = {KC_Z, KC_X, KC_C, KC_D, COMBO_END};

// Right Side
const uint16_t PROGMEM enter_combo[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM nav_combo[] = {KC_TAB, LA_SYM, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM delete_line_combo[] = {KC_L, KC_U, KC_Y, KC_QUOT, COMBO_END};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  DEFAULT LAYER
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |   "   | 
 * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   '   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |   <   |   >   |   ?   |
 * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               |       |       |       |       |       | 
 * |       |       |  REP  |  NAV  | SHFT  |      SWAP     |NAV-TAB|  SYM  |       |       |SEARCH |
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

    [DEF] = LAYOUT(
        KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,     XXXXXXX, XXXXXXX,   KC_J,      KC_L,    KC_U,      KC_Y,      KC_QUOT,
        KC_A,      KC_R,      KC_S,      KC_T,      KC_G,     XXXXXXX, XXXXXXX,   KC_M,      KC_N,    KC_E,      KC_I,      KC_O,
        KC_Z,      KC_X,      KC_C,      KC_D,      KC_V,     XXXXXXX, XXXXXXX,   KC_K,      KC_H,    KC_COMM,   KC_DOT,    KC_SLSH,
        XXXXXXX,   XXXXXXX,   QK_REP,    LA_NAV,    OS_LSFT,        SW_WIN,       LA_R_NAV,  LA_SYM,  XXXXXXX,   XXXXXXX,   TD(TD_SEARCH)
    ),

/*  SYMBOLS LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |  ESC  |   [   |   (   |   {   |   ~   |       |       |   ^   |   }   |   )   |   ]   |   `   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       | 
* |   -   |   *   |   =   |   _   |   $   |       |       |   #   |  CMD  |  ALT  |  CTL  |  SHFT |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   +   |   |   |   @   |   \   |   %   |       |       |       |   &   |   ;   |   :   |   !   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       | HOLD  |       |       |       | 
* |       |       |  REP  |  NAV  |  SHFT |      SWAP     |NAV-TAB|  SYM  |       |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

    [SYM] = LAYOUT(
        KC_ESC,    KC_LBRC,   KC_LPRN,   KC_LCBR,   KC_TILD,  XXXXXXX, XXXXXXX,   KC_CIRC,  KC_RCBR,  KC_RPRN,   KC_RBRC,   KC_GRV,
        KC_MINS,   KC_ASTR,   KC_EQL,    KC_UNDS,   KC_DLR,   XXXXXXX, XXXXXXX,   KC_HASH,  OS_CMD,   OS_ALT,    OS_CTRL,   OS_SHFT,
        KC_PLUS,   KC_PIPE,   KC_AT,     KC_BSLS,   KC_PERC,  XXXXXXX, XXXXXXX,   KC_NO,    KC_AMPR,  KC_SCLN,   KC_COLN,   KC_EXLM,
        XXXXXXX,   XXXXXXX,   _______,   _______,   _______,        SW_WIN,       _______,  _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

    /*  NAVIGATION LAYER
    * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * |  SWIN |  TABL |  TABR |  VOLU |       |       |       |  BOOT |  HOME |   UP  |  END  |  DELW |
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * | SHIFT | SELWD |  MPLY |  VOLD |       |       |       | CWTOG | LEFT  |  DOWN | RIGHT | BCSPC |
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * |  SHFT |  CTRL |  ALT  |  CMD  |       |       |       |       |  PGUP |  PGDN |  SPC  |  ENT  |
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| 
    * |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       | 
    * |       |       |  REP  |  NAV  | SHFT  |      SWAP     |NAV-TAB|  SYM  |       |       |       |
    * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
    */ 

    [NAV] = LAYOUT(
            SW_WIN,    TABL,      TABR,      KC_VOLU,  XXXXXXX,  XXXXXXX, XXXXXXX,   QK_BOOTLOADER,   HOME,     KC_UP,     END,       DEL_WORD,
            OS_SHFT,   SELWORD,   KC_MPLY,   KC_VOLD,  XXXXXXX,  XXXXXXX, XXXXXXX,   CW_TOGG,         KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
            OS_SHFT,   OS_CTRL,   OS_ALT,    OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,         KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT,
            XXXXXXX,   XXXXXXX,   _______,   _______,  _______,        SW_WIN,       _______,         _______,  XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

    /*  NUMPAD LAYER
    * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * |       |  ;    |  (    |  )    |  \    |       |       |   ,   |   7   |   8   |   9   |   $   |
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * |  SHFT |  CTRL |  ALT  |  CMD  |       |       |       |   0   |   4   |   5   |   6   | bcspc |   
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    * |       |       |       |       |       |       |       |       |       |       |       |       | 
    * |  TAB  |       | SHIFT |  SPC  |       |       |       |   .   |   1   |   2   |   3   |  ENT  |
    * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
    * |       |       |       | HOLD  |       |       |       |       | HOLD  |       |       |       |
    * |       |       |  REP  |  NAV  | SHFT  |      SWAP     |NAV-TAB|  SYM  |       |       |       |
    * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
    */

    [NUMPAD] = LAYOUT(
            XXXXXXX,   KC_SCLN,    KC_LPRN,   KC_RPRN,   KC_BSLS,  XXXXXXX, XXXXXXX,   KC_COMM,   KC_7,     KC_8,      KC_9,     KC_DLR,
            OS_SHFT,   OS_CTRL,    OS_ALT,    OS_CMD,    XXXXXXX,  XXXXXXX, XXXXXXX,   KC_0,      KC_4,     KC_5,      KC_6,     KC_BSPC,
            KC_TAB,    XXXXXXX,    KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,   KC_DOT,    KC_1,     KC_2,      KC_3,     KC_ENT,  
            XXXXXXX,   XXXXXXX,    _______,   _______,   _______,        SW_WIN,       _______,   _______,  XXXXXXX,   XXXXXXX,  XXXXXXX
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
        
        if (!process_select_word(keycode, record, SELWORD)) {
            return false;
        }
        
        // Alt-Tab
        if (keycode == ALT_TAB) {
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
            return false; // Skip all further processing of this key
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

    void process_combo_event(uint16_t combo_index, bool pressed) {
    
        switch(combo_index) {
            case LA_COMBO_NAV:
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
            return update_tri_layer_state(state, SYM, NAV, NUMPAD);
    }

    combo_t key_combos[COMBO_COUNT] = {
        // Left Side
        [COMBO_SHIFT] = COMBO(shift_combo, OS_SHFT),
        [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
        [COMBO_UNDO] = COMBO(undo_combo, UNDO),
        [COMBO_REDO] = COMBO(redo_combo, REDO),
        
        // Right Side
        [COMBO_ENTER] = COMBO(enter_combo, KC_ENT),        
        [LA_COMBO_NAV] = COMBO(nav_combo, LA_NAV),
        [COMBO_BSPC] = COMBO(bspc_combo, KC_BSPC),
        [COMBO_DELETE] = COMBO(delete_combo, DEL_WORD),
        [COMBO_DELETE_LINE] = COMBO(delete_line_combo, DEL_LINE),

    };