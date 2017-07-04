#ifndef libi386_h
#define libi386_h

#define NULL 0

#define SYS_read     0
#define SYS_write    1
#define SYS_open     2
#define SYS_close    3
#define SYS_mmap     9
#define SYS_mprotect 10
#define SYS_munmap   11
#define SYS_exit     60

#define STDIN  0
#define STDOUT 1

#define O_RDONLY 0x000
#define O_WRONLY 0x001
#define O_CREAT  0x200
#define O_TRUNC  0x400

#define PROT_READ  0x1
#define PROT_WRITE 0x2
#define PROT_EXEC  0x4

#define MAP_PRIVATE   0x02
#define MAP_FIXED     0x10
#define MAP_ANONYMOUS 0x20

typedef char      int8_t;
typedef short     int16_t;
typedef int       int32_t;
typedef long long int64_t;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef uint64_t size_t;
typedef uint64_t time_t;

typedef uint64_t uintptr_t;
typedef int64_t  ptrdiff_t;

void exit(int);

int read(int, char *, int);

int write(int, char *, int);

int open(char *, int, int);

int close(int);

char *mmap(void *, int, int, int, int, int);

int mprotect(void *, int, int);

int munmap(void *, int);

void *memset(void *, int, int);

void *memcpy(void *, void *, int);

void *memmove(void *, void *, int);

void *malloc(int);

void *calloc(int, int);

void free(void *);

#endif
