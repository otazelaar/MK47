/* Copyright (C) 2023 jonylee@hfd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layers {
    _LAYER_BASE = 0,
    _LAYER_MEDIA_RGB,
    _LAYER_NUMBER_SYMBOL,
    _LAYER_SHORTCUT_NAV,
    _LAYER_MOUSE,
};

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
};

enum tap_dance_indexes {
  // TD_FIND,
  TD_SEARCH,
  // TD_FLSH, // flash keyboard (as if the physical flash key was pressed)
};

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
    // [TD_FIND] = ACTION_TAP_DANCE_DOUBLE(KC_F, LCTL(KC_F)),
    [TD_SEARCH] = ACTION_TAP_DANCE_FN(tap_dance_search),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

// Timer for alt-tab
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 300) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _LAYER_BASE
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |   :   | 
 * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   ;   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | LCtl  | LAlt  | LGui  | LSft  |       |       |       |       | LSft  | LGui  | LAlt  | LCtl  | 
 * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |   <   |   >   |   ?   | 
 * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       | MOUSE |NUM/SYM|       |     Super     | MEDIA | NAV/SC| MOUSE |       |Search | 
 * |       |       |  TG   |  -->  | shift |    Alt tab    |  ent  |  <--  |  tab  |       |  TD   |
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------,
 */

 [_LAYER_BASE] = LAYOUT(
    KC_Q,             KC_W,             KC_F,      KC_P,             KC_B,         KC_NO,       KC_NO,     KC_J,              KC_L,              KC_U,              KC_Y,             KC_SCLN, \
    LCTL_T(KC_A),     LALT_T(KC_R),     LGUI_T(KC_S),     LSFT_T(KC_T),     KC_G,         KC_NO,       KC_NO,     KC_M,              LSFT_T(KC_N),      LGUI_T(KC_E),      LALT_T(KC_I),     LCTL_T(KC_O), \
    KC_Z,             KC_X,             KC_C,             KC_D,             KC_V,         KC_NO,       KC_NO,     KC_K,              KC_H,              KC_COMM,           KC_DOT,           KC_SLSH, \
    KC_NO,            KC_NO,            TG(4),           LT(2,KC_SPC),     KC_LSFT,             ALT_TAB,         LT(1,KC_ENT),      LT(3,KC_BSPC),     LT(4, KC_TAB),     KC_NO,            TD(TD_SEARCH)),

/* _LAYER_MEDIA_RGB
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * | Hue-  | Hue+  | Efct- | Efct+ |       |       |       |       | Vol-  |       | Vol-  |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * | RGBM- | RGBM+ | Lum-  | Lum+  |       |       |       | Slow  |  <--  | Play  |  -->  | Fast  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * | Sat-  | Sat+  |       | RGB~  |       |       |       |       | Prev  |       | Next  | Mute  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               | ENTRY |       |       |       |       | 
 * | Sleep | Reset |       |       |       |               | POINT |       |       |       |       |
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------,
 */

[_LAYER_MEDIA_RGB] = LAYOUT(
    RGB_HUD,     RGB_HUI,     RGB_SPD,     RGB_SPI,     KC_NO,     KC_NO,     KC_NO,     KC_NO,           KC_VOLD,     KC_NO,      KC_VOLU,     KC_NO, \
    RGB_RMOD,    RGB_MOD,     RGB_VAD,     RGB_VAI,     KC_NO,     KC_NO,     KC_NO,     LSFT(KC_LT),     KC_LEFT,     KC_MPLY,    KC_RGHT,     LSFT(KC_GT), \
    RGB_SAD,     RGB_SAI,     KC_NO,       RGB_TOG,     KC_NO,     KC_NO,     KC_NO,     KC_NO,           KC_MPRV,     KC_NO,      KC_MNXT,     KC_MUTE, \
    KC_SLEP,     QK_BOOT,     KC_NO,       KC_NO,       KC_NO,           KC_NO,          KC_NO,           KC_NO,       KC_NO,      KC_NO,       KC_NO),

/* _LAYER_NUMBER_SYMBOL
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |   !   |   @   |   #   |   $   |   %   |       |       |   ^   |   &   |   [   |   ]   |   *   | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |   1   |   2   |   3   |   4   |   5   |       |       |   -   |   =   |   (   |   )   |   "   | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |   6   |   7   |   8   |   9   |   0   |       |       |   |   |   +   |   {   |   }   |   \   | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       | ENTRY |       |               |       |       |  Caps |       |       | 
 * |       |       |       | POINT |   '   |               |   _   |   ~   |  Word |       |       | 
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------,
 */

[_LAYER_NUMBER_SYMBOL] = LAYOUT(
    KC_EXLM,     KC_AT,       KC_HASH,     KC_DLR,      KC_PERC,      KC_NO,       KC_NO,       KC_CIRC,        KC_AMPR,          KC_LBRC,     KC_RBRC,     KC_ASTR, \
    KC_P1,       KC_P2,       KC_P3,       KC_P4,       KC_P5,        KC_NO,       KC_NO,       KC_MINS,        KC_EQL,           KC_LPRN,     KC_RPRN,     LSFT(KC_QUOT), \
    KC_P6,       KC_P7,       KC_P8,       KC_P9,       KC_P0,        KC_NO,       KC_NO,       KC_PIPE,        LSFT(KC_EQL),     KC_LCBR,     KC_RCBR,     KC_BSLS, \
    KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_QUOTE,            KC_NO,             KC_UNDS,        LSFT(KC_GRV),     CW_TOGG,     KC_NO,       KC_NO),

/* _LAYER_SHORTCUT_NAV
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       | PRINT |       |       |       |       | PREV  |  UP   | NEXT  |DELETE | 
 * |  Esc  |  CUT  | FIND  | SCREEN|       |       |       | HOME  | TAB   | ARROW | TAB   | LINE  | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | BACK  |       |       |  NEW  | CLOSE |       |       | PAGE  | Left  | DOWN  | RIGHT | BACK  | 
 * | SPACE | COPY  | PASTE |  TAB  |  TAB  |       |       |  UP   | ARROW | ARROW | ARROW | SPACE | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | ZOOM  | ZOOM  |       |       |       |       | PAGE  | PREV  |BROWSER| NEXT  |DELETE |
 * | UNDO  |  OUT  |  IN   |  TAB  |       |       |       | DOWN  | PAGE  |SEARCH | PAGE  | WORD  | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       | LEFT  |     TRANS     |       | ENTRY |       |       |       | 
 * |       |       |       |       | SHIFT |    ALT TAB    |       | POINT |       |       |       | 
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------,
 */
