#include "libmips.h"

inline static int syscall_1(int sys, int arg1) {
    int ret;
    asm("move $v0, %1\n"
        "move $a0, %2\n"
        "syscall\n"
        "move %0, $a0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1)
        : "$v0", "$a0");
    return ret;
}

inline static int syscall_3(int sys, int arg1, int arg2, int arg3) {
    int ret;
    asm("move $v0, %1\n"
        "move $a0, %2\n"
        "move $a1, %3\n"
        "move $a2, %4\n"
        "syscall\n"
        "move %0, $a0"
        : "=r"(ret)
        : "r"(sys), "r"(arg1), "r"(arg2), "r"(arg3)
        : "$v0", "$a0", "$a1", "$a2");
    return ret;
}

void exit(int ret) {
    asm("li $v0, 0\n"
        "move $a0, %0\n"
        "syscall\n"
        :
        : "r"(ret)
        : "$v0", "$a0");
}

int read(int fd, char *buf, int count) {
    return syscall_3(SYS_read, fd, (int)buf, count);
}

int write(int fd, char *buf, int count) {
    return syscall_3(SYS_write, fd, (int)buf, count);
}

int open(char *pathname, int flags, int mode) {
    return syscall_3(SYS_open, (int)pathname, flags, mode);
}

int close(int fd) {
    return syscall_1(SYS_close, fd);
}

int main();

__attribute__ ((section (".init"))) void _start() {
    exit(main());
}
