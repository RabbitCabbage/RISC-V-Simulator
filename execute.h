//
// Created by lu'ren'jia'd's on 2022/6/30.
//

#ifndef UNTITLED4_EXECUTE_H
#define UNTITLED4_EXECUTE_H

#include "define.h"

void Lui(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.value.push_back(Decode(seat.imm + "000000000000"));
      //std::cout << "lui  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Auipc(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.value.push_back(Decode(seat.imm + "000000000000") + Current - 4);
      //std::cout << "auipc  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Jal(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(seat.pc + 4);
    torob.value.push_back(Decode(seat.imm));
    //    Register[torob.destination].value = Current - 4 * (int) ReadReg.size();
//      //std::cout << Register[torob.destination].value << std::endl;
    //Current += Decode(seat.imm) - 4;
    //在rob中执行跳转指令的时候再清空原本的指令
      //std::cout << "jal  " << Register[torob.destination].value << "\t" << Current << std::endl;
}

void Jalr(const StationSeat &seat) {
    std::string cur = Decimal_Binary32(Decode(seat.imm) + seat.value1);
    cur[31] = '0';
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(seat.pc + 4);
//      //std::cout << Register[torob.destination].value << std::endl;
    torob.value.push_back(Binary_Decimal(cur));
    //在rob中执行跳转指令的时候再清空原本的指令
      //std::cout << "jalr  " << Register[torob.destination].value << "\t" << Current << std::endl;
}

void Beq(const StationSeat &seat) {
      //std::cout << "beq  " << seat.value1 << "\t" << seat.value2 << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (seat.value1 == seat.value2)torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Bne(const StationSeat &seat) {
      //std::cout << "bne  " << seat.value1 << "\t" << seat.value2 << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (seat.value1 != seat.value2)torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Blt(const StationSeat &seat) {
      //std::cout << "blt  " << seat.value1 << "\t" << seat.value2 << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (seat.value1 < seat.value2)torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Bge(const StationSeat &seat) {
      //std::cout << "bge  " << seat.value1 << "\t" << seat.value2 << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (seat.value1 >= seat.value2)torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Bltu(const StationSeat &seat) {
      //std::cout << "bltu  " << ((unsigned) seat.value1) << "\t" << ((unsigned) seat.value2) << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (((unsigned) seat.value1) < ((unsigned) seat.value2))torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Bgeu(const StationSeat &seat) {
      //std::cout << "bgeu  " << ((unsigned) seat.value1) << "\t" << ((unsigned) seat.value2) << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.jump = seat.jump;
    if (((unsigned) seat.value1) >= ((unsigned) seat.value2))torob.value.push_back(1);
    else torob.value.push_back(0);
    torob.value.push_back(Decode(seat.imm));
}

void Lb(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.read_mem_address = seat.value1 + Decode(seat.imm);
    //这里还不能读内存的，可能没有更新
    //这个内存的读放到rob里面保证，只有这一个需要特判
      //std::cout << "lb  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Lh(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.read_mem_address = seat.value1 + Decode(seat.imm);
    //todo 这里还不能读内存的，可能没有更新
    //todo 这个内存的读放到rob里面保证，只有这一个需要特判
      //std::cout << "lh  " << torob.destination << " " << torob.value[0] << std::endl;
}

void Lw(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.read_mem_address = seat.value1 + Decode(seat.imm);
    //todo 这里还不能读内存的，可能没有更新
    //todo 这个内存的读放到rob里面保证，只有这一个需要特判
      //std::cout << "lw  " << torob.destination << " " << std::endl;
//<< torob.value[0] << std::endl;
}

void Lbu(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.read_mem_address = seat.value1 + Decode(seat.imm);
    //todo 这里还不能读内存的，可能没有更新
    //todo 这个内存的读放到rob里面保证，只有这一个需要特判
      //std::cout << "lbu  " << torob.destination << " " << std::endl;
//<< torob.value[0] << std::endl;
}

