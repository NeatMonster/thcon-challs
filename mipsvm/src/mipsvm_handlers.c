#include "libi386.h"

#include "mipsvm.h"
#include "mipsvm_handlers.h"

void no_handler(state_t *s, instr_t ins) {
    stop(s, STATUS_BAD_INS);
}

void handler_addu(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) + get_reg(s, ins.as_r.rt));
}

void handler_addiu(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed));
}

void handler_subu(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) - get_reg(s, ins.as_r.rt));
}

void handler_mult(state_t *s, instr_t ins) {
    int64_t val = (sword_t)get_reg(s, ins.as_r.rs) * (sword_t)get_reg(s, ins.as_r.rt);
    s->lo = val & 0xffffffff;
    s->hi = (val >> 32) & 0xffffffff;
}

void handler_multu(state_t *s, instr_t ins) {
    uint64_t val = get_reg(s, ins.as_r.rs) * get_reg(s, ins.as_r.rt);
    s->lo = val & 0xffffffff;
    s->hi = (val >> 32) & 0xffffffff;
}

void handler_div(state_t *s, instr_t ins) {
    sword_t dvnd = get_reg(s, ins.as_r.rs);
    sword_t dvsr = get_reg(s, ins.as_r.rt);
    s->lo = dvnd / dvsr;
    s->hi = dvnd % dvsr;
}

void handler_divu(state_t *s, instr_t ins) {
    word_t dvnd = get_reg(s, ins.as_r.rs);
    word_t dvsr = get_reg(s, ins.as_r.rt);
    s->lo = dvnd / dvsr;
    s->hi = dvnd % dvsr;
}

void handler_and(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) & get_reg(s, ins.as_r.rt));
}

void handler_andi(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, get_reg(s, ins.as_i.rs) & ins.as_i.immed);
}

void handler_or(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) | get_reg(s, ins.as_r.rt));
}

void handler_ori(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, get_reg(s, ins.as_i.rs) | ins.as_i.immed);
}

void handler_xor(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) ^ get_reg(s, ins.as_r.rt));
}

void handler_xori(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, get_reg(s, ins.as_i.rs) ^ ins.as_i.immed);
}

void handler_nor(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, ~(get_reg(s, ins.as_r.rs) | get_reg(s, ins.as_r.rt)));
}

void handler_sll(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rt) << ins.as_r.sa);
}

void handler_sllv(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rt) << get_reg(s, ins.as_r.rs));
}

void handler_srl(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rt) >> ins.as_r.sa);
}

void handler_srlv(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rt) >> get_reg(s, ins.as_r.rs));
}

void handler_sra(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, (sword_t)get_reg(s, ins.as_r.rt) >> (sword_t)ins.as_r.sa);
}

void handler_srav(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, (sword_t)get_reg(s, ins.as_r.rt) >> (sword_t)get_reg(s, ins.as_r.rs));
}

void handler_lb(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = 0;
    read_mem(s, addr, (byte_t *)&val, 1);
    val = SIGNEXT(8, val);
    set_reg(s, ins.as_i.rt, val);
}

void handler_lbu(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = 0;
    read_mem(s, addr, (byte_t *)&val, 1);
    set_reg(s, ins.as_i.rt, val);
}

void handler_lh(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = 0;
    read_mem(s, addr, (byte_t *)&val, 2);
    val = SIGNEXT(16, val);
    set_reg(s, ins.as_i.rt, val);
}

void handler_lhu(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = 0;
    read_mem(s, addr, (byte_t *)&val, 2);
    set_reg(s, ins.as_i.rt, val);
}

void handler_lw(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = 0;
    read_mem(s, addr, (byte_t *)&val, 4);
    set_reg(s, ins.as_i.rt, val);
}

void handler_lwl(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t vaddr = addr & 3;

    word_t mem_val;
    read_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
    mem_val <<= 8 * (3 - vaddr);

    word_t reg_val = get_reg(s, ins.as_i.rt);
    reg_val &= vaddr != 3 ? 0xffffffff >> (8 * (vaddr + 1)) : 0;

    set_reg(s, ins.as_i.rt, reg_val | mem_val);
}

void handler_lwr(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t vaddr = addr & 3;

    word_t mem_val;
    read_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
    mem_val >>= 8 * vaddr;

    word_t reg_val = get_reg(s, ins.as_i.rt);
    reg_val &= vaddr != 0 ? 0xffffffff << (8 * (4 - vaddr)) : 0;

    set_reg(s, ins.as_i.rt, reg_val | mem_val);
}

void handler_lui(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, ins.as_i.immed);
}

void handler_sb(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = get_reg(s, ins.as_i.rt) & 0xff;
    write_mem(s, addr, (byte_t *)&val, 1);
}

void handler_sh(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = get_reg(s, ins.as_i.rt) & 0xffff;
    write_mem(s, addr, (byte_t *)&val, 2);
}

