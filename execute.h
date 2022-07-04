//
// Created by lu'ren'jia'd's on 2022/6/27.
//

#ifndef UNTITLED4_EXECUTE_H
#define UNTITLED4_EXECUTE_H

int ReadUpdatedMem(int address) {
    if (MemUpdate.empty() || address < Address || address >= Address + Bytes)return Memory[address];
    else return MemUpdate[address - Address];
}

void Lui(const ds::Operation &opt) {
    int reg_number = Decode(opt.imm + "000000000000");
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "lui " << opt.rd << "\t" << reg_number << std::endl;
}

void Auipc(const ds::Operation &opt) {
    int reg_number = Decode(opt.imm + "000000000000") + Current - 4;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "auipc " << opt.rd << "\t" << reg_number << std::endl;
}

void Jal(const ds::Operation &opt) {
    Register[opt.rd] = opt.pc + 4;
    ////std::couttt << Register[opt.rd] << std::endl;
    Current = opt.pc + Decode(opt.imm);
    while (!ReadReg.empty()) {
        ReadReg.pop();
    }
    while (!Execute.empty())Execute.pop();
    Halt = false;
    //std::coutt << "jal " << Register[opt.rd] << "\t" << Current << std::endl;
}

void Jalr(const ds::Operation &opt) {
    std::string cur = Decimal_Binary32(Decode(opt.imm) + opt.rs1_number);
    cur[31] = '0';
    Register[opt.rd] = opt.pc + 4;
    ////std::coutt << Register[opt.rd] << std::endl;
    Current = Binary_Decimal(cur);
    while (!ReadReg.empty()) {
        ReadReg.pop();
    }
    while (!Execute.empty())Execute.pop();
    Halt = false;
    //std::coutt << "jalr " << Register[opt.rd] << "\t" << Current << std::endl;
}

void Beq(const ds::Operation &opt) {
    //std::coutt << "beq " << opt.rs1_number << "\t" << opt.rs2_number << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && opt.rs1_number == opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        //std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && opt.rs1_number != opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Bne(const ds::Operation &opt) {
    //std::coutt << "bne " << opt.rs1_number << "\t" << opt.rs2_number << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && opt.rs1_number != opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        ////std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && opt.rs1_number == opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Blt(const ds::Operation &opt) {
    //std::coutt << "blt " << opt.rs1_number << "\t" << opt.rs2_number << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && opt.rs1_number < opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        ////std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && opt.rs1_number >= opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Bge(const ds::Operation &opt) {
    //std::coutt << "bge " << opt.rs1_number << "\t" << opt.rs2_number << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && opt.rs1_number >= opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        //std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && opt.rs1_number < opt.rs2_number) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Bltu(const ds::Operation &opt) {
    //std::coutt << "bltu " << ((unsigned) opt.rs1_number) << "\t" << ((unsigned) opt.rs2_number) << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && ((unsigned) opt.rs1_number) < ((unsigned) opt.rs2_number)) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        //std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && ((unsigned) opt.rs1_number) >= ((unsigned) opt.rs2_number)) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Bgeu(const ds::Operation &opt) {
    //std::coutt << "bgeu " << ((unsigned) opt.rs1_number) << "\t" << ((unsigned) opt.rs2_number) << std::endl;
    //现在的Current已经是指向下一条指令了，相当于正在执行的+4或者已经跳转了
    unsigned int pc = opt.pc;
    if (!opt.jump && ((unsigned) opt.rs1_number) >= ((unsigned) opt.rs2_number)) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + Decode(opt.imm);
        while (!Execute.empty())Execute.pop();
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
        //std::coutt << "jump to " << Current << std::endl;
    } else if (opt.jump && ((unsigned) opt.rs1_number) < ((unsigned) opt.rs2_number)) {
        while (!ReadReg.empty()) {
            ReadReg.pop();
        }
        Current = pc + 4;
        Halt = false;
        Wrong++;
        counter[pc % Mod].Update(!opt.jump);
    } else {
        Correct++;
        counter[pc % Mod].Update(opt.jump);
    }
}

void Lb(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    int reg_number = Decode(Decimal_Binary8(ReadUpdatedMem(address)));
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "lb " << opt.rd << "\t" << reg_number << std::endl;
}

