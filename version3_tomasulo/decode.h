//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#ifndef UNTITLED4_DECODE_H
#define UNTITLED4_DECODE_H

#include "tool.h"
#include <iostream>
#include <string>
#include "define.h"

std::pair<int, ds::Operation>
LuiDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    std::string imm;
    int rd;
    U_Type(ins.second.second, imm, rd);
    ds::Operation lui;
    lui.rd = rd;
    lui.pc = ins.first.second;
    lui.imm = imm;
    lui.type = ds::Lui;
    //std::cout << "lui " << rd << " " << imm << std::endl;
    return {ins.second.first, lui};
}

std::pair<int, ds::Operation>
AuipcDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    std::string imm;
    int rd;
    U_Type(ins.second.second, imm, rd);
    ds::Operation auipc;
    auipc.rd = rd;
    auipc.pc = ins.first.second;
    auipc.imm = imm;
    auipc.type = ds::Auipc;
    //std::cout << "auipc " << rd << " " << imm << std::endl;
    return {ins.second.first, auipc};
}

std::pair<int, ds::Operation>
JalDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    std::string imm;
    int rd;
    J_Type(ins.second.second, imm, rd);
    ds::Operation jal;
    jal.rd = rd;
    jal.pc = ins.first.second;
    jal.imm = imm;
    jal.type = ds::Jal;
    //std::cout << "jal " << rd << " " << imm << std::endl;
    return {ins.second.first, jal};
}

std::pair<int, ds::Operation>
JalrDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation jalr;
    jalr.imm = imm;
    jalr.rs1 = rs1;
    jalr.pc = ins.first.second;
    jalr.rd = rd;
    jalr.imm = imm;
    jalr.type = ds::Jalr;
    //std::cout << "jalr " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, jalr};
}

std::pair<int, ds::Operation>
BeqDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation beq;
    beq.imm = imm;
    beq.rs1 = rs1;
    beq.pc = ins.first.second;
    beq.rs2 = rs2;
    beq.type = ds::Beq;
    beq.jump = ins.first.first;
    //std::cout << "beq " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, beq};
}

std::pair<int, ds::Operation>
BneDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation bne;
    bne.imm = imm;
    bne.rs1 = rs1;
    bne.pc = ins.first.second;
    bne.rs2 = rs2;
    bne.type = ds::Bne;
    bne.jump = ins.first.first;
    //std::cout << "bne " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, bne};
}

std::pair<int, ds::Operation>
BltDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation blt;
    blt.imm = imm;
    blt.rs1 = rs1;
    blt.pc = ins.first.second;
    blt.rs2 = rs2;
    blt.type = ds::Blt;
    blt.jump = ins.first.first;
    //std::cout << "blt " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, blt};
}

std::pair<int, ds::Operation>
BgeDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation bge;
    bge.imm = imm;
    bge.rs1 = rs1;
    bge.pc = ins.first.second;
    bge.rs2 = rs2;
    bge.type = ds::Bge;
    bge.jump = ins.first.first;
    //std::cout << "bge " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, bge};
}

std::pair<int, ds::Operation>
BltuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation bltu;
    bltu.imm = imm;
    bltu.rs1 = rs1;
    bltu.pc = ins.first.second;
    bltu.rs2 = rs2;
    bltu.type = ds::Bltu;
    bltu.jump = ins.first.first;
    //std::cout << "bltu " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, bltu};
}

std::pair<int, ds::Operation>
BgeuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs2, rs1;
    std::string imm;
    B_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation bgeu;
    bgeu.imm = imm;
    bgeu.rs1 = rs1;
    bgeu.pc = ins.first.second;
    bgeu.rs2 = rs2;
    bgeu.type = ds::Bgeu;
    bgeu.jump = ins.first.first;
    //std::cout << "bgeu " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, bgeu};
}

std::pair<int, ds::Operation>
LbDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation lb;
    lb.imm = imm;
    lb.rd = rd;
    lb.rs1 = rs1;
    lb.pc = ins.first.second;
    lb.type = ds::Lb;
    //std::cout << "lb " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, lb};
}

