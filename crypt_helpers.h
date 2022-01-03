#ifndef UTILS_H_
#define UTILS_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DecodedData {
    uint8_t *data;
    size_t size;
};

enum PrintType { PRINT_TYPE_NUM, PRINT_TYPE_CHAR };

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

static void print_decoded_data(
    const struct DecodedData *dd, enum PrintType pt) {
    char *fmt_str = NULL;

    if (pt == PRINT_TYPE_NUM) {
        fmt_str = "%i ";
    } else if (pt == PRINT_TYPE_CHAR) {
        fmt_str = "%c ";
    }

    for (size_t i = 0; i < dd->size; ++i) {
        printf(fmt_str, dd->data[i]);
    }

    putchar('\n');
}

static void *free_hex_decode(struct DecodedData *s) {
    free(s->data);
    free(s);

    return NULL;
}

static void strip_newline(char *line) {
    const size_t len = strlen(line);

    for (size_t i = 0; i < len; ++i) {
        if (line[i] == '\n') {
            /* null-terminate instead */
            line[i] = '\0';
            return;
        }
    }
}

#endif