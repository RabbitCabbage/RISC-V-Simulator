//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#ifndef UNTITLED4_DECODE_H
#define UNTITLED4_DECODE_H

#include "tool.h"
#include <iostream>
#include <string>
#include "define.h"

int ReadUpdatedReg(int number) {
    if (number == Number)return RegUpdate;
    else return Register[number];
}

void LuiDecode(const std::string &dir) {
    std::string imm;
    int rd;
    U_Type(dir, imm, rd);
    ds::Operation lui;
    lui.rd = rd;
    lui.imm = imm;
    lui.type = ds::Lui;
    Execute.push(lui);
    //std::cout << "lui " << rd << " " << imm << std::endl;
}

void AuipcDecode(const std::string &dir) {
    std::string imm;
    int rd;
    U_Type(dir, imm, rd);
    ds::Operation auipc;
    auipc.rd = rd;
    auipc.imm = imm;
    auipc.type = ds::Auipc;
    Execute.push(auipc);
    //std::cout << "auipc " << rd << " " << imm << std::endl;
}

void JalDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    std::string imm;
    int rd;
    J_Type(dir, imm, rd);
    ds::Operation jal;
    jal.rd = rd;
    jal.imm = imm;
    jal.type = ds::Jal;
    jal.pc = dir_pair.second.second;
    Execute.push(jal);
    //std::cout << "jal " << rd << " " << imm << std::endl;
}

void JalrDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation jalr;
    jalr.imm = imm;
    jalr.rs1_number = ReadUpdatedReg(rs1);
    jalr.rd = rd;
    jalr.imm = imm;
    jalr.type = ds::Jalr;
    jalr.pc = dir_pair.second.second;
    Execute.push(jalr);
    //std::cout << "jalr " << rd << " " << rs1 << " " << imm << std::endl;
}

void BeqDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation beq;
    beq.imm = imm;
    beq.rs1_number = ReadUpdatedReg(rs1);
    beq.rs2_number = ReadUpdatedReg(rs2);
    beq.type = ds::Beq;
    beq.jump = dir_pair.second.first;
    beq.pc = dir_pair.second.second;
    Execute.push(beq);
    //std::cout << "beq " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void BneDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation bne;
    bne.imm = imm;
    bne.rs1_number = ReadUpdatedReg(rs1);
    bne.rs2_number = ReadUpdatedReg(rs2);
    bne.type = ds::Bne;
    bne.jump = dir_pair.second.first;
    bne.pc = dir_pair.second.second;
    Execute.push(bne);
    //std::cout << "bne " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void BltDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation blt;
    blt.imm = imm;
    blt.rs1_number = ReadUpdatedReg(rs1);
    blt.rs2_number = ReadUpdatedReg(rs2);
    blt.type = ds::Blt;
    blt.jump = dir_pair.second.first;
    blt.pc = dir_pair.second.second;
    Execute.push(blt);
    //std::cout << "blt " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void BgeDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation bge;
    bge.imm = imm;
    bge.rs1_number = ReadUpdatedReg(rs1);
    bge.rs2_number = ReadUpdatedReg(rs2);
    bge.type = ds::Bge;
    bge.jump = dir_pair.second.first;
    bge.pc = dir_pair.second.second;
    Execute.push(bge);
    //std::cout << "bge " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void BltuDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation bltu;
    bltu.imm = imm;
    bltu.rs1_number = ReadUpdatedReg(rs1);
    bltu.rs2_number = ReadUpdatedReg(rs2);
    bltu.type = ds::Bltu;
    bltu.jump = dir_pair.second.first;
    bltu.pc = dir_pair.second.second;
    Execute.push(bltu);
    //std::cout << "bltu " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void BgeuDecode(const std::pair<std::string, std::pair<bool, int>> &dir_pair) {
    std::string dir = dir_pair.first;
    int rs2, rs1;
    std::string imm;
    B_Type(dir, imm, rs1, rs2);
    ds::Operation bgeu;
    bgeu.imm = imm;
    bgeu.rs1_number = ReadUpdatedReg(rs1);
    bgeu.rs2_number = ReadUpdatedReg(rs2);
    bgeu.type = ds::Bgeu;
    bgeu.jump = dir_pair.second.first;
    bgeu.pc = dir_pair.second.second;
    Execute.push(bgeu);
    //std::cout << "bgeu " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void LbDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation lb;
    lb.imm = imm;
    lb.rd = rd;
    lb.rs1_number = ReadUpdatedReg(rs1);
    lb.type = ds::Lb;
    Execute.push(lb);
    //std::cout << "lb " << rd << " " << rs1 << " " << imm << std::endl;
}

void LhDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation lh;
    lh.imm = imm;
    lh.rd = rd;
    lh.rs1_number = ReadUpdatedReg(rs1);
    lh.type = ds::Lh;
    Execute.push(lh);
    //std::cout << "lh " << rd << " " << rs1 << " " << imm << std::endl;
}

void LwDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation lw;
    lw.imm = imm;
    lw.rd = rd;
    lw.rs1_number = ReadUpdatedReg(rs1);
    lw.type = ds::Lw;
    Execute.push(lw);
    //std::cout << "lw " << rd << " " << rs1 << " " << imm << std::endl;
}

void LbuDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation lbu;
    lbu.imm = imm;
    lbu.rd = rd;
    lbu.rs1_number = ReadUpdatedReg(rs1);
    lbu.type = ds::Lbu;
    Execute.push(lbu);
    //std::cout << "lbu " << rd << " " << rs1 << " " << imm << std::endl;
}

void LhuDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation lhu;
    lhu.imm = imm;
    lhu.rd = rd;
    lhu.rs1_number = ReadUpdatedReg(rs1);
    lhu.type = ds::Lhu;
    Execute.push(lhu);
    //std::cout << "lhu " << rd << " " << rs1 << " " << imm << std::endl;
}

void SbDecode(const std::string &dir) {
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    ds::Operation sb;
    sb.imm = imm;
    sb.rs1_number = ReadUpdatedReg(rs1);
    sb.rs2_number = ReadUpdatedReg(rs2);
    sb.type = ds::Sb;
    Execute.push(sb);
    //std::cout << "sb " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void ShDecode(const std::string &dir) {
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    ds::Operation sh;
    sh.imm = imm;
    sh.rs1_number = ReadUpdatedReg(rs1);
    sh.rs2_number = ReadUpdatedReg(rs2);
    sh.type = ds::Sh;
    Execute.push(sh);
    //std::cout << "sh " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void SwDecode(const std::string &dir) {
    int rs1, rs2;
    std::string imm;
    S_Type(dir, imm, rs1, rs2);
    ds::Operation sw;
    sw.imm = imm;
    sw.rs1_number = ReadUpdatedReg(rs1);
    sw.rs2_number = ReadUpdatedReg(rs2);
    sw.type = ds::Sw;
    Execute.push(sw);
    //std::cout << "sw " << rs1 << " " << rs2 << " " << imm << std::endl;
}

void XoriDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation xori;
    xori.imm = imm;
    xori.type = ds::Xori;
    xori.rd = rd;
    xori.rs1_number = ReadUpdatedReg(rs1);
    Execute.push(xori);
    //std::cout << "xori " << rd << " " << rs1 << " " << imm << std::endl;
}

void OriDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation ori;
    ori.imm = imm;
    ori.type = ds::Ori;
    ori.rd = rd;
    ori.rs1_number = ReadUpdatedReg(rs1);
    Execute.push(ori);
    //std::cout << "ori " << rd << " " << rs1 << " " << imm << std::endl;
}

void AndiDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation addi;
    addi.imm = imm;
    addi.type = ds::Andi;
    addi.rd = rd;
    addi.rs1_number = ReadUpdatedReg(rs1);
    Execute.push(addi);
    //std::cout << "andi " << rd << " " << rs1 << " " << imm << std::endl;
}

void XorDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation xor_;
    xor_.rd = rd;
    xor_.rs1_number = ReadUpdatedReg(rs1);
    xor_.rs2_number = ReadUpdatedReg(rs2);
    xor_.type = ds::Xor;
    Execute.push(xor_);
    //std::cout << "xor " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void OrDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation or_;
    or_.rd = rd;
    or_.rs1_number = ReadUpdatedReg(rs1);
    or_.rs2_number = ReadUpdatedReg(rs2);
    or_.type = ds::Or;
    Execute.push(or_);
    //std::cout << "or " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void AndDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation and_;
    and_.rd = rd;
    and_.rs1_number = ReadUpdatedReg(rs1);
    and_.rs2_number = ReadUpdatedReg(rs2);
    and_.type = ds::And;
    Execute.push(and_);
    //std::cout << "and " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SlliDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation slli;
    slli.rd = rd;
    slli.rs1_number = ReadUpdatedReg(rs1);
    slli.rs2_number = ReadUpdatedReg(rs2);
    slli.rs2 = rs2;
    slli.type = ds::Slli;
    Execute.push(slli);
    //std::cout << "slli " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SrliDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation srli;
    srli.rd = rd;
    srli.rs1_number = ReadUpdatedReg(rs1);
    srli.rs2_number = ReadUpdatedReg(rs2);
    srli.rs2 = rs2;
    srli.type = ds::Srli;
    Execute.push(srli);
    //std::cout << "srli " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SraiDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation srai;
    srai.rd = rd;
    srai.rs1_number = ReadUpdatedReg(rs1);
    srai.rs2_number = ReadUpdatedReg(rs2);
    srai.rs2 = rs2;
    srai.type = ds::Srai;
    Execute.push(srai);
    //std::cout << "srai " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SllDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation sll;
    sll.rd = rd;
    sll.rs1_number = ReadUpdatedReg(rs1);
    sll.rs2_number = ReadUpdatedReg(rs2);
    sll.type = ds::Sll;
    Execute.push(sll);
    //std::cout << "sll " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SltDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation slt;
    slt.rd = rd;
    slt.rs1_number = ReadUpdatedReg(rs1);
    slt.rs2_number = ReadUpdatedReg(rs2);
    slt.type = ds::Slt;
    Execute.push(slt);
    //std::cout << "slt " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SltuDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation sltu;
    sltu.rd = rd;
    sltu.rs1_number = ReadUpdatedReg(rs1);
    sltu.rs2_number = ReadUpdatedReg(rs2);
    sltu.type = ds::Sltu;
    Execute.push(sltu);
    //std::cout << "sltu " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SrlDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation srl;
    srl.rd = rd;
    srl.rs1_number = ReadUpdatedReg(rs1);
    srl.rs2_number = ReadUpdatedReg(rs2);
    srl.type = ds::Srl;
    Execute.push(srl);
    //std::cout << "srl " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SraDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation sra;
    sra.rd = rd;
    sra.rs1_number = ReadUpdatedReg(rs1);
    sra.rs2_number = ReadUpdatedReg(rs2);
    sra.type = ds::Sra;
    Execute.push(sra);
    //std::cout << "sra " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SltiDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation slti;
    slti.type = ds::Slti;
    slti.imm = imm;
    slti.rs1_number = ReadUpdatedReg(rs1);
    slti.rd = rd;
    Execute.push(slti);
    //std::cout << "slti " << rd << " " << rs1 << " " << imm << std::endl;
}

void SltiuDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation sltiu;
    sltiu.type = ds::Sltiu;
    sltiu.imm = imm;
    sltiu.rs1_number = ReadUpdatedReg(rs1);
    sltiu.rd = rd;
    Execute.push(sltiu);
    //std::cout << "sltiu " << rd << " " << rs1 << " " << imm << std::endl;
}

void AddDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation add;
    add.rd = rd;
    add.rs1_number = ReadUpdatedReg(rs1);
    add.rs2_number = ReadUpdatedReg(rs2);
    add.type = ds::Add;
    Execute.push(add);
    //std::cout << "add " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void SubDecode(const std::string &dir) {
    int rd, rs1, rs2;
    R_Type(dir, rs2, rs1, rd);
    ds::Operation sub;
    sub.rd = rd;
    sub.rs1_number = ReadUpdatedReg(rs1);
    sub.rs2_number = ReadUpdatedReg(rs2);
    sub.type = ds::Sub;
    Execute.push(sub);
    //std::cout << "sub " << rd << " " << rs1 << " " << rs2 << std::endl;
}

void AddiDecode(const std::string &dir) {
    int rd, rs1;
    std::string imm;
    I_Type(dir, imm, rs1, rd);
    ds::Operation addi;
    addi.type = ds::Addi;
    addi.imm = imm;
    addi.rs1_number = ReadUpdatedReg(rs1);
    addi.rd = rd;
    Execute.push(addi);
    //std::cout << "addi " << rd << " " << rs1 << " " << imm << std::endl;
}

#endif //UNTITLED4_DECODE_H