std::pair<int, ds::Operation>
LhDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation lh;
    lh.imm = imm;
    lh.rd = rd;
    lh.rs1 = rs1;
    lh.pc = ins.first.second;
    lh.type = ds::Lh;
    //std::cout << "lh " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, lh};
}

std::pair<int, ds::Operation>
LwDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation lw;
    lw.imm = imm;
    lw.rd = rd;
    lw.rs1 = rs1;
    lw.pc = ins.first.second;
    lw.type = ds::Lw;
    //std::cout << "lw " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, lw};
}

std::pair<int, ds::Operation>
LbuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation lbu;
    lbu.imm = imm;
    lbu.rd = rd;
    lbu.rs1 = rs1;
    lbu.pc = ins.first.second;
    lbu.type = ds::Lbu;
    //std::cout << "lbu " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, lbu};
}

std::pair<int, ds::Operation>
LhuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation lhu;
    lhu.imm = imm;
    lhu.rd = rd;
    lhu.rs1 = rs1;
    lhu.pc = ins.first.second;
    lhu.type = ds::Lhu;
    //std::cout << "lhu " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, lhu};
}

std::pair<int, ds::Operation>
SbDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs1, rs2;
    std::string imm;
    S_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation sb;
    sb.imm = imm;
    sb.rs1 = rs1;
    sb.pc = ins.first.second;
    sb.rs2 = rs2;
    sb.type = ds::Sb;
    //std::cout << "sb " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, sb};
}

std::pair<int, ds::Operation>
ShDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs1, rs2;
    std::string imm;
    S_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation sh;
    sh.imm = imm;
    sh.rs1 = rs1;
    sh.pc = ins.first.second;
    sh.rs2 = rs2;
    sh.type = ds::Sh;
    //std::cout << "sh " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, sh};
}

std::pair<int, ds::Operation>
SwDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rs1, rs2;
    std::string imm;
    S_Type(ins.second.second, imm, rs1, rs2);
    ds::Operation sw;
    sw.imm = imm;
    sw.rs1 = rs1;
    sw.pc = ins.first.second;
    sw.rs2 = rs2;
    sw.type = ds::Sw;
    //std::cout << "sw " << rs1 << " " << rs2 << " " << imm << std::endl;
    return {ins.second.first, sw};
}

std::pair<int, ds::Operation>
XoriDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation xori;
    xori.imm = imm;
    xori.type = ds::Xori;
    xori.rd = rd;
    xori.rs1 = rs1;
    xori.pc = ins.first.second;
    //std::cout << "xori " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, xori};
}

std::pair<int, ds::Operation>
OriDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation ori;
    ori.imm = imm;
    ori.type = ds::Ori;
    ori.rd = rd;
    ori.rs1 = rs1;
    ori.pc = ins.first.second;
    //std::cout << "ori " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, ori};
}

std::pair<int, ds::Operation>
AndiDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation addi;
    addi.imm = imm;
    addi.type = ds::Andi;
    addi.rd = rd;
    addi.rs1 = rs1;
    addi.pc = ins.first.second;
    //std::cout << "andi " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, addi};
}

std::pair<int, ds::Operation>
XorDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation xor_;
    xor_.rd = rd;
    xor_.rs1 = rs1;
    xor_.pc = ins.first.second;
    xor_.rs2 = rs2;
    xor_.type = ds::Xor;
    //std::cout << "xor " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, xor_};
}

std::pair<int, ds::Operation>
OrDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation or_;
    or_.rd = rd;
    or_.rs1 = rs1;
    or_.pc = ins.first.second;
    or_.rs2 = rs2;
    or_.type = ds::Or;
    //std::cout << "or " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, or_};
}

std::pair<int, ds::Operation>
AndDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation and_;
    and_.rd = rd;
    and_.rs1 = rs1;
    and_.pc = ins.first.second;
    and_.rs2 = rs2;
    and_.type = ds::And;
    //std::cout << "and " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, and_};
}

std::pair<int, ds::Operation>
SlliDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation slli;
    slli.rd = rd;
    slli.rs1 = rs1;
    slli.pc = ins.first.second;
    slli.rs2 = rs2;
    slli.rs2 = rs2;
    slli.type = ds::Slli;
    //std::cout << "slli " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, slli};
}