[_LAYER_SHORTCUT_NAV] = LAYOUT(
    KC_ESC,         LCTL(KC_X),        TD(TD_FIND),       KC_PSCR,        KC_NO,          KC_NO,          KC_NO,     KC_HOME,        LCTL(KC_PGDN),     KC_UP,          LCTL(KC_PGUP),     KC_DEL, \
    KC_BSPC,        LCTL(KC_C),        LCTL(KC_V),        LCTL(KC_T),     LCTL(KC_W),     KC_NO,          KC_NO,     KC_PGUP,        KC_LEFT,           KC_DOWN,        KC_RGHT,           KC_BSPC, \
    LCTL(KC_Z),     LCTL(KC_PMNS),     LCTL(KC_PPLS),     KC_TAB,         KC_NO,          KC_NO,          KC_NO,     KC_PGDN,        KC_WBAK,           KC_WSCH,        KC_WFWD,           LCTL(KC_BSPC), \
    KC_NO,          KC_NO,             KC_NO,             KC_NO,          KC_LSFT,               KC_TRNS,            KC_NO,          KC_NO,             KC_NO,          KC_NO,             KC_NO),

// Make this layer TOGGLEABLE so you can stay in it without holding a key
/* _LAYER_MOUSE
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |       |       |   up  |       |       |       |       |       |       |       |       |       | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       | 
 * |       | left  | down  | right |       |       |       |       | acl0  | acl2  | acl1|       | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | wheel | wheel | wheel | wheel |       |       |       |       |       |       |       |       |
 * | left  | right | down  |  up   |       |       |       |       |  tab  |repeat |       |       | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       | ENTRY |       |       |               | left  |       |       |       |       | 
 * |       |       | POINT |       |       |    ALT_TAB    | click |       |       |       |       | 
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------,
 */

[_LAYER_MOUSE] = LAYOUT(
    KC_NO,        KC_NO,        KC_MS_U,        KC_NO,           KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_NO,     
    KC_NO,        KC_MS_L,      KC_MS_D,        KC_MS_R,         KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_ACL0,   KC_ACL2,   KC_ACL1,       KC_NO,     
    KC_WH_L,      KC_WH_R,      KC_WH_D,        KC_WH_U,         KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_TAB,    QK_REP,    KC_NO,       KC_NO,     
    KC_NO,        KC_TRNS,      KC_TRNS,        KC_NO,           KC_NO,     KC_TRNS,     KC_BTN1,    KC_BTN2,     KC_NO,     KC_NO,     KC_NO)
};

// Keycodes Overview
// When defining a keymap each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK.

// This is a reference only. Each group of keys links to the page documenting their functionality in more detail.

// Basic Keycodes :id=basic-keycodes
// See also: Basic Keycodes

