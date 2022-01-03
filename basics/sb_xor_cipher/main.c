#include <string.h>

#include "sb_xor_cipher.h"

/* Tolerance for special characters outside alphanum */
#define TOLERANCE 10

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