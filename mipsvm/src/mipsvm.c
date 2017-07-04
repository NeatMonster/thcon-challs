#include "libi386.h"

#include "mipsvm.h"
#include "mipsvm_handlers.h"

#include "memory.c"

int find_entry(state_t *s, word_t addr, entry_t **entry) {
    word_t page = addr / PAGE_SIZE;
    entry_t *lru = NULL;

    for (int i = ENTRY_COUNT - 1; i >= 0; --i) {
        if (s->map[i].flags.present && s->map[i].page == page) {
            *entry = &s->map[i];
            return 0;
        }

        if (lru == NULL || !s->map[i].flags.present
                || (lru->flags.present && s->map[i].access < lru->access))
            lru = &s->map[i];
    }

    if (lru == NULL)
        return -1;

    if (lru->flags.present && lru->flags.written) {
        ECRYPT_ivsetup(&s->ctx, (const u8 *)&lru->page);
        ECRYPT_encrypt_bytes(&s->ctx, s->cache + lru->index * PAGE_SIZE,
                             s->mem + lru->page * PAGE_SIZE, PAGE_SIZE);
    }

    lru->page = page;
    lru->flags.present = 1;
    lru->flags.written = 0;
    lru->access = s->ticks;

    ECRYPT_ivsetup(&s->ctx, (const u8 *)&lru->page);
    ECRYPT_decrypt_bytes(&s->ctx, s->mem + lru->page * PAGE_SIZE,
                         s->cache + lru->index * PAGE_SIZE, PAGE_SIZE);
    *entry = lru;
    return 0;
}

int read_mem(state_t *s, word_t addr, void *dst, size_t size) {
    entry_t *entry;
    word_t caddr, csize, coffset;

    if (addr > MEM_SIZE) {
        stop(s, STATUS_MEM_FAULT);
        return -1;
    }
    addr &= MEM_MASK;

    caddr = addr;
    while (1) {
        coffset = caddr % PAGE_SIZE;
        csize = size - caddr + addr;
        if (csize > PAGE_SIZE - coffset)
            csize = PAGE_SIZE - coffset;
        if (csize == 0)
            break;
        find_entry(s, caddr, &entry);
        memcpy(dst + caddr - addr, s->cache + entry->index * PAGE_SIZE + coffset, csize);
        entry->access = s->ticks;
        caddr += csize;
    }
    return 0;
}

int write_mem(state_t *s, word_t addr, void *src, size_t size) {
    entry_t *entry;
    word_t caddr, csize, coffset;

    if (addr > MEM_SIZE) {
        stop(s, STATUS_MEM_FAULT);
        return -1;
    }
    addr &= MEM_MASK;

    caddr = addr;
    while (1) {
        coffset = caddr % PAGE_SIZE;
        csize = size - caddr + addr;
        if (csize > PAGE_SIZE - coffset)
            csize = PAGE_SIZE - coffset;
        if (csize == 0)
            break;
        find_entry(s, caddr, &entry);
        memcpy(s->cache + entry->index * PAGE_SIZE + coffset, src + caddr - addr, csize);
        entry->access = s->ticks;
        entry->flags.written = 1;
        caddr += csize;
    }
    return 0;
}

reg_t get_reg(state_t *s, int reg) {
    if (reg == 0)
        return 0;
    return *((reg_t *)&s->regs + reg);
}

void set_reg(state_t *s, int reg, reg_t val) {
    if (reg == 0)
        return;
    *((reg_t *)&s->regs + reg) = val;
}

