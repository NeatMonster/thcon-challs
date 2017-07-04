#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: ./lfsr <key> <input> <output>\n");
        return -1;
    }

    FILE *fd = fopen(argv[2], "rb");
    fseek(fd, 0, SEEK_END);
    int payload_size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char *payload = malloc(payload_size);
    fread(payload, 1, payload_size, fd);
    fclose(fd);

    int i, j = 0, k;
    unsigned char c, lfsr[8] = { 0 };

    for (i = 0; i < 16; ++i) {
        c = argv[1][15 - i];
        if (c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'A' && c <= 'F')
            c -= 'A' - 10;

        if (i % 2) c <<= 4;
        lfsr[j] |= c;
        if (i % 2) ++j;
    }

    for (i = 0; i < payload_size; ++i) {
        c = 0;
        for (j = 0; j < 8; ++j) {
            k = *((unsigned long long *)lfsr) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 59) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 60) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 62) & 1;
            k ^= (*((unsigned long long *)lfsr) >> 63) & 1;
            *((unsigned long long *)lfsr) >>= 1;
            *((unsigned long long *)lfsr) |= (unsigned long long) k << 63;
            c |= (unsigned char) k << j;
        }
        payload[i] ^= c;
    }

    fd = fopen(argv[3], "wb+");
    fwrite(payload, 1, payload_size, fd);
    fclose(fd);

    return 0;
}