// Key	Aliases	Description	Windows	macOS	Linux1
// KC_NO	XXXXXXX	Ignore this key (NOOP)	N/A	N/A	N/A
// KC_TRANSPARENT	KC_TRNS, _______	Use the next lowest non-transparent key	N/A	N/A	N/A
// KC_A		a and A	✔	✔	✔
// KC_B		b and B	✔	✔	✔
// KC_C		c and C	✔	✔	✔
// KC_D		d and D	✔	✔	✔
// KC_E		e and E	✔	✔	✔
// KC_F		f and F	✔	✔	✔
// KC_G		g and G	✔	✔	✔
// KC_H		h and H	✔	✔	✔
// KC_I		i and I	✔	✔	✔
// KC_J		j and J	✔	✔	✔
// KC_K		k and K	✔	✔	✔
// KC_L		l and L	✔	✔	✔
// KC_M		m and M	✔	✔	✔
// KC_N		n and N	✔	✔	✔
// KC_O		o and O	✔	✔	✔
// KC_P		p and P	✔	✔	✔
// KC_Q		q and Q	✔	✔	✔
// KC_R		r and R	✔	✔	✔
// KC_S		s and S	✔	✔	✔
// KC_T		t and T	✔	✔	✔
// KC_U		u and U	✔	✔	✔
// KC_V		v and V	✔	✔	✔
// KC_W		w and W	✔	✔	✔
// KC_X		x and X	✔	✔	✔
// KC_Y		y and Y	✔	✔	✔
// KC_Z		z and Z	✔	✔	✔
// KC_1		1 and !	✔	✔	✔
// KC_2		2 and @	✔	✔	✔
// KC_3		3 and #	✔	✔	✔
// KC_4		4 and $	✔	✔	✔
// KC_5		5 and %	✔	✔	✔
// KC_6		6 and ^	✔	✔	✔
// KC_7		7 and &	✔	✔	✔
// KC_8		8 and *	✔	✔	✔
// KC_9		9 and (	✔	✔	✔
// KC_0		0 and )	✔	✔	✔
// KC_ENTER	KC_ENT	Return (Enter)	✔	✔	✔
// KC_ESCAPE	KC_ESC	Escape	✔	✔	✔
// KC_BACKSPACE	KC_BSPC	Delete (Backspace)	✔	✔	✔
// KC_TAB		Tab	✔	✔	✔
// KC_SPACE	KC_SPC	Spacebar	✔	✔	✔
// KC_MINUS	KC_MINS	- and _	✔	✔	✔
// KC_EQUAL	KC_EQL	= and +	✔	✔	✔
// KC_LEFT_BRACKET	KC_LBRC	[ and {	✔	✔	✔
// KC_RIGHT_BRACKET	KC_RBRC	] and }	✔	✔	✔
// KC_BACKSLASH	KC_BSLS	\ and |	✔	✔	✔
// KC_NONUS_HASH	KC_NUHS	Non-US # and ~	✔	✔	✔
// KC_SEMICOLON	KC_SCLN	; and :	✔	✔	✔
// KC_QUOTE	KC_QUOT	' and "	✔	✔	✔
// KC_GRAVE	KC_GRV	` and ~	✔	✔	✔
// KC_COMMA	KC_COMM	, and <	✔	✔	✔
// KC_DOT		. and >	✔	✔	✔
// KC_SLASH	KC_SLSH	/ and ?	✔	✔	✔
// KC_CAPS_LOCK	KC_CAPS	Caps Lock	✔	✔	✔
// KC_F1		F1	✔	✔	✔
// KC_F2		F2	✔	✔	✔
// KC_F3		F3	✔	✔	✔
// KC_F4		F4	✔	✔	✔
// KC_F5		F5	✔	✔	✔
// KC_F6		F6	✔	✔	✔
// KC_F7		F7	✔	✔	✔
// KC_F8		F8	✔	✔	✔
// KC_F9		F9	✔	✔	✔
// KC_F10		F10	✔	✔	✔
// KC_F11		F11	✔	✔	✔
// KC_F12		F12	✔	✔	✔
// KC_PRINT_SCREEN	KC_PSCR	Print Screen	✔	✔2	✔
// KC_SCROLL_LOCK	KC_SCRL, KC_BRMD	Scroll Lock, Brightness Down (macOS)	✔	✔2	✔
// KC_PAUSE	KC_PAUS, KC_BRK, KC_BRMU	Pause, Brightness Up (macOS)	✔	✔2	✔
// KC_INSERT	KC_INS	Insert	✔		✔
// KC_HOME		Home	✔	✔	✔
// KC_PAGE_UP	KC_PGUP	Page Up	✔	✔	✔
// KC_DELETE	KC_DEL	Forward Delete	✔	✔	✔
// KC_END		End	✔	✔	✔
// KC_PAGE_DOWN	KC_PGDN	Page Down	✔	✔	✔
// KC_RIGHT	KC_RGHT	Right Arrow	✔	✔	✔
// KC_LEFT		Left Arrow	✔	✔	✔
// KC_DOWN		Down Arrow	✔	✔	✔
// KC_UP		Up Arrow	✔	✔	✔
// KC_NUM_LOCK	KC_NUM	Keypad Num Lock and Clear	✔	✔	✔
// KC_KP_SLASH	KC_PSLS	Keypad /	✔	✔	✔
// KC_KP_ASTERISK	KC_PAST	Keypad *	✔	✔	✔
// KC_KP_MINUS	KC_PMNS	Keypad -	✔	✔	✔
// KC_KP_PLUS	KC_PPLS	Keypad +	✔	✔	✔
// KC_KP_ENTER	KC_PENT	Keypad Enter	✔	✔	✔
// KC_KP_1	KC_P1	Keypad 1 and End	✔	✔	✔
// KC_KP_2	KC_P2	Keypad 2 and Down Arrow	✔	✔	✔
// KC_KP_3	KC_P3	Keypad 3 and Page Down	✔	✔	✔
// KC_KP_4	KC_P4	Keypad 4 and Left Arrow	✔	✔	✔
// KC_KP_5	KC_P5	Keypad 5	✔	✔	✔
// KC_KP_6	KC_P6	Keypad 6 and Right Arrow	✔	✔	✔
// KC_KP_7	KC_P7	Keypad 7 and Home	✔	✔	✔
// KC_KP_8	KC_P8	Keypad 8 and Up Arrow	✔	✔	✔
// KC_KP_9	KC_P9	Keypad 9 and Page Up	✔	✔	✔
// KC_KP_0	KC_P0	Keypad 0 and Insert	✔	✔	✔
// KC_KP_DOT	KC_PDOT	Keypad . and Delete	✔	✔	✔
// KC_NONUS_BACKSLASH	KC_NUBS	Non-US \ and |	✔	✔	✔
// KC_APPLICATION	KC_APP	Application (Windows Context Menu Key)	✔		✔
// KC_KB_POWER		System Power		✔3	✔
// KC_KP_EQUAL	KC_PEQL	Keypad =	✔	✔	✔
// KC_F13		F13	✔	✔	✔
// KC_F14		F14	✔	✔	✔
// KC_F15		F15	✔	✔	✔
// KC_F16		F16	✔	✔	✔
// KC_F17		F17	✔	✔	✔
// KC_F18		F18	✔	✔	✔
// KC_F19		F19	✔	✔	✔
// KC_F20		F20	✔		✔
// KC_F21		F21	✔		✔
// KC_F22		F22	✔		✔
// KC_F23		F23	✔		✔
// KC_F24		F24	✔		✔
// KC_EXECUTE	KC_EXEC	Execute			✔
// KC_HELP		Help			✔
// KC_MENU		Menu			✔
// KC_SELECT	KC_SLCT	Select			✔
// KC_STOP		Stop			✔
// KC_AGAIN	KC_AGIN	Again			✔
// KC_UNDO		Undo			✔
// KC_CUT		Cut			✔
// KC_COPY		Copy			✔
// KC_PASTE	KC_PSTE	Paste			✔
// KC_FIND		Find			✔
// KC_KB_MUTE		Mute		✔	✔
// KC_KB_VOLUME_UP		Volume Up		✔	✔
// KC_KB_VOLUME_DOWN		Volume Down		✔	✔
// KC_LOCKING_CAPS_LOCK	KC_LCAP	Locking Caps Lock	✔	✔	
// KC_LOCKING_NUM_LOCK	KC_LNUM	Locking Num Lock	✔	✔	
// KC_LOCKING_SCROLL_LOCK	KC_LSCR	Locking Scroll Lock	✔	✔	
// KC_KP_COMMA	KC_PCMM	Keypad ,			✔
// KC_KP_EQUAL_AS400		Keypad = on AS/400 keyboards			
// KC_INTERNATIONAL_1	KC_INT1	International 1	✔		✔
// KC_INTERNATIONAL_2	KC_INT2	International 2	✔		✔
// KC_INTERNATIONAL_3	KC_INT3	International 3	✔		✔
// KC_INTERNATIONAL_4	KC_INT4	International 4	✔		✔
// KC_INTERNATIONAL_5	KC_INT5	International 5	✔		✔
// KC_INTERNATIONAL_6	KC_INT6	International 6			✔
// KC_INTERNATIONAL_7	KC_INT7	International 7			
// KC_INTERNATIONAL_8	KC_INT8	International 8			
// KC_INTERNATIONAL_9	KC_INT9	International 9			
// KC_LANGUAGE_1	KC_LNG1	Language 1			✔
// KC_LANGUAGE_2	KC_LNG2	Language 2			✔
// KC_LANGUAGE_3	KC_LNG3	Language 3			✔
// KC_LANGUAGE_4	KC_LNG4	Language 4			✔
// KC_LANGUAGE_5	KC_LNG5	Language 5			✔
// KC_LANGUAGE_6	KC_LNG6	Language 6			
// KC_LANGUAGE_7	KC_LNG7	Language 7			
// KC_LANGUAGE_8	KC_LNG8	Language 8			
// KC_LANGUAGE_9	KC_LNG9	Language 9			
// KC_ALTERNATE_ERASE	KC_ERAS	Alternate Erase			
// KC_SYSTEM_REQUEST	KC_SYRQ	SysReq/Attention			
// KC_CANCEL	KC_CNCL	Cancel			
// KC_CLEAR	KC_CLR	Clear			✔
// KC_PRIOR	KC_PRIR	Prior			
// KC_RETURN	KC_RETN	Return			
// KC_SEPARATOR	KC_SEPR	Separator			
// KC_OUT		Out			
// KC_OPER		Oper			
// KC_CLEAR_AGAIN	KC_CLAG	Clear/Again			
// KC_CRSEL	KC_CRSL	CrSel/Props			
// KC_EXSEL	KC_EXSL	ExSel			
// KC_LEFT_CTRL	KC_LCTL	Left Control	✔	✔	✔
// KC_LEFT_SHIFT	KC_LSFT	Left Shift	✔	✔	✔
// KC_LEFT_ALT	KC_LALT, KC_LOPT	Left Alt (Option)	✔	✔	✔
// KC_LEFT_GUI	KC_LGUI, KC_LCMD, KC_LWIN	Left GUI (Windows/Command/Meta key)	✔	✔	✔
// KC_RIGHT_CTRL	KC_RCTL	Right Control	✔	✔	✔
// KC_RIGHT_SHIFT	KC_RSFT	Right Shift	✔	✔	✔
// KC_RIGHT_ALT	KC_RALT, KC_ROPT, KC_ALGR	Right Alt (Option/AltGr)	✔	✔	✔
// KC_RIGHT_GUI	KC_RGUI, KC_RCMD, KC_RWIN	Right GUI (Windows/Command/Meta key)	✔	✔	✔
// KC_SYSTEM_POWER	KC_PWR	System Power Down	✔	✔3	✔
// KC_SYSTEM_SLEEP	KC_SLEP	System Sleep	✔	✔3	✔
// KC_SYSTEM_WAKE	KC_WAKE	System Wake		✔3	✔
// KC_AUDIO_MUTE	KC_MUTE	Mute	✔	✔	✔
// KC_AUDIO_VOL_UP	KC_VOLU	Volume Up	✔	✔4	✔
// KC_AUDIO_VOL_DOWN	KC_VOLD	Volume Down	✔	✔4	✔
// KC_MEDIA_NEXT_TRACK	KC_MNXT	Next Track	✔	✔5	✔
// KC_MEDIA_PREV_TRACK	KC_MPRV	Previous Track	✔	✔5	✔
// KC_MEDIA_STOP	KC_MSTP	Stop Track	✔		✔
// KC_MEDIA_PLAY_PAUSE	KC_MPLY	Play/Pause Track	✔	✔	✔
// KC_MEDIA_SELECT	KC_MSEL	Launch Media Player	✔		✔
// KC_MEDIA_EJECT	KC_EJCT	Eject		✔	✔
// KC_MAIL		Launch Mail	✔		✔
// KC_CALCULATOR	KC_CALC	Launch Calculator	✔		✔
// KC_MY_COMPUTER	KC_MYCM	Launch My Computer	✔		✔
// KC_WWW_SEARCH	KC_WSCH	Browser Search	✔		✔
// KC_WWW_HOME	KC_WHOM	Browser Home	✔		✔
// KC_WWW_BACK	KC_WBAK	Browser Back	✔		✔
// KC_WWW_FORWARD	KC_WFWD	Browser Forward	✔		✔
// KC_WWW_STOP	KC_WSTP	Browser Stop	✔		✔
// KC_WWW_REFRESH	KC_WREF	Browser Refresh	✔		✔
// KC_WWW_FAVORITES	KC_WFAV	Browser Favorites	✔		✔
// KC_MEDIA_FAST_FORWARD	KC_MFFD	Next Track	✔	✔5	✔
// KC_MEDIA_REWIND	KC_MRWD	Previous Track	✔6	✔5	✔
// KC_BRIGHTNESS_UP	KC_BRIU	Brightness Up	✔	✔	✔
// KC_BRIGHTNESS_DOWN	KC_BRID	Brightness Down	✔	✔	✔
// KC_CONTROL_PANEL	KC_CPNL	Open Control Panel	✔		
// KC_ASSISTANT	KC_ASST	Launch Context-Aware Assistant	✔		
// KC_MISSION_CONTROL	KC_MCTL	Open Mission Control		✔	
// KC_LAUNCHPAD	KC_LPAD	Open Launchpad		✔	
// 1. The Linux kernel HID driver recognizes nearly all keycodes, but the default bindings depend on the DE/WM.
// 2. Treated as F13-F15.
// 3. Must be held for about three seconds, and will display a prompt instead.
// 4. Holding Shift+Option allows for finer control of volume level.
// 5. Skips the entire track in iTunes when tapped, seeks within the current track when held.
// 6. WMP does not recognize the Rewind key, but both alter playback speed in VLC.

