#include <stdio.h>
#include <stdlib.h>

#include "../crypt_helpers.h"

/* Repeating-key XOR */

static struct DecodedData *encrypt_xor_repeating_key(
    const struct DecodedData *data, const struct DecodedData *key) {
    struct DecodedData *encrypted_data = NULL;
    size_t key_index = 0;

    encrypted_data = malloc(sizeof(struct DecodedData));
    encrypted_data->size = data->size;
    encrypted_data->data = malloc(data->size);

    for (size_t i = 0; i < data->size; ++i) {
        encrypted_data->data[i] = data->data[i] ^ key->data[key_index];

        key_index = ((key_index + 1) == key->size ? 0 : key_index + 1);
    }

    return encrypted_data;
}

int main() { 
    const char text_data[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char key[] = "ICE";

    struct DecodedData *r_text_data = new_decode(text_data, strlen(text_data));
    struct DecodedData *r_key = new_decode(key, strlen(key));

    struct DecodedData *encrypted_data = encrypt_xor_repeating_key(r_text_data, r_key);

    print_decoded_data(encrypted_data, PRINT_TYPE_HEX);

    free_hex_decode(r_text_data);
    free_hex_decode(r_key);
    free_hex_decode(encrypted_data);

    return EXIT_SUCCESS;    
}