void handler_sw(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t val = get_reg(s, ins.as_i.rt);
    write_mem(s, addr, (byte_t *)&val, 4);
}

void handler_swl(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t vaddr = addr & 3;

    word_t mem_val;
    read_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
    mem_val &= vaddr != 3 ? 0xffffffff << (8 * (vaddr + 1)) : 0;

    word_t reg_val = get_reg(s, ins.as_i.rt);
    reg_val >>= 8 * (3 - vaddr);

    mem_val |= reg_val;
    write_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
}

void handler_swr(state_t *s, instr_t ins) {
    word_t addr = get_reg(s, ins.as_i.rs) + SIGNEXT(16, ins.as_i.immed);
    word_t vaddr = addr & 3;

    word_t mem_val;
    read_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
    mem_val &= vaddr != 0 ? 0xffffffff >> (8 * (4 - vaddr)) : 0;

    word_t reg_val = get_reg(s, ins.as_i.rt);
    reg_val <<= 8 * vaddr;

    mem_val |= reg_val;
    write_mem(s, addr - vaddr, (byte_t *)&mem_val, 4);
}

void handler_mfhi(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, s->hi);
}

void handler_mflo(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, s->lo);
}

void handler_mthi(state_t *s, instr_t ins) {
    s->hi = get_reg(s, ins.as_r.rs);
}

void handler_mtlo(state_t *s, instr_t ins) {
    s->lo = get_reg(s, ins.as_r.rs);
}

void handler_slt(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, (word_t)get_reg(s, ins.as_r.rs) < (word_t)get_reg(s, ins.as_r.rt) ? 1 : 0);
}

void handler_slti(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, (sword_t)get_reg(s, ins.as_i.rs) < SIGNEXT(16, ins.as_i.immed) ? 1 : 0);
}

void handler_sltu(state_t *s, instr_t ins) {
    set_reg(s, ins.as_r.rd, get_reg(s, ins.as_r.rs) < get_reg(s, ins.as_r.rt) ? 1 : 0);
}

void handler_sltiu(state_t *s, instr_t ins) {
    set_reg(s, ins.as_i.rt, get_reg(s, ins.as_i.rs) < SIGNEXT(16, ins.as_i.immed) ? 1 : 0);
}

void handler_beq(state_t *s, instr_t ins) {
    if (get_reg(s, ins.as_i.rs) == get_reg(s, ins.as_i.rt)) {
        tick(s);
        s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
    }
}

void handler_bne(state_t *s, instr_t ins) {
    if (get_reg(s, ins.as_i.rs) != get_reg(s, ins.as_i.rt)) {
        tick(s);
        s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
    }
}

#define SIGN_BIT 0x80000000

void handler_bgtz(state_t *s, instr_t ins) {
    if (ins.as_i.rt == 0x00) {
        word_t val = get_reg(s, ins.as_i.rs);
        if (val != 0 && !(val & SIGN_BIT)) {
            tick(s);
            s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
        }
    } else
        stop(s, STATUS_BAD_INS);
}

void handler_bltz_bgez(state_t *s, instr_t ins) {
    word_t val = get_reg(s, ins.as_i.rs);
    if (ins.as_i.rt == 0x00) {
        if (val & SIGN_BIT) {
            tick(s);
            s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
        }
    } else if (ins.as_i.rt == 0x01) {
        if (!(val & SIGN_BIT)) {
            tick(s);
            s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
        }
    } else
        stop(s, STATUS_BAD_INS);
}

void handler_blez(state_t *s, instr_t ins) {
    if (ins.as_i.rt == 0x00) {
        word_t val = get_reg(s, ins.as_i.rs);
        if (val == 0 || val & SIGN_BIT) {
            tick(s);
            s->pc += SIGNEXT(18, ins.as_i.immed << 2) - 4;
        }
    } else
        stop(s, STATUS_BAD_INS);
}

void handler_j(state_t *s, instr_t ins) {
    tick(s);
    s->pc = (s->pc & 0xf0000000) | (ins.as_j.target << 2);
}

void handler_jr(state_t *s, instr_t ins) {
    tick(s);
    s->pc = get_reg(s, ins.as_r.rs);
}

void handler_jal(state_t *s, instr_t ins) {
    tick(s);
    s->regs.ra = s->pc;
    s->pc = (s->pc & 0xf0000000) | (ins.as_j.target << 2);
}

void handler_jalr(state_t *s, instr_t ins) {
    tick(s);
    s->regs.ra = s->pc;
    s->pc = get_reg(s, ins.as_r.rs);
}