// Quantum Keycodes :id=quantum-keycodes
// See also: Quantum Keycodes

// Key	Aliases	Description
// QK_BOOTLOADER	QK_BOOT	Put the keyboard into bootloader mode for flashing
// QK_DEBUG_TOGGLE	DB_TOGG	Toggle debug mode
// QK_CLEAR_EEPROM	EE_CLR	Reinitializes the keyboard's EEPROM (persistent memory)
// QK_MAKE		Sends qmk compile -kb (keyboard) -km (keymap), or qmk flash if shift is held. Puts keyboard into bootloader mode if shift & control are held
// QK_REBOOT	QK_RBT	Resets the keyboard. Does not load the bootloader
// Audio Keys :id=audio-keys
// See also: Audio

// Key	Aliases	Description
// QK_AUDIO_ON	AU_ON	Turns on Audio Feature
// QK_AUDIO_OFF	AU_OFF	Turns off Audio Feature
// QK_AUDIO_TOGGLE	AU_TOGG	Toggles Audio state
// QK_AUDIO_CLICKY_TOGGLE	CK_TOGG	Toggles Audio clicky mode
// QK_AUDIO_CLICKY_ON	CK_ON	Turns on Audio clicky mode
// QK_AUDIO_CLICKY_OFF	CK_OFF	Turns on Audio clicky mode
// QK_AUDIO_CLICKY_UP	CK_UP	Increases frequency of the clicks
// QK_AUDIO_CLICKY_DOWN	CK_DOWN	Decreases frequency of the clicks
// QK_AUDIO_CLICKY_RESET	CK_RST	Resets frequency to default
// QK_MUSIC_ON	MU_ON	Turns on Music Mode
// QK_MUSIC_OFF	MU_OFF	Turns off Music Mode
// QK_MUSIC_TOGGLE	MU_TOGG	Toggles Music Mode
// QK_MUSIC_MODE_NEXT	MU_NEXT	Cycles through the music modes
// QK_AUDIO_VOICE_NEXT	AU_NEXT	Cycles through the audio voices
// QK_AUDIO_VOICE_PREVIOUS	AU_PREV	Cycles through the audio voices in reverse
// Auto Shift :id=auto-shift
// See also: Auto Shift

