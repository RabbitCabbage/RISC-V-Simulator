//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#ifndef UNTITLED4_DEFINE_H
#define UNTITLED4_DEFINE_H

#include <vector>
#include "counter.h"

int Current = 0;
int Register[32];
int Memory[500000];
namespace ds {
    enum Type {
        Lui, Auipc, Jal, Jalr, Beq, Bne, Blt, Bge, Bltu, Bgeu,
        Lb, Lh, Lw, Lbu, Lhu, Sb, Sh, Sw, Xori, Ori, Andi, Xor, Or,
        And, Slli, Srai, Srli, Sll, Slt, Sltu, Srl, Sra, Slti, Sltiu,
        Add, Sub, Addi
    };
    struct Operation {
        int rd = 0, rs1_number = 0, rs2_number = 0;
        int rs2 = 0;
        std::string imm;
        Type type;
        bool jump;
        int pc;
    };
}
std::queue<std::pair<std::string, std::pair<bool, int>>> ReadReg;
std::queue<ds::Operation> Execute;
std::queue<std::pair<int, int>> WriteReg;
std::queue<std::pair<int, std::pair<int, int>>> WriteMem;
std::vector<int> MemUpdate;
int Address, Bytes;
int RegUpdate = 0, Number = 0;
bool Halt = false;

Counter counter[10007];
const int Mod = 10007;
int Wrong = 0;
int Correct = 0;
#endif //UNTITLED4_DEFINE_H