std::pair<int, ds::Operation>
SrliDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation srli;
    srli.rd = rd;
    srli.rs1 = rs1;
    srli.pc = ins.first.second;
    srli.rs2 = rs2;
    srli.rs2 = rs2;
    srli.type = ds::Srli;
    //std::cout << "srli " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, srli};
}

std::pair<int, ds::Operation>
SraiDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation srai;
    srai.rd = rd;
    srai.rs1 = rs1;
    srai.pc = ins.first.second;
    srai.rs2 = rs2;
    srai.rs2 = rs2;
    srai.type = ds::Srai;
    //std::cout << "srai " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, srai};
}

std::pair<int, ds::Operation>
SllDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation sll;
    sll.rd = rd;
    sll.rs1 = rs1;
    sll.pc = ins.first.second;
    sll.rs2 = rs2;
    sll.type = ds::Sll;
    //std::cout << "sll " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, sll};
}

std::pair<int, ds::Operation>
SltDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation slt;
    slt.rd = rd;
    slt.rs1 = rs1;
    slt.pc = ins.first.second;
    slt.rs2 = rs2;
    slt.type = ds::Slt;
    //std::cout << "slt " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, slt};
}

std::pair<int, ds::Operation>
SltuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation sltu;
    sltu.rd = rd;
    sltu.rs1 = rs1;
    sltu.pc = ins.first.second;
    sltu.rs2 = rs2;
    sltu.type = ds::Sltu;
    //std::cout << "sltu " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, sltu};
}

std::pair<int, ds::Operation>
SrlDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation srl;
    srl.rd = rd;
    srl.rs1 = rs1;
    srl.pc = ins.first.second;
    srl.rs2 = rs2;
    srl.type = ds::Srl;
    //std::cout << "srl " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, srl};
}

std::pair<int, ds::Operation>
SraDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation sra;
    sra.rd = rd;
    sra.rs1 = rs1;
    sra.pc = ins.first.second;
    sra.rs2 = rs2;
    sra.type = ds::Sra;
    //std::cout << "sra " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, sra};
}

std::pair<int, ds::Operation>
SltiDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation slti;
    slti.type = ds::Slti;
    slti.imm = imm;
    slti.rs1 = rs1;
    slti.pc = ins.first.second;
    slti.rd = rd;
    //std::cout << "slti " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, slti};
}

std::pair<int, ds::Operation>
SltiuDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation sltiu;
    sltiu.type = ds::Sltiu;
    sltiu.imm = imm;
    sltiu.rs1 = rs1;
    sltiu.pc = ins.first.second;
    sltiu.rd = rd;
    //std::cout << "sltiu " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, sltiu};
}

std::pair<int, ds::Operation>
AddDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation add;
    add.rd = rd;
    add.rs1 = rs1;
    add.pc = ins.first.second;
    add.rs2 = rs2;
    add.type = ds::Add;
    //std::cout << "add " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, add};
}

std::pair<int, ds::Operation>
SubDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1, rs2;
    R_Type(ins.second.second, rs2, rs1, rd);
    ds::Operation sub;
    sub.rd = rd;
    sub.rs1 = rs1;
    sub.pc = ins.first.second;
    sub.rs2 = rs2;
    sub.type = ds::Sub;
    //std::cout << "sub " << rd << " " << rs1 << " " << rs2 << std::endl;
    return {ins.second.first, sub};
}

std::pair<int, ds::Operation>
AddiDecode(const std::pair<std::pair<bool, unsigned int>, std::pair<int, std::string>> &ins) {
    int rd, rs1;
    std::string imm;
    I_Type(ins.second.second, imm, rs1, rd);
    ds::Operation addi;
    addi.type = ds::Addi;
    addi.imm = imm;
    addi.rs1 = rs1;
    addi.pc = ins.first.second;
    addi.rd = rd;
    //std::cout << "addi " << rd << " " << rs1 << " " << imm << std::endl;
    return {ins.second.first, addi};
}

#endif //UNTITLED4_DECODE_H
