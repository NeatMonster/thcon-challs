#ifndef libmips_h
#define libmips_h

#define SYS_exit  0
#define SYS_read  1
#define SYS_write 2
#define SYS_open  3
#define SYS_close 4

#define STDIN  0
#define STDOUT 1

#define O_WRONLY 0x001
#define O_CREAT  0x040
#define O_TRUNC  0x200

void exit(int);

int read(int, char *, int);

int write(int, char *, int);

int open(char *, int, int);

int close(int);

#endif
