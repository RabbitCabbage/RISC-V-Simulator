//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#ifndef UNTITLED4_COMMAND_H
#define UNTITLED4_COMMAND_H

#include <string>
#include "tool.h"
#include "decode.h"
#include <iostream>
#include "define.h"
#include "execute.h"
#include "counter.h"

void ReadCommand() {
    char x;
    int addr;
    while (std::cin >> x) {
        if (x == '@') {
            std::string address;
            address.clear();
            for (int i = 0; i < 8; ++i) {
                std::cin >> x;
                address += x;
            }
            addr = Hex_Decimal(address);
        } else if (x == ' ')continue;
        else if (x == '#')break;
        else {
            std::string section;//指令的片段，是一个十六进制数字
            section += x;
            std::cin >> x;
            section += x;
            Memory[addr++] = Hex_Decimal(section);
        }
    }
}

void IF() {
    if (Halt)return;
    std::string command;
    command.clear();
    for (int i = 3; i >= 0; --i) {
        std::string part = Decimal_Hex(Memory[Current + i]);
        if (part.length() == 1)part = '0' + part;
        command += part;
    }
    //std::cout << "IF " << command << std::endl;
    if (command == "0FF00513") {
        //std::cout << "HERE" << std::endl;
        Halt = true;
        return;//halt指令就不放进去了，并且halt之后新的指令也不读进来了
    }
    Current += 4;//每一次读完之后的current已经被放到了下一个位置
    std::string dir = Hex_Binary(command);
    int pc = Hex_Decimal(command);
    std::string com = dir.substr(25, 7);
    if (com == "1100011") {
        bool jump = counter[pc % Mod].Query();
        if (jump) {
            std::string imm = dir.substr(0, 1) + dir.substr(24, 1) + dir.substr(1, 6) + dir.substr(20, 4) + "0";
            Current += Decode(imm) - 4;
            ReadReg.push({dir, {true, pc}});
        } else ReadReg.push({dir, {false, pc}});
    } else ReadReg.push({dir, {false, pc}});
}

void ID() {
    if (ReadReg.empty())return;//队列空了就不用执行了
    Register[0] = 0;
    auto dir_pair = ReadReg.front();
    std::string dir = dir_pair.first;
    ReadReg.pop();
    //std::cout << "ID ";
    std::string com = dir.substr(25, 7);
    if (com == "0110111")LuiDecode(dir);
    else if (com == "0010111")AuipcDecode(dir);
    else if (com == "1101111")JalDecode(dir);
    else if (com == "1100111")JalrDecode(dir);
    else if (com == "1100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")BeqDecode(dir_pair);
        else if (f3 == "001")BneDecode(dir_pair);
        else if (f3 == "100")BltDecode(dir_pair);
        else if (f3 == "101")BgeDecode(dir_pair);
        else if (f3 == "110")BltuDecode(dir_pair);
        else if (f3 == "111")BgeuDecode(dir_pair);
    } else if (com == "0000011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")LbDecode(dir);
        else if (f3 == "001")LhDecode(dir);
        else if (f3 == "010")LwDecode(dir);
        else if (f3 == "100")LbuDecode(dir);
        else if (f3 == "101")LhuDecode(dir);
    } else if (com == "0100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000") SbDecode(dir);
        else if (f3 == "001")ShDecode(dir);
        else if (f3 == "010")SwDecode(dir);
    } else if (com == "0010011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")AddiDecode(dir);
        else if (f3 == "010")SltiDecode(dir);
        else if (f3 == "011")SltiuDecode(dir);
        else if (f3 == "001")SlliDecode(dir);
        else if (f3 == "100")XoriDecode(dir);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")SrliDecode(dir);
            else SraiDecode(dir);
        } else if (f3 == "110")OriDecode(dir);
        else if (f3 == "111")AndiDecode(dir);
    } else if (com == "0110011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")AddDecode(dir);
            else SubDecode(dir);
        } else if (f3 == "001")SllDecode(dir);
        else if (f3 == "010")SltDecode(dir);
        else if (f3 == "011")SltuDecode(dir);
        else if (f3 == "100")XorDecode(dir);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")SrlDecode(dir);
            else SraDecode(dir);
        } else if (f3 == "110")OrDecode(dir);
        else if (f3 == "111")AndDecode(dir);
    }
}

void EX() {
    if (Execute.empty())return;
    ds::Operation opt = Execute.front();
    Execute.pop();
    //std::cout << "EX ";
    switch (opt.type) {
        case ds::Lui:
            Lui(opt);
            break;
        case ds::Auipc:
            Auipc(opt);
            break;
        case ds::Jal:
            Jal(opt);
            break;
        case ds::Jalr:
            Jalr(opt);
            break;
        case ds::Beq:
            Beq(opt);
            break;
        case ds::Bne:
            Bne(opt);
            break;
        case ds::Blt:
            Blt(opt);
            break;
        case ds::Bge:
            Bge(opt);
            break;
        case ds::Bltu:
            Bltu(opt);
            break;
        case ds::Bgeu:
            Bgeu(opt);
            break;
        case ds::Lb:
            Lb(opt);
            break;
        case ds::Lh:
            Lh(opt);
            break;
        case ds::Lw:
            Lw(opt);
            break;
        case ds::Lbu:
            Lbu(opt);
            break;
        case ds::Lhu:
            Lhu(opt);
            break;
        case ds::Sb:
            Sb(opt);
            break;
        case ds::Sh:
            Sh(opt);
            break;
        case ds::Sw:
            Sw(opt);
            break;
        case ds::Xori:
            Xori(opt);
            break;
        case ds::Ori:
            Ori(opt);
            break;
        case ds::Andi:
            Andi(opt);
            break;
        case ds::Xor:
            Xor(opt);
            break;
        case ds::Or:
            Or(opt);
            break;
        case ds::And:
            And(opt);
            break;
        case ds::Slli:
            Slli(opt);
            break;
        case ds::Srai:
            Srai(opt);
            break;
        case ds::Srli:
            Srli(opt);
            break;
        case ds::Sll:
            Sll(opt);
            break;
        case ds::Slt:
            Slt(opt);
            break;
        case ds::Sltu:
            Sltu(opt);
            break;
        case ds::Srl:
            Srl(opt);
            break;
        case ds::Sra:
            Sra(opt);
            break;
        case ds::Slti:
            Slti(opt);
            break;
        case ds::Sltiu:
            Sltiu(opt);
            break;
        case ds::Add:
            Add(opt);
            break;
        case ds::Sub:
            Sub(opt);
            break;
        case ds::Addi:
            Addi(opt);
            break;
    }
}

void MEM() {
    if (WriteMem.empty())return;
    auto directive = WriteMem.front();
    for (int i = 0; i < directive.first; ++i) {
        auto command = WriteMem.front();
        WriteMem.pop();
        Memory[command.second.first] = command.second.second;
    }
    //std::cout << "MEM " << " 131068 " << Memory[131068] << std::endl;
}

void WB() {
    if (WriteReg.empty())return;
    auto command = WriteReg.front();
    WriteReg.pop();
    Register[command.first] = command.second;
    //std::cout << "WB " << command.first << " " << command.second << std::endl;
}

#endif //UNTITLED4_COMMAND_H
