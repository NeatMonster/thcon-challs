#include "libi386.h"

#include "lz4.h"

struct segment {
    unsigned char *mmap_addr;
    unsigned long mmap_size;
    unsigned char *data_addr;
    unsigned long data_size;
    unsigned int mprotect;
    unsigned char compressed;
};

#include "segments.c"
static int (*entry_point)(int, char **) = (int (*)(int, char **))main_addr;

int main(int argc, char *argv[]) {
    int i, ret;
    unsigned char *addr;
    unsigned long size;
    struct segment *s;

    for (i = 0; i < segments_count; ++i) {
        s = &segments[i];

        size = s->mmap_size;
        size += 0xfff;
        size &= ~0xfff;

        addr = mmap(s->mmap_addr, size, PROT_READ | PROT_WRITE,
                    MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
        if (addr != s->mmap_addr)
            return -1;

        if (s->compressed)
            LZ4_decompress_safe(s->data_addr, addr, s->data_size, size);
        else
            memcpy(addr, s->data_addr, s->data_size);

        ret = mprotect(addr, size, s->mprotect);
        if (ret < 0)
            return -1;
    }

    return entry_point(argc, argv);
}