/*void debug(state_t *s, instr_t ins) {
    char *regs[] = {
         "$0", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };
    char *type_r[] = {
        "sll", "", "srl", "sra", "sllv", "", "srlv", "srav", "jr", "jalr", "",
        "", "syscall", "break", "", "", "mfhi", "mthi", "mflo", "mtlo", "",
        "", "", "", "mult", "multu", "div", "divu", "", "", "", "", "add",
        "addu", "sub", "subu", "and", "or", "xor", "nor", "", "", "slt", "sltu"
    };
    char *type_ij[] = {
        "", "bltz/bgez", "j", "jal", "beq", "bne", "blez", "bgtz", "addi",
        "addiu", "slti", "sltiu", "andi", "ori", "xori", "lui", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "lb", "lh", "lwl", "lw",
        "lbu", "lhu", "lwr", "", "sb", "sh", "swl", "sw", "", "", "swr"
    };

    char *mnemonic = NULL;
    word_t opcode = ins.as_r.opcode;
    if (opcode == 0x0)
        mnemonic = type_r[ins.as_r.funct];
    else
        mnemonic = type_ij[ins.as_r.opcode];

    printf("\n############################################################\n");
    printf(" $0:%08x    $at:%08x    $v0:%08x    $v1:%08x\n",
           s->regs.zero, s->regs.at, s->regs.v0, s->regs.v1);
    printf("$a0:%08x    $a1:%08x    $a2:%08x    $a3:%08x\n",
           s->regs.a0, s->regs.a1, s->regs.a2, s->regs.a3);
    printf("$t0:%08x    $t1:%08x    $t2:%08x    $t3:%08x\n",
           s->regs.t0, s->regs.t1, s->regs.t2, s->regs.t3);
    printf("$t4:%08x    $t5:%08x    $t6:%08x    $t7:%08x\n",
           s->regs.t4, s->regs.t5, s->regs.t6, s->regs.t7);
    printf("$s0:%08x    $s1:%08x    $s2:%08x    $s3:%08x\n",
           s->regs.s0, s->regs.s1, s->regs.s2, s->regs.s3);
    printf("$s4:%08x    $s5:%08x    $s6:%08x    $s7:%08x\n",
           s->regs.s4, s->regs.s5, s->regs.s6, s->regs.s7);
    printf("$t8:%08x    $t9:%08x    $k0:%08x    $k1:%08x\n",
           s->regs.t8, s->regs.t9, s->regs.k0, s->regs.k1);
    printf("$gp:%08x    $sp:%08x    $fp:%08x    $ra:%08x\n",
           s->regs.gp, s->regs.sp, s->regs.fp, s->regs.ra);
    printf("\n$pc:%08x    $hi:%08x    $lo:%08x\n", s->pc, s->hi, s->lo);

    if (opcode == 0x00)
        printf("opcode:%#x(%s),rs=%s,rt=%s,rd=%s,sa=%d,funct=%#x\n",
               ins.as_r.opcode, mnemonic, regs[ins.as_r.rs], regs[ins.as_r.rt],
               regs[ins.as_r.rd], ins.as_r.sa, ins.as_r.funct);
    else if (opcode == 0x02 || opcode == 0x03)
        printf("opcode:%#x(%s),target=%#x\n", ins.as_j.opcode, mnemonic, ins.as_j.target);
    else
        printf("opcode:%#x(%s),rs=%s,rd=%s,immed=%#x/%i\n", ins.as_i.opcode, mnemonic,
               regs[ins.as_i.rs], regs[ins.as_i.rt], ins.as_i.immed,
               SIGNEXT(16, (sword_t)ins.as_i.immed));
    printf("############################################################\n");
}*/

void tick(state_t *s) {
    if (s->pc >= MEM_SIZE) {
        stop(s, STATUS_BAD_PC);
        return;
    }

    instr_t ins;
    read_mem(s, s->pc, &ins, 4);
    //debug(s, ins);
    //getchar();
    s->pc += 4;
    s->ticks++;

    if (ins.as_r.opcode == 0x00)
        s->by_funct[ins.as_r.funct](s, ins);
    else
        s->by_opcode[ins.as_r.opcode](s, ins);
}

int start(state_t *s) {
    s->ticks = 0;
    s->halted = 0;

    while (!s->halted)
        tick(s);

    switch (s->halted) {
    case STATUS_NO_ERROR:
        break;
    case STATUS_BAD_PC:
        write(1, "Bad instruction pointer.\n", 25);
        break;
    case STATUS_BAD_INS:
        write(1, "Invalid instruction.\n", 21);
        break;
    case STATUS_MEM_FAULT:
        write(1, "Memory fault.\n", 14);
        break;
    default:
        write(1, "Unknown error.\n", 15);
        break;
    }

    return s->halted - 1;
}

void stop(state_t *s, int reason) {
    s->halted = reason;
}

int init_cache(state_t *s) {
    for (int i = 0; i < ENTRY_COUNT; ++i) {
        s->map[i].page = 0;
        s->map[i].flags.present = 0;
        s->map[i].flags.written = 0;
        s->map[i].access = 0;
        s->map[i].index = i;
    }

    s->cache = (byte_t *)malloc(CACHE_SIZE);
    if (s->cache == NULL)
        return -1;
    return 0;
}

int init(state_t **sp) {
    state_t *s;

    s = (state_t *)malloc(sizeof(state_t));
    if (s == NULL)
        return -1;

    s->mem = (byte_t *)malloc(MEM_SIZE);
    if (s->mem == NULL)
        return -1;

    if (init_cache(s))
        return -1;

    s->regs.sp = MEM_SIZE;
    s->regs.fp = MEM_SIZE;
    memcpy(s->mem, memory, memory_len);

    ECRYPT_init();
    ECRYPT_keysetup(&s->ctx, CHACHA_KEY, 256, 64);

    init_handlers(s);

    *sp = s;
    return 0;
}

int main(int argc, char *argv[]) {
    state_t *s;
    if (init(&s))
        return -1;
    return start(s);
}
