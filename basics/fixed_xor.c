#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../crypt_helpers.h"

static struct DecodedData *xor_with(
    const struct DecodedData *data1, const struct DecodedData *data2) {
    assert(data1->size == data2->size);

    struct DecodedData *xord_data = NULL;

    xord_data = malloc(sizeof(struct DecodedData));
    xord_data->size = data1->size;
    xord_data->data = malloc(xord_data->size + 1);

    for (size_t i = 0; i < xord_data->size; ++i) {
        xord_data->data[i] = (data1->data[i] ^ data2->data[i]);
    }

    xord_data->data[xord_data->size] = '\0';

    return xord_data;
}

int main() {
    const char data[] = "1c0111001f010100061a024b53535009181c";
    const char xor_data[] = "686974207468652062756c6c277320657965";

    struct DecodedData *decoded_data = hex_decode(data, strlen(data));
    struct DecodedData *decoded_xor_data =
        hex_decode(xor_data, strlen(xor_data));

    struct DecodedData *result = xor_with(decoded_data, decoded_xor_data);

    for (size_t i = 0; i < result->size; ++i) {
        printf("%x", result->data[i]);
    }

    putchar('\n');

    decoded_data = free_hex_decode(decoded_data);
    decoded_xor_data = free_hex_decode(decoded_xor_data);
    result = free_hex_decode(result);

    return EXIT_SUCCESS;
}