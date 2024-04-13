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

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_ESC, KC_SLEP, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T), KC_G, KC_NO, KC_NO, KC_M, LSFT_T(KC_N), LGUI_T(KC_E), LALT_T(KC_I), LCTL_T(KC_O), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_NO, KC_NO, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_NO, KC_TAB, LT(2, KC_SPC), KC_LSFT, LALT(KC_TAB), LT(1, KC_ENT), LT(3, KC_BSPC), KC_TAB, KC_NO, KC_NO),

    [1] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, QK_BOOT, KC_NO, KC_VOLD, LSFT(KC_GT), KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_LEFT, KC_MPLY, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, LSFT(KC_LT), KC_MNXT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO),

    [2] = LAYOUT(KC_QUES, KC_DLR, KC_GRV, KC_ASTR, KC_CIRC, KC_NO, KC_NO, KC_BSLS, KC_EQL, KC_QUOT, KC_PERC, KC_AMPR, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_NO, KC_NO, KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_PDOT, KC_MINS, KC_PIPE, KC_LT, KC_LBRC, KC_NO, KC_NO, KC_RBRC, KC_GT, KC_EXLM, KC_HASH, KC_AT, KC_NO, KC_NO, KC_TRNS, KC_TRNS, SC_LSPO, KC_TRNS, SC_RSPC, KC_TRNS, KC_TRNS, KC_NO, KC_NO),

    [3] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, LCTL(KC_PGDN), KC_UP, LCTL(KC_PGUP), KC_NO, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_T), LCTL(KC_W), KC_NO, KC_NO, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_BSPC), LCTL(KC_Z), LCTL(KC_PMNS), LCTL(KC_PPLS), KC_TAB, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_WBAK, KC_WSCH, KC_WFWD, KC_BSPC, KC_NO, KC_NO, KC_TRNS, KC_LALT, LCTL(KC_F), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO)

};
// clang-format on