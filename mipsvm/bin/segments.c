#include "segment0.c"
#include "segment1.c"

static struct segment segments[] = {
    { .mmap_addr = (unsigned char *)0x400000,
      .mmap_size = 0x2380,
      .data_addr = segment0_lz4,
      .data_size = segment0_lz4_len,
      .mprotect = 0 | PROT_EXEC | PROT_READ,
      .compressed = 1 },
    { .mmap_addr = (unsigned char *)0x604000,
      .mmap_size = 0x10018,
      .data_addr = segment1,
      .data_size = segment1_len,
      .mprotect = 0 | PROT_WRITE | PROT_READ,
      .compressed = 0 },
};
static int segments_count = 2;
#define main_addr 0x0000000000400150
