// #include "layer_selection.h"
// #include "layer_list.h"

// enum quinoa_layers {
// #define QUINOA_X(LAYER, STRING) U_##LAYER,
// QUINOA_LAYER_LIST
// #undef QUINOA_X
// };

// keymaps.h

#ifndef KEYMAPS_H
#define KEYMAPS_H

#include QMK_KEYBOARD_H

extern const uint16_t PROGMEM keymaps_windows[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t PROGMEM keymaps_macos[][MATRIX_ROWS][MATRIX_COLS];

#endif // KEYMAPS_H