#include "libmips.h"

#include "payload.c"

int main() {
    int i, j = 0, k, fd;
    unsigned char c, key[16], lfsr[8] = { 0 };

    write(STDOUT, ":: Please enter the decryption key: ", 36);
    int ret = read(STDIN, key, 16);
    if (ret != 16)
        goto wrong_format;

    for (i = 0; i < 16; ++i) {
        c = key[15 - i];
        if (c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'A' && c <= 'F')
            c -= 'A' - 10;
        else
            goto wrong_format;

        if (i % 2) c <<= 4;
        lfsr[j] |= c;
        if (i % 2) ++j;
    }

    write(STDOUT, ":: Trying to decrypt payload...\n", 32);
    for (i = 0; i < payload_len; ++i) {
        c = 0;
        for (j = 0; j < 8; ++j) {
            k = *((unsigned long long *)lfsr) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 59) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 60) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 62) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 63) & 1;
            *((unsigned long long *)lfsr) >>= 1;
            *((unsigned long long *)lfsr) |= (unsigned long long) k << 63;
            c |= (char) k << j;
        }
        payload[i] ^= c;
    }

    for (i = payload_len - 8; i < payload_len; ++i)
        if (payload[i] != 0)
            goto invalid_padding;

    write(STDOUT, ":: Payload successfully decrypted.\n", 35);
    fd = open("payload.bin", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd, payload, payload_len);
    close(fd);

    return 0;

wrong_format:
    write(STDOUT, ":: Wrong key format!\n", 21);
    return -1;

invalid_padding:
    write(STDOUT, ":: Invalid padding!\n", 20);
    return -1;
}
