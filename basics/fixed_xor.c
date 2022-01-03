#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DecodedData {
    uint8_t *data;
    size_t size;
};

static void *free_decoded_data(struct DecodedData *s) {
    free(s->data);
    free(s);

    return NULL;
}

static long hex_to_decimal_byte(const char *data) {
    uint_fast8_t hex_quivs[2];

    for (int i = 0; i < 2; ++i) {
        char bytea[] = {data[i], '\0'};
        hex_quivs[i] = strtol(bytea, NULL, 16);
    }

    return (hex_quivs[0] * 16) + hex_quivs[1];
}

static struct DecodedData *hex_decode(const char *str, size_t len) {
    /* Is even */
    assert(len % 2 == 0);

    struct DecodedData *data;
    size_t decoded_i = 0;

    data = malloc(sizeof(struct DecodedData));
    data->size = len / 2;
    data->data = malloc(data->size + 1);

    for (size_t i = 0; i < len; i += 2, decoded_i += 1) {
        const long val = hex_to_decimal_byte(&str[i]);
        data->data[decoded_i] = val;
    }

    data->data[data->size] = '\0';

    return data;
}

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

    decoded_data = free_decoded_data(decoded_data);
    decoded_xor_data = free_decoded_data(decoded_xor_data);
    result = free_decoded_data(result);

    return EXIT_SUCCESS;
}