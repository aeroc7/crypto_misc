#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const char *B64_TABLE =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static long hex_to_decimal(const char *data) {
    uint_fast8_t hex_quivs[2];

    for (int i = 0; i < 2; ++i) {
        char bytea[] = {data[i], '\0'};
        hex_quivs[i] = strtol(bytea, NULL, 16);
    }

    return (hex_quivs[0] * 16) + hex_quivs[1];
}

size_t b64_encoded_size(size_t len) {
    size_t b64_len = len;

    if ((b64_len % 3) != 0) {
        b64_len += (3 - (b64_len % 3));
    }

    b64_len /= 3;
    b64_len *= 4;

    return b64_len;
}

/* Returns pointer to null-terminated, heap-allocated buffer */
char *encode_b64(const char *data, size_t size) {
    const size_t b64len = b64_encoded_size(size);
    char *b64encoded = malloc(b64len + 1);

    uint32_t v = 0;
    size_t b64i = 0;

    for (size_t i = 0; i < size; i += 6, b64i += 4) {
        v = 0;

        const char v1 = hex_to_decimal(&data[i]);
        const char v2 = hex_to_decimal(&data[i + 2]);
        const char v3 = hex_to_decimal(&data[i + 4]);

        const char ndata[] = {v1, v2, v3};

        v |= (ndata[0] << 24);
        v |= (ndata[1] << 16);
        v |= (ndata[2] << 8);

        /* Make offset even increments of 6 */
        v >>= 2;

        b64encoded[b64i] = B64_TABLE[(v >> 24) & 0x3F];
        b64encoded[b64i + 1] = B64_TABLE[(v >> 18) & 0x3F];
        b64encoded[b64i + 2] = B64_TABLE[(v >> 12) & 0x3F];
        b64encoded[b64i + 3] = B64_TABLE[(v >> 6) & 0x3F];
    }

    b64encoded[b64len] = '\0';

    return b64encoded;
}

int main(int argc, char *argv[]) {
    const char data[] =
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f"
        "6e6f7573206d757368726f6f6d";

    const char *encoded_data = encode_b64(data, sizeof(data) - 1);
    printf("%s", encoded_data);
    free((void *)encoded_data);

    return EXIT_SUCCESS;
}