void Lh(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string code = Decimal_Binary8(ReadUpdatedMem(address + 1)) + Decimal_Binary8(ReadUpdatedMem(address));
    int reg_number = Decode(code);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "lh " << opt.rd << " " << reg_number << std::endl;
}

void Lw(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string code = Decimal_Binary8(ReadUpdatedMem(address + 3)) + Decimal_Binary8(ReadUpdatedMem(address + 2))
                       + Decimal_Binary8(ReadUpdatedMem(address + 1)) + Decimal_Binary8(ReadUpdatedMem(address));
    int reg_number = Decode(code);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
//    //std::coutt << std::endl;
//    //std::coutt << "=========================================================" << std::endl;
//    //std::coutt << "Register[rs1] = " << opt.rs1_number << std::endl;
//    //std::coutt << "address = " << address << std::endl;
//    //std::coutt << ReadUpdatedMem(address) << " " << ReadUpdatedMem(address + 1) << " " << ReadUpdatedMem(address + 2)
    //          << " "
    //          << ReadUpdatedMem(address + 3) << std::endl;

    //std::coutt << "lw " << opt.rd << " " << reg_number << std::endl;
//    //std::coutt << "=========================================================" << std::endl;
//    //std::coutt << std::endl;
}

void Lbu(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    int reg_number = DecodeZeroExtend(Decimal_Binary8(ReadUpdatedMem(address)));
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "lbu " << opt.rd << " " << reg_number << std::endl;
}

void Lhu(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string code = Decimal_Binary8(ReadUpdatedMem(address + 1)) + Decimal_Binary8(ReadUpdatedMem(address));
    int reg_number = DecodeZeroExtend(code);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "lhu " << opt.rd << "\t" << reg_number << std::endl;
}

void Sb(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string b_number32 = Decimal_Binary32(opt.rs2_number);
    int mem_number = Binary_Decimal(b_number32.substr(24, 8));
    WriteMem.push({1, {address, mem_number}});//这里的1代表的是后面有多少个写内存操作是来自与同一项指令
    MemUpdate.clear();
    MemUpdate.push_back(mem_number);
    Address = address;
    Bytes = 1;
    //std::coutt << "sb " << address << "\t" << Decimal_Binary32(opt.rs2_number) << std::endl;
}

void Sh(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string b_number32 = Decimal_Binary32(opt.rs2_number);
    int mem_number = Binary_Decimal(b_number32.substr(24, 8));
    int mem_number2 = Binary_Decimal(b_number32.substr(16, 8));
    WriteMem.push({2, {address, mem_number}});
    WriteMem.push({0, {address + 1, mem_number2}});
    MemUpdate.clear();
    MemUpdate.push_back(mem_number);
    MemUpdate.push_back(mem_number2);
    Address = address;
    Bytes = 2;
    //std::coutt << "sh " << address << "\t" << Decimal_Binary32(opt.rs2_number) << std::endl;
}

void Sw(const ds::Operation &opt) {
    int address = opt.rs1_number + Decode(opt.imm);
    std::string b_number32 = Decimal_Binary32(opt.rs2_number);
    int mem_number = Binary_Decimal(b_number32.substr(24, 8));
    int mem_number2 = Binary_Decimal(b_number32.substr(16, 8));
    int mem_number3 = Binary_Decimal(b_number32.substr(8, 8));
    int mem_number4 = Binary_Decimal(b_number32.substr(0, 8));
    WriteMem.push({4, {address, mem_number}});
    WriteMem.push({0, {address + 1, mem_number2}});
    WriteMem.push({0, {address + 2, mem_number3}});
    WriteMem.push({0, {address + 3, mem_number4}});
    MemUpdate.clear();
    MemUpdate.push_back(mem_number);
    MemUpdate.push_back(mem_number2);
    MemUpdate.push_back(mem_number3);
    MemUpdate.push_back(mem_number4);
    Address = address;
    Bytes = 4;
//    //std::coutt << std::endl;
//    //std::coutt << "=========================================================" << std::endl;
//    //std::coutt << "address = " << address << std::endl;
//    //std::coutt << mem_number << " " << mem_number2 << " " << mem_number3 << " "
    //          << mem_number4 << std::endl;
    //std::coutt << "sw " << mem_number << std::endl;
//    //std::coutt << "=========================================================" << std::endl;
}

