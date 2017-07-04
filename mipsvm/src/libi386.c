#include "libi386.h"

void exit(int ret) {
    long long sys = SYS_exit;
    asm("mov %0, %%rax\n"
        "mov %1, %%rdi\n"
        "syscall"
        :
        : "r"(sys), "r"((long long) ret)
        : "%rax", "%rdi"
    );
}

inline static long long syscall_1(long long sys, long long arg1) {
    long long ret;
    asm("mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1)
        : "%rax", "%rdi"
    );
    return ret;
}

inline static long long syscall_2(long long sys, long long arg1, long long arg2) {
    long long ret;
    asm("mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1), "r"(arg2)
        : "%rax", "%rdi", "%rsi"
    );
    return ret;
}

inline static long long syscall_3(long long sys, long long arg1, long long arg2, long long arg3) {
    long long ret;
    asm("mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1), "r"(arg2), "r"(arg3)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return ret;
}

inline static long long syscall_6(long long sys, long long arg1, long long arg2, long long arg3,
                    long long arg4, long long arg5, long long arg6) {
    long long ret;
    asm("mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "mov %5, %%r10\n"
        "mov %6, %%r8\n"
        "mov %7, %%r9\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5), "r"(arg6)
        : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9"
    );
    return ret;
}

int read(int fd, char *buf, int count) {
    return syscall_3(SYS_read, fd, (long long)buf, count);
}

int write(int fd, char *buf, int count) {
    return syscall_3(SYS_write, fd, (long long)buf, count);
}

int open(char *pathname, int flags, int mode) {
    return syscall_3(SYS_open, (long long)pathname, flags, mode);
}

int close(int fd) {
    return syscall_1(SYS_close, fd);
}

char *mmap(void *addr, int length, int prot, int flags, int fd, int offset) {
    return (char *)syscall_6(SYS_mmap, (long long)addr, length, prot, flags, fd, offset);
}

int mprotect(void *addr, int len, int prot) {
    return syscall_3(SYS_mprotect, (long long)addr, len, prot);
}

int munmap(void *addr, int length) {
    return syscall_2(SYS_munmap, (long long)addr, length);
}

void *memset(void *ptr, int value, int num) {
    int i;
    for (i = 0; i < num; ++i)
        ((char *)ptr)[i] = value;
    return ptr;
}

void *memcpy(void *dst, void *src, int n) {
    int i;
    for (i = 0; i < n; ++i)
        ((char *)dst)[i] = ((char *)src)[i];
    return dst;
}

void *memmove(void *dst, void *src, int n) {
    int i;
    if (dst < src) {
        for (i = 0; i < n; ++i)
            ((char *)dst)[i] = ((char *)src)[i];
    } else {
        for (i = n - 1; i >= 0; --i)
            ((char *)dst)[i] = ((char *)src)[i];
    }
    return dst;
}

void *malloc(int size) {
    char *ptr = mmap(0, size + 4, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    *((int *)ptr) = size;
    return ptr + 4;
}

void *calloc(int num, int size) {
    void *ptr = malloc(num * size);
    memset(ptr, 0, size);
    return ptr;
}

void free(void *ptr) {
    int size = *((int *)(ptr - 4));
    munmap(ptr, size);
}
