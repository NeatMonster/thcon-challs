#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <elf.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: /elf_util <input> <output>\n");
        return -1;
    }

    FILE *fd = fopen(argv[1], "rb");
    fseek(fd, 0, SEEK_END);
    int size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char *buf = malloc(size);
    fread(buf, 1, size, fd);
    fclose(fd);

    fd = fopen(argv[2], "w+");
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)buf;

    int *compressed = (int *)malloc(ehdr->e_phnum * sizeof(int));
    memset(compressed, 0, ehdr->e_phnum);

    int segments_count = 0;
    for (int i = 0; i < ehdr->e_phnum; ++i) {
        Elf64_Phdr *phdr = (Elf64_Phdr *)(buf + ehdr->e_phoff + ehdr->e_phentsize * i);
        if (phdr->p_type & PT_LOAD && phdr->p_filesz) {
            ++segments_count;

            char cmd[512];
            sprintf(cmd, "cd bin && dd bs=1 skip=%ld count=%ld if=../%s of=segment%i",
                   phdr->p_offset, phdr->p_filesz, argv[1], i);
            system(cmd);
            sprintf(cmd, "cd bin && ./lz4_util segment%i segment%i.lz4", i, i);
            system(cmd);

            sprintf(cmd, "bin/segment%i", i);
            FILE *fd_seg = fopen(cmd, "rb");
            fseek(fd_seg, 0, SEEK_END);
            int bin_size = ftell(fd_seg);
            fclose(fd_seg);

            sprintf(cmd, "bin/segment%i.lz4", i);
            fd_seg = fopen(cmd, "rb");
            fseek(fd_seg, 0, SEEK_END);
            int lz4_size = ftell(fd_seg);
            fclose(fd_seg);

            compressed[i] = lz4_size < bin_size ? 1 : 0;
            if (compressed[i])
                sprintf(cmd, "cd bin && xxd -i segment%i.lz4 > segment%i.c"
                    " && sed -i -e 's/unsigned int \\(\\w\\+\\) = \\(\\w\\+\\);/#define \\1 \\2/g' segment%i.c", i, i, i);
            else
                sprintf(cmd, "cd bin && xxd -i segment%i > segment%i.c"
                    " && sed -i -e 's/unsigned int \\(\\w\\+\\) = \\(\\w\\+\\);/#define \\1 \\2/g' segment%i.c", i, i, i);
            system(cmd);

            fprintf(fd, "#include \"segment%i.c\"\n", i);
        }
    }

    fprintf(fd, "\nstatic struct segment segments[] = {\n");

    for (int i = 0; i < ehdr->e_phnum; ++i) {
        Elf64_Phdr *phdr = (Elf64_Phdr *)(buf + ehdr->e_phoff + ehdr->e_phentsize * i);
        if (phdr->p_type & PT_LOAD && phdr->p_filesz) {
            fprintf(fd, "    { .mmap_addr = (unsigned char *)0x%lx,\n", phdr->p_vaddr);
            fprintf(fd, "      .mmap_size = 0x%lx,\n", phdr->p_memsz);
            if (compressed[i]) {
                fprintf(fd, "      .data_addr = segment%i_lz4,\n", i);
                fprintf(fd, "      .data_size = segment%i_lz4_len,\n", i);
            } else {
                fprintf(fd, "      .data_addr = segment%i,\n", i);
                fprintf(fd, "      .data_size = segment%i_len,\n", i);
            }
            fprintf(fd, "      .mprotect = 0");
            if (phdr->p_flags & PF_X)
                fprintf(fd, " | PROT_EXEC");
            if (phdr->p_flags & PF_W)
                fprintf(fd, " | PROT_WRITE");
            if (phdr->p_flags & PF_R)
                fprintf(fd, " | PROT_READ");
            fprintf(fd, ",\n");
            fprintf(fd, "      .compressed = %i },\n", compressed[i]);
        }
    }

    fprintf(fd, "};\n");
    fprintf(fd, "static int segments_count = %d;\n", segments_count);
    fclose(fd);

    return 0;
}