void Xori(const ds::Operation &opt) {
    int reg_number = opt.rs1_number ^ Decode(opt.imm);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "xori " << opt.rd << "\t" << reg_number << std::endl;
}

void Ori(const ds::Operation &opt) {
    int reg_number = opt.rs1_number | Decode(opt.imm);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "ori " << opt.rd << "\t" << reg_number << std::endl;
}

void Andi(const ds::Operation &opt) {
    int reg_number = opt.rs1_number & Decode(opt.imm);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "andi " << opt.rd << "\t" << reg_number << std::endl;
}

void Xor(const ds::Operation &opt) {
    int reg_number = opt.rs1_number ^ opt.rs2_number;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "xor " << opt.rd << "\t" << reg_number << std::endl;
}

void Or(const ds::Operation &opt) {
    int reg_number = opt.rs1_number | opt.rs2_number;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "or " << opt.rd << "\t" << reg_number << std::endl;
}

void And(const ds::Operation &opt) {
    int reg_number = opt.rs1_number & opt.rs2_number;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "and " << opt.rd << "\t" << reg_number << std::endl;
}

void Slli(const ds::Operation &opt) {
    int reg_number = ((unsigned) opt.rs1_number) << opt.rs2;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "slli " << opt.rd << "\t" << reg_number << std::endl;
}

void Srli(const ds::Operation &opt) {
    int reg_number = ((unsigned) opt.rs1_number) >> opt.rs2;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "srli " << opt.rd << "\t" << reg_number << std::endl;
}

void Srai(const ds::Operation &opt) {
    int reg_number = ((int) opt.rs1_number) >> opt.rs2;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "srai " << opt.rd << "\t" << reg_number << std::endl;
}

void Sll(const ds::Operation &opt) {
    int move = Binary_Decimal(Decimal_Binary5(opt.rs2_number));
    int reg_number = ((unsigned) opt.rs1_number) << move;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "sll " << opt.rd << "\t" << reg_number << std::endl;
}

void Slt(const ds::Operation &opt) {
    int reg_number;
    if (opt.rs1_number < opt.rs2_number)reg_number = 1;
    else reg_number = 0;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "slt " << opt.rd << "\t" << reg_number << std::endl;
}

void Sltu(const ds::Operation &opt) {
    int reg_number;
    if (((unsigned) opt.rs1_number) < ((unsigned) opt.rs2_number))reg_number = 1;
    else reg_number = 0;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "sltu " << opt.rd << "\t" << reg_number << std::endl;
}

void Srl(const ds::Operation &opt) {
    int move = Binary_Decimal(Decimal_Binary5(opt.rs2_number));
    int reg_number = ((unsigned) opt.rs1_number) >> move;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "srl " << opt.rd << "\t" << reg_number << std::endl;
}

void Sra(const ds::Operation &opt) {
    int move = Binary_Decimal(Decimal_Binary5(opt.rs2_number));
    int reg_number = ((int) opt.rs1_number) >> move;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "sra " << opt.rd << "\t" << reg_number << std::endl;
}

void Slti(const ds::Operation &opt) {
    int reg_number;
    if (opt.rs1_number < Decode(opt.imm))reg_number = 1;
    else reg_number = 0;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "slti " << opt.rd << "\t" << reg_number << std::endl;
}

void Sltiu(const ds::Operation &opt) {
    int reg_number;
    if (((unsigned) opt.rs1_number) < ((unsigned) Decode(opt.imm)))reg_number = 1;
    else reg_number = 0;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "sltiu " << opt.rd << "\t" << reg_number << std::endl;
}

void Add(const ds::Operation &opt) {
    int reg_number = opt.rs1_number + opt.rs2_number;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "add " << opt.rd << "\t" << reg_number << std::endl;
}

void Sub(const ds::Operation &opt) {
    int reg_number = opt.rs1_number - opt.rs2_number;
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "sub " << opt.rd << "\t" << reg_number << std::endl;
}

void Addi(const ds::Operation &opt) {
    int reg_number = opt.rs1_number + Decode(opt.imm);
    WriteReg.push({opt.rd, reg_number});
    Number = opt.rd;
    RegUpdate = reg_number;
    //std::coutt << "addi " << opt.rd << "\t" << reg_number << std::endl;
}

#endif //UNTITLED4_EXECUTE_H