// Key	Aliases	Description
// QK_AUTO_SHIFT_DOWN	AS_DOWN	Lower the Auto Shift timeout variable (down)
// QK_AUTO_SHIFT_UP	AS_UP	Raise the Auto Shift timeout variable (up)
// QK_AUTO_SHIFT_REPORT	AS_RPT	Report your current Auto Shift timeout value
// QK_AUTO_SHIFT_ON	AS_ON	Turns on the Auto Shift Function
// QK_AUTO_SHIFT_OFF	AS_OFF	Turns off the Auto Shift Function
// QK_AUTO_SHIFT_TOGGLE	AS_TOGG	Toggles the state of the Auto Shift feature
// Autocorrect :id=autocorrect
// See also: Autocorrect

// Key	Aliases	Description
// QK_AUTOCORRECT_ON	AC_ON	Turns on the Autocorrect feature.
// QK_AUTOCORRECT_OFF	AC_OFF	Turns off the Autocorrect feature.
// QK_AUTOCORRECT_TOGGLE	AC_TOGG	Toggles the status of the Autocorrect feature.
// Backlighting :id=backlighting
// See also: Backlighting

// Key	Aliases	Description
// QK_BACKLIGHT_TOGGLE	BL_TOGG	Turn the backlight on or off
// QK_BACKLIGHT_STEP	BL_STEP	Cycle through backlight levels
// QK_BACKLIGHT_ON	BL_ON	Set the backlight to max brightness
// QK_BACKLIGHT_OFF	BL_OFF	Turn the backlight off
// QK_BACKLIGHT_UP	BL_UP	Increase the backlight level
// QK_BACKLIGHT_DOWN	BL_DOWN	Decrease the backlight level
// QK_BACKLIGHT_TOGGLE_BREATHING	BL_BRTG	Toggle backlight breathing
// Bluetooth :id=bluetooth
// See also: Bluetooth

// Key	Aliases	Description
// Replace the problematic code block with valid C/C++ code
// Keycodes Overview
// When defining a keymap each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK.
// KC_A		a and A	✔	✔	✔
// KC_B		b and B	✔	✔	✔
// KC_C		c and C	✔	✔	✔
// KC_D		d and D	✔	✔	✔
// KC_E		e and E	✔	✔	✔
// KC_F		f and F	✔	✔	✔
// KC_G		g and G	✔	✔	✔
// KC_H		h and H	✔	✔	✔
// KC_I		i and I	✔	✔	✔
// KC_J		j and J	✔	✔	✔
// KC_K		k and K	✔	✔	✔
// KC_L		l and L	✔	✔	✔
// KC_M		m and M	✔	✔	✔
// KC_N		n and N	✔	✔	✔
// KC_O		o and O	✔	✔	✔
// KC_P		p and P	✔	✔	✔
// KC_Q		q and Q	✔	✔	✔
// KC_R		r and R	✔	✔	✔
// KC_S		s and S	✔	✔	✔
// KC_T		t and T	✔	✔	✔
// KC_U		u and U	✔	✔	✔
// KC_V		v and V	✔	✔	✔
// KC_W		w and W	✔	✔	✔
// KC_X		x and X	✔	✔	✔
// KC_Y		y and Y	✔	✔	✔
// KC_Z		z and Z	✔	✔	✔
// QK_MIDI_TRANSPOSE_2	MI_TR2	Set transposition to +2 semitones
// QK_MIDI_TRANSPOSE_3	MI_TR3	Set transposition to +3 semitones
// QK_MIDI_TRANSPOSE_4	MI_TR4	Set transposition to +4 semitones
// QK_MIDI_TRANSPOSE_5	MI_TR5	Set transposition to +5 semitones
// QK_MIDI_TRANSPOSE_6	MI_TR6	Set transposition to +6 semitones
// QK_MIDI_TRANSPOSE_DOWN	MI_TRSD	Decrease transposition
// QK_MIDI_TRANSPOSE_UP	MI_TRSU	Increase transposition
// QK_MIDI_VELOCITY_0	MI_VL0	Set velocity to 0
// QK_MIDI_VELOCITY_1	MI_VL1	Set velocity to 12
// QK_MIDI_VELOCITY_2	MI_VL2	Set velocity to 25
// QK_MIDI_VELOCITY_3	MI_VL3	Set velocity to 38
// QK_MIDI_VELOCITY_4	MI_VL4	Set velocity to 51
// QK_MIDI_VELOCITY_5	MI_VL5	Set velocity to 64
// QK_MIDI_VELOCITY_6	MI_VL6	Set velocity to 76
// QK_MIDI_VELOCITY_7	MI_VL7	Set velocity to 89
// QK_MIDI_VELOCITY_8	MI_VL8	Set velocity to 102
// QK_MIDI_VELOCITY_9	MI_VL9	Set velocity to 114
// QK_MIDI_VELOCITY_10	MI_VL10	Set velocity to 127
// QK_MIDI_VELOCITY_DOWN	MI_VELD	Decrease velocity
// QK_MIDI_VELOCITY_UP	MI_VELU	Increase velocity
// QK_MIDI_CHANNEL_1	MI_CH1	Set channel to 1
// QK_MIDI_CHANNEL_2	MI_CH2	Set channel to 2
// QK_MIDI_CHANNEL_3	MI_CH3	Set channel to 3
// QK_MIDI_CHANNEL_4	MI_CH4	Set channel to 4
// QK_MIDI_CHANNEL_5	MI_CH5	Set channel to 5
// QK_MIDI_CHANNEL_6	MI_CH6	Set channel to 6
// QK_MIDI_CHANNEL_7	MI_CH7	Set channel to 7
// QK_MIDI_CHANNEL_8	MI_CH8	Set channel to 8
// QK_MIDI_CHANNEL_9	MI_CH9	Set channel to 9
// QK_MIDI_CHANNEL_10	MI_CH10	Set channel to 10
// QK_MIDI_CHANNEL_11	MI_CH11	Set channel to 11
// QK_MIDI_CHANNEL_12	MI_CH12	Set channel to 12
// QK_MIDI_CHANNEL_13	MI_CH13	Set channel to 13
// QK_MIDI_CHANNEL_14	MI_CH14	Set channel to 14
// QK_MIDI_CHANNEL_15	MI_CH15	Set channel to 15
// QK_MIDI_CHANNEL_16	MI_CH16	Set channel to 16
// QK_MIDI_CHANNEL_DOWN	MI_CHND	Decrease channel
// QK_MIDI_CHANNEL_UP	MI_CHNU	Increase channel
// QK_MIDI_ALL_NOTES_OFF	MI_AOFF	Stop all notes
// QK_MIDI_SUSTAIN	MI_SUST	Sustain
// QK_MIDI_PORTAMENTO	MI_PORT	Portmento
// QK_MIDI_SOSTENUTO	MI_SOST	Sostenuto
// QK_MIDI_SOFT	MI_SOFT	Soft Pedal
// QK_MIDI_LEGATO	MI_LEG	Legato
// QK_MIDI_MODULATION	MI_MOD	Modulation
// QK_MIDI_MODULATION_SPEED_DOWN	MI_MODD	Decrease modulation speed
// QK_MIDI_MODULATION_SPEED_UP	MI_MODU	Increase modulation speed
// QK_MIDI_PITCH_BEND_DOWN	MI_BNDD	Bend pitch down
// QK_MIDI_PITCH_BEND_UP	MI_BNDU	Bend pitch up
// Mouse Keys :id=mouse-keys
// See also: Mouse Keys

