#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../crypt_helpers.h"

/* Tolerance for special characters outside alphanum */
#define TOLERANCE 10

static size_t filter_xord_against(const struct DecodedData *data1) {
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

static struct DecodedData *xor_against_c(
    const struct DecodedData *data1, char c) {
    struct DecodedData *xord = NULL;

    xord = malloc(sizeof(struct DecodedData));
    xord->data = malloc(data1->size);
    xord->size = data1->size;

    for (size_t i = 0; i < data1->size; ++i) {
        xord->data[i] = data1->data[i] ^ c;
    }

    return xord;
}

int main() {
    const char hex_data[] =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    struct DecodedData *decoded_data = hex_decode(hex_data, strlen(hex_data));

    for (int c = 0; c < 255; ++c) {
        struct DecodedData *test_decrypt = xor_against_c(decoded_data, c);

        if (filter_xord_against(test_decrypt) > TOLERANCE) {
            print_decoded_data(test_decrypt, PRINT_TYPE_CHAR);
        }

        free_hex_decode(test_decrypt);
    }

    decoded_data = free_hex_decode(decoded_data);

    return EXIT_SUCCESS;
}