void handler_syscall(state_t *s, instr_t ins) {
    word_t ret, code = s->regs.v0;
    sword_t fd, offset, size, path, flags, mode;
    byte_t *buf = NULL;
    switch (code) {
    case SYSCALL_EXIT:
        stop(s, STATUS_NO_ERROR);
        break;
    case SYSCALL_READ:
        fd = s->regs.a0;
        offset = s->regs.a1;
        size = s->regs.a2;

        buf = malloc(size);
        ret = read(fd, buf, size);
        write_mem(s, offset, buf, size);
        free(buf);

        s->regs.a0 = ret;
        break;
    case SYSCALL_WRITE:
        fd = s->regs.a0;
        offset = s->regs.a1;
        size = s->regs.a2;

        buf = malloc(size);
        read_mem(s, offset, buf, size);
        ret = write(fd, buf, size);
        free(buf);

        s->regs.a0 = ret;
        break;
    case SYSCALL_OPEN:
        path = s->regs.a0;
        flags = s->regs.a1;
        mode = s->regs.a2;

        size = 0;
        do {
            read_mem(s, path + size++, (byte_t *)&code, 1);
        } while (code != '\0');
        buf = malloc(size);
        read_mem(s, path, buf, size);
        ret = open((char *)buf, flags, mode);
        free(buf);

        s->regs.a0 = ret;
        break;
    case SYSCALL_CLOSE:
        fd = s->regs.a0;
        ret = close(fd);
        s->regs.a0 = ret;
        break;
    default:
        stop(s, STATUS_BAD_INS);
        break;
    }
}

void handler_break(state_t *s, instr_t ins) {
    //debug(s, ins);
}

void init_handlers(state_t *s) {
    for (int i = 0; i < 0x40; ++i) {
        s->by_funct[i] = no_handler;
        s->by_opcode[i] = no_handler;
    }

    s->by_funct[FUNCT_ADDU] = handler_addu;
    s->by_funct[FUNCT_AND] = handler_and;
    s->by_funct[FUNCT_BREAK] = handler_break;
    s->by_funct[FUNCT_DIV] = handler_div;
    s->by_funct[FUNCT_DIVU] = handler_divu;
    s->by_funct[FUNCT_JALR] = handler_jalr;
    s->by_funct[FUNCT_JR] = handler_jr;
    s->by_funct[FUNCT_MFHI] = handler_mfhi;
    s->by_funct[FUNCT_MFLO] = handler_mflo;
    s->by_funct[FUNCT_MTHI] = handler_mthi;
    s->by_funct[FUNCT_MTLO] = handler_mtlo;
    s->by_funct[FUNCT_MULT] = handler_mult;
    s->by_funct[FUNCT_MULTU] = handler_multu;
    s->by_funct[FUNCT_NOR] = handler_nor;
    s->by_funct[FUNCT_OR] = handler_or;
    s->by_funct[FUNCT_SLL] = handler_sll;
    s->by_funct[FUNCT_SLLV] = handler_sllv;
    s->by_funct[FUNCT_SLT] = handler_slt;
    s->by_funct[FUNCT_SLTU] = handler_sltu;
    s->by_funct[FUNCT_SRA] = handler_sra;
    s->by_funct[FUNCT_SRAV] = handler_srav;
    s->by_funct[FUNCT_SRL] = handler_srl;
    s->by_funct[FUNCT_SRLV] = handler_srlv;
    s->by_funct[FUNCT_SUBU] = handler_subu;
    s->by_funct[FUNCT_SYSCALL] = handler_syscall;
    s->by_funct[FUNCT_XOR] = handler_xor;

    s->by_opcode[OPCODE_ADDIU] = handler_addiu;
    s->by_opcode[OPCODE_ANDI] = handler_andi;
    s->by_opcode[OPCODE_BEQ] = handler_beq;
    s->by_opcode[OPCODE_BGTZ] = handler_bgtz;
    s->by_opcode[OPCODE_BLEZ] = handler_blez;
    s->by_opcode[OPCODE_BLTZ_BGEZ] = handler_bltz_bgez;
    s->by_opcode[OPCODE_BNE] = handler_bne;
    s->by_opcode[OPCODE_J] = handler_j;
    s->by_opcode[OPCODE_JAL] = handler_jal;
    s->by_opcode[OPCODE_LB] = handler_lb;
    s->by_opcode[OPCODE_LBU] = handler_lbu;
    s->by_opcode[OPCODE_LH] = handler_lh;
    s->by_opcode[OPCODE_LHU] = handler_lhu;
    s->by_opcode[OPCODE_LUI] = handler_lui;
    s->by_opcode[OPCODE_LW] = handler_lw;
    s->by_opcode[OPCODE_LWL] = handler_lwl;
    s->by_opcode[OPCODE_LWR] = handler_lwr;
    s->by_opcode[OPCODE_ORI] = handler_ori;
    s->by_opcode[OPCODE_SB] = handler_sb;
    s->by_opcode[OPCODE_SH] = handler_sh;
    s->by_opcode[OPCODE_SLTI] = handler_slti;
    s->by_opcode[OPCODE_SLTIU] = handler_sltiu;
    s->by_opcode[OPCODE_SW] = handler_sw;
    s->by_opcode[OPCODE_SWL] = handler_swl;
    s->by_opcode[OPCODE_SWR] = handler_swr;
    s->by_opcode[OPCODE_XORI] = handler_xori;
}