// Key	Aliases	Description
// KC_MS_UP	KC_MS_U	Mouse Cursor Up
// KC_MS_DOWN	KC_MS_D	Mouse Cursor Down
// KC_MS_LEFT	KC_MS_L	Mouse Cursor Left
// KC_MS_RIGHT	KC_MS_R	Mouse Cursor Right
// KC_MS_BTN1	KC_BTN1	Mouse Button 1
// KC_MS_BTN2	KC_BTN2	Mouse Button 2
// KC_MS_BTN3	KC_BTN3	Mouse Button 3
// KC_MS_BTN4	KC_BTN4	Mouse Button 4
// KC_MS_BTN5	KC_BTN5	Mouse Button 5
// KC_MS_WH_UP	KC_WH_U	Mouse Wheel Up
// KC_MS_WH_DOWN	KC_WH_D	Mouse Wheel Down
// KC_MS_WH_LEFT	KC_WH_L	Mouse Wheel Left
// KC_MS_WH_RIGHT	KC_WH_R	Mouse Wheel Right
// KC_MS_ACCEL0	KC_ACL0	Set mouse acceleration to 0
// KC_MS_ACCEL1	KC_ACL1	Set mouse acceleration to 1
// KC_MS_ACCEL2	KC_ACL2	Set mouse acceleration to 2
// Modifiers :id=modifiers
// See also: Modifier Keys

