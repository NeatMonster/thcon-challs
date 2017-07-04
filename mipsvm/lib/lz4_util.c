#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz4.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: /lz4_util <input> <output>\n");
        return -1;
    }

    FILE *fd = fopen(argv[1], "rb");
    fseek(fd, 0, SEEK_END);
    int mmap_size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char *mmap_buf = malloc(mmap_size);
    fread(mmap_buf, 1, mmap_size, fd);
    fclose(fd);

    int data_size = LZ4_compressBound(mmap_size);
    char *data_buf = malloc(data_size);
    data_size = LZ4_compress_default(mmap_buf, data_buf, mmap_size, data_size);
    data_buf = realloc(data_buf, data_size);

    fd = fopen(argv[2], "wb+");
    fwrite(data_buf, 1, data_size, fd);
    fclose(fd);

    return 0;
}
