#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../sb_xor_cipher/sb_xor_cipher.h"

#define FILE_NAME "xor_strings.txt"
#define TOLERANCE 20

static void read_xor_strings(const char *filename) {
    FILE *fp;
    char *line;
    size_t len;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1) {
        strip_newline(line);

        struct DecodedData *decoded_data = hex_decode(line, strlen(line));

        for (int c = 0; c < 255; ++c) {
            struct DecodedData *test_decrypt = xor_against_c(decoded_data, c);

            if (filter_xord_against(test_decrypt) > TOLERANCE) {
                print_decoded_data(test_decrypt, PRINT_TYPE_CHAR);
            }

            free_hex_decode(test_decrypt);
        }

        decoded_data = free_hex_decode(decoded_data);
    }

    fclose(fp);
    free(line);
}

int main() {
    read_xor_strings(FILE_NAME);

    return EXIT_SUCCESS;
}