void Lhu(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.clk = seat.clk;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.destination = seat.destination;
    torob.read_mem_address = seat.value1 + Decode(seat.imm);
    //todo 这里还不能读内存的，可能没有更新
    //todo 这个内存的读放到rob里面保证，只有这一个需要特判
      //std::cout << "lhu  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sb(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.value1 + Decode(seat.imm);
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    std::string b_number32 = Decimal_Binary32(seat.value2);
    torob.value.push_back(Binary_Decimal(b_number32.substr(24, 8)));
      //std::cout << "sb  " << torob.destination << "\t" << Decimal_Binary32(seat.value2) << std::endl;
}

void Sh(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.value1 + Decode(seat.imm);
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    std::string b_number32 = Decimal_Binary32(seat.value2);
    torob.value.push_back(Binary_Decimal(b_number32.substr(24, 8)));
    torob.value.push_back(Binary_Decimal(b_number32.substr(16, 8)));
      //std::cout << "sh  " << torob.destination << "\t" << Decimal_Binary32(seat.value2) << std::endl;
}

void Sw(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.value1 + Decode(seat.imm);
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    std::string b_number32 = Decimal_Binary32(seat.value2);
    torob.value.push_back(Binary_Decimal(b_number32.substr(24, 8)));
    torob.value.push_back(Binary_Decimal(b_number32.substr(16, 8)));
    torob.value.push_back(Binary_Decimal(b_number32.substr(8, 8)));
    torob.value.push_back(Binary_Decimal(b_number32.substr(0, 8)));
      //std::cout << "sw  " << torob.destination << "\t" << Decimal_Binary32(seat.value2) << std::endl;
}

void Xori(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 ^ Decode(seat.imm));
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "xori  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Ori(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 | Decode(seat.imm));
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "ori  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Andi(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 & Decode(seat.imm));
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "andi  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Xor(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 ^ seat.value2);
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "xor  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Or(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 | seat.value2);
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "or  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void And(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 & seat.value2);
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "and  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Slli(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((unsigned) seat.value1) << seat.rs2);
      //std::cout << "slli  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Srli(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((unsigned) seat.value1) >> seat.rs2);
      //std::cout << "srli  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Srai(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((int) seat.value1) >> seat.rs2);
      //std::cout << "srai  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sll(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((unsigned) seat.value1) << move);
      //std::cout << "sll  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Slt(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    if (seat.value1 < seat.value2)torob.value.push_back(1);
    else torob.value.push_back(0);
      //std::cout << "slt  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sltu(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    if (((unsigned) seat.value1) < ((unsigned) seat.value2))torob.value.push_back(1);
    else torob.value.push_back(0);
      //std::cout << "sltu  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Srl(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((unsigned) seat.value1) >> move);
      //std::cout << "srl  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sra(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(((int) seat.value1) >> move);
      //std::cout << "sra  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Slti(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    if (seat.value1 < Decode(seat.imm))torob.value.push_back(1);
    else torob.value.push_back(0);
      //std::cout << "slti  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sltiu(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    if (((unsigned) seat.value1) < ((unsigned) Decode(seat.imm)))torob.value.push_back(1);
    else torob.value.push_back(0);
      //std::cout << "sltiu  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Add(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(seat.value1 + seat.value2);
      //std::cout << "add  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Sub(const StationSeat &seat) {
    int move = Binary_Decimal(Decimal_Binary5(seat.value2));
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
    torob.value.push_back(seat.value1 - seat.value2);
      //std::cout << "sub  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

void Addi(const StationSeat &seat) {
    BufferSeat &torob = ReorderBuffer.find(seat.clk)->second;
    torob.value.push_back(seat.value1 + Decode(seat.imm));
    torob.destination = seat.destination;
    torob.type = seat.type;
    torob.pc = seat.pc;
    torob.ready = true;
    torob.clk = seat.clk;
      //std::cout << "addi  " << torob.destination << "\t" << torob.value[0] << std::endl;
}

#endif //UNTITLED4_EXECUTE_H
