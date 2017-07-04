#ifndef mipsvm_h
#define mipsvm_h

#include "libi386.h"

#include "chacha.h"

typedef uint8_t  byte_t;
typedef uint16_t half_t;
typedef uint32_t word_t;

typedef int8_t  sbyte_t;
typedef int16_t shalf_t;
typedef int32_t sword_t;

typedef word_t reg_t;
typedef struct {
    reg_t zero, at, v0, v1, a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7,
            s0, s1, s2, s3, s4, s5, s6, s7, t8, t9, k0, k1, gp, sp, fp, ra;
} regs_t;

#define MEM_SIZE 0x10000
#define MEM_MASK (MEM_SIZE - 1)

#define CACHE_SIZE 0x800
#define CACHE_MASK (CACHE_SIZE - 1)

#define PAGE_SIZE   0x40
#define ENTRY_COUNT (CACHE_SIZE / PAGE_SIZE)

typedef struct {
    uint64_t page;
    uint64_t index;
    struct {
        unsigned written:1;
        unsigned present:1;
    } flags;
    uint64_t access;
} entry_t;

#define SIGNEXT(size, val) (((sword_t)val << (32 - size)) >> (32 - size))

typedef union {
    struct {
        unsigned funct:6;
        unsigned sa:5;
        unsigned rd:5;
        unsigned rt:5;
        unsigned rs:5;
        unsigned opcode:6;
    } as_r;

    struct {
        unsigned immed:16;
        unsigned rt:5;
        unsigned rs:5;
        unsigned opcode:6;
    } as_i;

    struct {
        unsigned target:26;
        unsigned opcode:6;
    } as_j;
} instr_t;

struct _state_t;
typedef void (*handler_t)(struct _state_t *, instr_t);

typedef struct _state_t {
    regs_t regs;
    reg_t hi, lo, pc;

    entry_t map[32];
    byte_t *mem, *cache;

    unsigned int halted, ticks;
    handler_t by_funct[0x40];
    handler_t by_opcode[0x40];

    ECRYPT_ctx ctx;
} state_t;

enum {
    FUNCT_SLL = 0x00,
    FUNCT_SRL = 0x02,
    FUNCT_SRA = 0x03,
    FUNCT_SLLV = 0x04, 
    FUNCT_SRLV = 0x06, 
    FUNCT_SRAV = 0x07, 
    FUNCT_JR = 0x08, 
    FUNCT_JALR = 0x09, 
    FUNCT_SYSCALL = 0x0c, 
    FUNCT_BREAK = 0x0d, 
    FUNCT_MFHI = 0x10, 
    FUNCT_MTHI = 0x11, 
    FUNCT_MFLO = 0x12, 
    FUNCT_MTLO = 0x13, 
    FUNCT_MULT = 0x18, 
    FUNCT_MULTU = 0x19, 
    FUNCT_DIV = 0x1a, 
    FUNCT_DIVU = 0x1b, 
    FUNCT_ADDU = 0x21, 
    FUNCT_SUBU = 0x23, 
    FUNCT_AND = 0x24, 
    FUNCT_OR = 0x25, 
    FUNCT_XOR = 0x26, 
    FUNCT_NOR = 0x27, 
    FUNCT_SLT = 0x2a, 
    FUNCT_SLTU = 0x2b
} FUNCT_ENUM;

enum {
    OPCODE_BLTZ_BGEZ = 0x01,
    OPCODE_J = 0x02, 
    OPCODE_JAL = 0x03, 
    OPCODE_BEQ = 0x04, 
    OPCODE_BNE = 0x05, 
    OPCODE_BLEZ = 0x06, 
    OPCODE_BGTZ = 0x07, 
    OPCODE_ADDIU = 0x09, 
    OPCODE_SLTI = 0x0a, 
    OPCODE_SLTIU = 0x0b, 
    OPCODE_ANDI = 0x0c, 
    OPCODE_ORI = 0x0d, 
    OPCODE_XORI = 0x0e, 
    OPCODE_LUI = 0x0f, 
    OPCODE_LB = 0x20, 
    OPCODE_LH = 0x21, 
    OPCODE_LWL = 0x22,
    OPCODE_LW = 0x23, 
    OPCODE_LBU = 0x24, 
    OPCODE_LHU = 0x25, 
    OPCODE_LWR = 0x26,
    OPCODE_SB = 0x28, 
    OPCODE_SH = 0x29,
    OPCODE_SWL = 0x2a, 
    OPCODE_SW = 0x2b,
    OPCODE_SWR = 0x2e
} OPCODE_ENUM;

enum {
    SYSCALL_EXIT,
    SYSCALL_READ,
    SYSCALL_WRITE,
    SYSCALL_OPEN,
    SYSCALL_CLOSE
} SYSCALL_ENUM;

enum {
    STATUS_NO_ERROR = 1,
    STATUS_BAD_PC,
    STATUS_BAD_INS,
    STATUS_MEM_FAULT
} STATUS_ENUM;

int init(state_t **);
int start(state_t *);
void tick(state_t *);
void stop(state_t *, int);

reg_t get_reg(state_t *, int);
void set_reg(state_t *, int, reg_t);

int read_mem(state_t *, word_t, void *, size_t);
int write_mem(state_t *, word_t, void *, size_t);

//void debug(state_t *, instr_t);

#endif
