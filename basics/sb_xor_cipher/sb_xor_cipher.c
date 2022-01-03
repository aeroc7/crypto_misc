#include "sb_xor_cipher.h"

size_t filter_xord_against(const struct DecodedData *data1) {
    size_t ctr = 0;
    for (size_t i = 0; i < data1->size; ++i) {
        char cur_c = data1->data[i];
        ctr += 1;

        if (cur_c >= 'A' && cur_c <= 'Z') {
            continue;
        }

        if (cur_c >= 'a' && cur_c <= 'z') {
            continue;
        }

        if (cur_c == ' ') {
            continue;
        }

        if (cur_c >= '0' && cur_c <= '9') {
            continue;
        } else {
            return ctr;
        }
    }

    return ctr;
}

struct DecodedData *xor_against_c(const struct DecodedData *data1, char c) {
    struct DecodedData *xord = NULL;

    xord = malloc(sizeof(struct DecodedData));
    xord->data = malloc(data1->size);
    xord->size = data1->size;

    for (size_t i = 0; i < data1->size; ++i) {
        xord->data[i] = data1->data[i] ^ c;
    }

    return xord;
}