// Key	Aliases	Description
// LCTL(kc)	C(kc)	Hold Left Control and press kc
// LSFT(kc)	S(kc)	Hold Left Shift and press kc
// LALT(kc)	A(kc), LOPT(kc)	Hold Left Alt and press kc
// LGUI(kc)	G(kc), LCMD(kc), LWIN(kc)	Hold Left GUI and press kc
// RCTL(kc)		Hold Right Control and press kc
// RSFT(kc)		Hold Right Shift and press kc
// RALT(kc)	ROPT(kc), ALGR(kc)	Hold Right Alt (AltGr) and press kc
// RGUI(kc)	RCMD(kc), RWIN(kc)	Hold Right GUI and press kc
// LSG(kc)	SGUI(kc), SCMD(kc), SWIN(kc)	Hold Left Shift and Left GUI and press kc
/*
// FILEPATH: /Users/owentazelaar/qmk_firmware/keyboards/inland/mk47/keymaps/oats/keymap.c

// LAG(kc)		Hold Left Alt and Left GUI and press kc
// RSG(kc)		Hold Right Shift and Right GUI and press kc
// RAG(kc)		Hold Right Alt and Right GUI and press kc
// LCA(kc)		Hold Left Control and Alt and press kc
// LSA(kc)		Hold Left Shift and Left Alt and press kc
// RSA(kc)	SAGR(kc)	Hold Right Shift and Right Alt (AltGr) and press kc
// RCS(kc)		Hold Right Control and Right Shift and press kc
// LCAG(kc)		Hold Left Control, Alt and GUI and press kc
// MEH(kc)		Hold Left Control, Shift and Alt and press kc
// HYPR(kc)		Hold Left Control, Shift, Alt and GUI and press kc
// KC_MEH		Left Control, Shift and Alt
// KC_HYPR		Left Control, Shift, Alt and GUI
// Mod-Tap Keys :id=mod-tap-keys
// See also: Mod-Tap

// Key	Aliases	Description
// MT(mod, kc)		mod when held, kc when tapped
// LCTL_T(kc)	CTL_T(kc)	Left Control when held, kc when tapped
// LSFT_T(kc)	SFT_T(kc)	Left Shift when held, kc when tapped
// LALT_T(kc)	LOPT_T(kc), ALT_T(kc), OPT_T(kc)	Left Alt when held, kc when tapped
// LGUI_T(kc)	LCMD_T(kc), LWIN_T(kc), GUI_T(kc), CMD_T(kc), WIN_T(kc)	Left GUI when held, kc when tapped
// RCTL_T(kc)		Right Control when held, kc when tapped
// RSFT_T(kc)		Right Shift when held, kc when tapped
// RALT_T(kc)	ROPT_T(kc), ALGR_T(kc)	Right Alt (AltGr) when held, kc when tapped
// RGUI_T(kc)	RCMD_T(kc), RWIN_T(kc)	Right GUI when held, kc when tapped
// LSG_T(kc)	SGUI_T(kc), SCMD_T(kc), SWIN_T(kc)	Left Shift and GUI when held, kc when tapped
// LAG_T(kc)		Left Alt and GUI when held, kc when tapped
// RSG_T(kc)		Right Shift and GUI when held, kc when tapped
// RAG_T(kc)		Right Alt and GUI when held, kc when tapped
// LCA_T(kc)		Left Control and Alt when held, kc when tapped
// LSA_T(kc)		Left Shift and Left Alt when held, kc when tapped
// RSA_T(kc)	SAGR_T(kc)	Right Shift and Right Alt (AltGr) when held, kc when tapped
// RCS_T(kc)		Right Control and Right Shift when held, kc when tapped
// LCAG_T(kc)		Left Control, Alt and GUI when held, kc when tapped
// RCAG_T(kc)		Right Control, Alt and GUI when held, kc when tapped
// C_S_T(kc)		Left Control and Shift when held, kc when tapped
// MEH_T(kc)		Left Control, Shift and Alt when held, kc when tapped
// HYPR_T(kc)	ALL_T(kc)	Left Control, Shift, Alt and GUI when held, kc when tapped - more info here
// Tapping Term Keys :id=tapping-term-keys
// See also: Dynamic Tapping Term

// Key	Aliases	Description
// QK_DYNAMIC_TAPPING_TERM_PRINT	DT_PRNT	Types the current tapping term, in milliseconds
// QK_DYNAMIC_TAPPING_TERM_UP	DT_UP	Increases the current tapping term by DYNAMIC_TAPPING_TERM_INCREMENTms (5ms by default)
// QK_DYNAMIC_TAPPING_TERM_DOWN	DT_DOWN	Decreases the current tapping term by DYNAMIC_TAPPING_TERM_INCREMENTms (5ms by default)
// RGB Lighting :id=rgb-lighting
// See also: RGB Lighting

// Key	Aliases	Description
// RGB_TOG		Toggle RGB lighting on or off
// RGB_MODE_FORWARD	RGB_MOD	Cycle through modes, reverse direction when Shift is held
// RGB_MODE_REVERSE	RGB_RMOD	Cycle through modes in reverse, forward direction when Shift is held
// RGB_HUI		Increase hue, decrease hue when Shift is held
// RGB_HUD		Decrease hue, increase hue when Shift is held
// RGB_SAI		Increase saturation, decrease saturation when Shift is held
// RGB_SAD		Decrease saturation, increase saturation when Shift is held
// RGB_VAI		Increase value (brightness), decrease value when Shift is held
// RGB_VAD		Decrease value (brightness), increase value when Shift is held
// RGB_MODE_PLAIN	RGB_M_P 	Static (no animation) mode
// RGB_MODE_BREATHE	RGB_M_B	Breathing animation mode
// RGB_MODE_RAINBOW	RGB_M_R	Rainbow animation mode
// RGB_MODE_SWIRL	RGB_M_SW	Swirl animation mode
// RGB_MODE_SNAKE	RGB_M_SN	Snake animation mode
// RGB_MODE_KNIGHT	RGB_M_K	"Knight Rider" animation mode
// RGB_MODE_XMAS	RGB_M_X	Christmas animation mode
// RGB_MODE_GRADIENT	RGB_M_G	Static gradient animation mode
// RGB_MODE_RGBTEST	RGB_M_T	Red,Green,Blue test animation mode
// RGB Matrix Lighting :id=rgb-matrix-lighting
// See also: RGB Matrix Lighting

// Key	Aliases	Description
// RGB_TOG		Toggle RGB lighting on or off
// RGB_MODE_FORWARD	RGB_MOD	Cycle through modes, reverse direction when Shift is held
// RGB_MODE_REVERSE	RGB_RMOD	Cycle through modes in reverse, forward direction when Shift is held
// RGB_HUI		Increase hue, decrease hue when Shift is held
// RGB_HUD		Decrease hue, increase hue when Shift is held
// RGB_SAI		Increase saturation, decrease saturation when Shift is held
// RGB_SAD		Decrease saturation, increase saturation when Shift is held
// RGB_VAI		Increase value (brightness), decrease value when Shift is held
// RGB_VAD		Decrease value (brightness), increase value when Shift is held
// RGB_SPI		Increase effect speed (does not support eeprom yet), decrease speed when Shift is held
// RGB_SPD		Decrease effect speed (does not support eeprom yet), increase speed when Shift is held
// US ANSI Shifted Symbols :id=us-ansi-shifted-symbols
// See also: US ANSI Shifted Symbols

// Key	Aliases	Description
// KC_TILDE	KC_TILD	~
// KC_EXCLAIM	KC_EXLM	!
// KC_AT		@
// KC_HASH		#
// KC_DOLLAR	KC_DLR	$
// KC_PERCENT	KC_PERC	%
// KC_CIRCUMFLEX	KC_CIRC	^
// KC_AMPERSAND	KC_AMPR	&
// KC_ASTERISK	KC_ASTR	*
// KC_LEFT_PAREN	KC_LPRN	(
// KC_RIGHT_PAREN	KC_RPRN	)
// KC_UNDERSCORE	KC_UNDS	_
// KC_PLUS		+
// KC_LEFT_CURLY_BRACE	KC_LCBR	{
// KC_RIGHT_CURLY_BRACE	KC_RCBR	}
// KC_PIPE		|
// KC_COLON	KC_COLN	:
// KC_DOUBLE_QUOTE	KC_DQUO, KC_DQT	"
// KC_LEFT_ANGLE_BRACKET	KC_LABK, KC_LT	<
// KC_RIGHT_ANGLE_BRACKET	KC_RABK, KC_GT	>
// KC_QUESTION	KC_QUES	?
// One Shot Keys :id=one-shot-keys
// See also: One Shot Keys

// Key	Aliases	Description
// OSM(mod)		Hold mod for one keypress
// OSL(layer)		Switch to layer for one keypress
// QK_ONE_SHOT_TOGGLE	OS_TOGG	Toggles One Shot keys status
// QK_ONE_SHOT_ON	OS_ON	Turns One Shot keys on
// QK_ONE_SHOT_OFF	OS_OFF	Turns One Shot keys off
// Programmable Button Support :id=programmable-button
// See also: Programmable Button

// Key	Aliases	Description
// QK_PROGRAMMABLE_BUTTON_1	PB_1	Programmable button 1
// QK_PROGRAMMABLE_BUTTON_2	PB_2	Programmable button 2
// QK_PROGRAMMABLE_BUTTON_3	PB_3	Programmable button 3
// QK_PROGRAMMABLE_BUTTON_4	PB_4	Programmable button 4
// QK_PROGRAMMABLE_BUTTON_5	PB_5	Programmable button 5
// QK_PROGRAMMABLE_BUTTON_6	PB_6	Programmable button 6
// QK_PROGRAMMABLE_BUTTON_7	PB_7	Programmable button 7
// QK_PROGRAMMABLE_BUTTON_8	PB_8	Programmable button 8
// QK_PROGRAMMABLE_BUTTON_9	PB_9	Programmable button 9
// QK_PROGRAMMABLE_BUTTON_10	PB_10	Programmable button 10
// QK_PROGRAMMABLE_BUTTON_11	PB_11	Programmable button 11
// QK_PROGRAMMABLE_BUTTON_12	PB_12	Programmable button 12
// QK_PROGRAMMABLE_BUTTON_13	PB_13	Programmable button 13
// QK_PROGRAMMABLE_BUTTON_14	PB_14	Programmable button 14
// QK_PROGRAMMABLE_BUTTON_15	PB_15	Programmable button 15
// QK_PROGRAMMABLE_BUTTON_16	PB_16	Programmable button 16
// QK_PROGRAMMABLE_BUTTON_17	PB_17	Programmable button 17
// QK_PROGRAMMABLE_BUTTON_18	PB_18	Programmable button 18
// QK_PROGRAMMABLE_BUTTON_19	PB_19	Programmable button 19
// QK_PROGRAMMABLE_BUTTON_20	PB_20	Programmable button 20
// QK_PROGRAMMABLE_BUTTON_21	PB_21	Programmable button 21
// QK_PROGRAMMABLE_BUTTON_22	PB_22	Programmable button 22
// QK_PROGRAMMABLE_BUTTON_23	PB_23	Programmable button 23
// QK_PROGRAMMABLE_BUTTON_24	PB_24	Programmable button 24
// QK_PROGRAMMABLE_BUTTON_25	PB_25	Programmable button 25
// QK_PROGRAMMABLE_BUTTON_26	PB_26	Programmable button 26
// QK_PROGRAMMABLE_BUTTON_27	PB_27	Programmable button 27
// QK_PROGRAMMABLE_BUTTON_28	PB_28	Programmable button 28
// QK_PROGRAMMABLE_BUTTON_29	PB_29	Programmable button 29
// QK_PROGRAMMABLE_BUTTON_30	PB_30	Programmable button 30
// QK_PROGRAMMABLE_BUTTON_31	PB_31	Programmable button 31
// QK_PROGRAMMABLE_BUTTON_32	PB_32	Programmable button 32
// Repeat Key :id=repeat-key
// See also: Repeat Key

// Keycode	Aliases	Description
// QK_REPEAT_KEY	QK_REP	Repeat the last pressed key
// QK_ALT_REPEAT_KEY	QK_AREP	Perform alternate of the last key
// Space Cadet :id=space-cadet
// See also: Space Cadet

// Key	Aliases	Description
// QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN	SC_LCPO	Left Control when held, ( when tapped
// QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE	SC_RCPC	Right Control when held, ) when tapped
// QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN	SC_LSPO	Left Shift when held, ( when tapped
// QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE	SC_RSPC	Right Shift when held, ) when tapped
// QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN	SC_LAPO	Left Alt when held, ( when tapped
// QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE	SC_RAPC	Right Alt when held, ) when tapped
// QK_SPACE_CADET_RIGHT_SHIFT_ENTER	SC_SENT	Right Shift when held, Enter when tapped
// Swap Hands :id=swap-hands
// See also: Swap Hands

// Key	Aliases	Description
// SH_T(kc)		Momentary swap when held, kc when tapped
// QK_SWAP_HANDS_ON	SH_ON	Turn on hand swap
// QK_SWAP_HANDS_OFF	SH_OFF	Turn off hand swap
// QK_SWAP_HANDS_MOMENTARY_ON	SH_MON	Turn on hand swap while held
// QK_SWAP_HANDS_MOMENTARY_OFF	SH_MOFF	Turn off hand swap while held
// QK_SWAP_HANDS_TOGGLE	SH_TOGG	Toggle hand swap
// QK_SWAP_HANDS_TAP_TOGGLE	SH_TT	Momentary swap when held, toggle when tapped
// QK_SWAP_HANDS_ONE_SHOT	SH_OS	Turn on hand swap while held or until next key press
// Unicode Support :id=unicode-support
// See also: Unicode Support

// Key	Aliases	Description
// UC(c)		Send Unicode code point c, up to 0x7FFF
// UM(i)		Send Unicode code point at index i in unicode_map
// UP(i, j)		Send Unicode code point at index i, or j if Shift/Caps is on
// QK_UNICODE_MODE_NEXT	UC_NEXT	Cycle through selected input modes
// QK_UNICODE_MODE_PREVIOUS	UC_PREV	Cycle through selected input modes in reverse
// QK_UNICODE_MODE_MACOS	UC_MAC	Switch to macOS input
// QK_UNICODE_MODE_LINUX	UC_LINX	Switch to Linux input
// QK_UNICODE_MODE_WINDOWS	UC_WIN	Switch to Windows input
// QK_UNICODE_MODE_BSD	UC_BSD	Switch to BSD input (not implemented)
// QK_UNICODE_MODE_WINCOMPOSE	UC_WINC	Switch to Windows input using WinCompose
// QK_UNICODE_MODE_EMACS	UC_EMAC	Switch to emacs (C-x-8 RET)
*/
