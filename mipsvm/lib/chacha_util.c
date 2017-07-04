#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chacha.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: /chacha_util <key> <input> <output>\n");
        return -1;
    }

    FILE *fd = fopen(argv[2], "rb");
    fseek(fd, 0, SEEK_END);
    int plain_size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char *plain_buf = malloc(plain_size);
    char *cipher_buf = malloc(plain_size);
    fread(plain_buf, 1, plain_size, fd);
    fclose(fd);

    ECRYPT_ctx ctx;
    ECRYPT_keysetup(&ctx, argv[1], 256, 64);
    unsigned long long page = 0;
    for (int i = 0; i < plain_size; i += 64) {
        ECRYPT_ivsetup(&ctx, (const u8 *)&page);
        ECRYPT_encrypt_bytes(&ctx, &plain_buf[i], &cipher_buf[i], 64);
        ++page;
    }

    fd = fopen(argv[3], "wb+");
    fwrite(cipher_buf, 1, plain_size, fd);
    fclose(fd);

    return 0;
}
