#include "layer_selection.h"
#include "layer_list.h"

enum quinoa_layers {
#define QUINOA_X(LAYER, STRING) U_##LAYER,
QUINOA_LAYER_LIST
#undef QUINOA_X
};