#ifndef SB_XOR_CIPHER_H_
#define SB_XOR_CIPHER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../crypt_helpers.h"

size_t filter_xord_against(const struct DecodedData *data1);
struct DecodedData *xor_against_c(const struct DecodedData *data1, char c);

#endif