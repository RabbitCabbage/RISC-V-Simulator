//
// Created by lu'ren'jia'd's on 2022/6/29.
//

#ifndef UNTITLED4_DEFINE_H
#define UNTITLED4_DEFINE_H

#include "counter.h"
#include <queue>
#include <string>
#include <vector>
#include <map>

unsigned int Current = 0;
struct {
    unsigned int value;
    int rename = 0;//用RS的编号来rename,rename==0说明没有在重命名
} Register[32];
int Memory[500000];
namespace ds {
    enum Type {
        Lui, Auipc, Jal, Jalr, Beq, Bne, Blt, Bge, Bltu, Bgeu,
        Lb, Lh, Lw, Lbu, Lhu, Sb, Sh, Sw, Xori, Ori, Andi, Xor, Or,
        And, Slli, Srai, Srli, Sll, Slt, Sltu, Srl, Sra, Slti, Sltiu,
        Add, Sub, Addi
    };
    struct Operation {
        int rd, rs1, rs2;
        std::string imm;
        Type type;
        bool jump;
        unsigned int pc;
    };
}

Counter counter[10007];
const int Mod = 10007;
int Wrong = 0;
int Correct = 0;
int CLK = 0;
//以下传递的信息分别是《《我预测的是否跳转，pc》，《clk，二进制命令》》
std::queue<std::pair<std::pair<bool,unsigned int>, std::pair<int, std::string>>> InstructionQueue;

struct StationSeat {
    int rs2=0;
    int clk;
    int value1, value2;
    int rename1 = 0, rename2 = 0;
    int destination=0;
    std::string imm;
    unsigned int pc;
    bool jump;
    ds::Type type;
};
std::vector<StationSeat> ReservationStation;
std::vector<StationSeat> StorageStation;
struct BufferSeat {//NOLINT
    bool ready = false;
    int clk;
    int destination;
    ds::Type type;
    //如果说type是涉及到读内存的load还要再issue的时候
    //做相应的操作
    int read_mem_address;
    std::vector<int> value;
    bool jump;
    unsigned int pc;
};

std::map<int, BufferSeat> ReorderBuffer;
bool Halt = false;
#endif //UNTITLED4_DEFINE_H
