//
// Created by lu'ren'jia'd's on 2022/6/29.
//

#ifndef UNTITLED4_RUN_H
#define UNTITLED4_RUN_H

#include "tool.h"
#include "decode.h"
#include "execute.h"

void Init() {
    BufferSeat tmp;
    ReorderBuffer.clear();
    ReorderBuffer.insert({0, tmp});
    while (!InstructionQueue.empty())InstructionQueue.pop();
    //先放进去一个，这样所有的rename都是大于零的数字，就很合适
    //下面清空rs，并且rs的结果涉及到的寄存器，如果是用它重命名了，就得改回来
    for (auto p = ReservationStation.begin(); p != ReservationStation.end(); p++) {
        Register[p->destination].rename = 0;
    }
    ReservationStation.clear();
    StorageStation.clear();
}

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

void FetchInstruction() {
    if (Halt)return;
    std::string command;
    command.clear();
    if (Current >= 500000) {
        Halt = true;
        return ;
    }
    for (int i = 3; i >= 0; --i) {
        std::string part = Decimal_Hex(Memory[Current + i]);
        if (part.length() == 1)part = "0" + part;
        command += part;
    }
    //std::cout << "fetch instruction " << command << std::endl;
    if (command == "0FF00513") {
        Halt = true;
        return;
    }
    unsigned int pc = Current;
    Current += 4;//每一次读完之后的current已经被放到了下一个位置
    std::string dir = Hex_Binary(command);
    std::string com = dir.substr(25, 7);
    bool jump = false;
    if (com == "1100011") {
        jump = counter[pc % Mod].Query();
        if (jump) {
            std::string imm = dir.substr(0, 1) + dir.substr(24, 1) + dir.substr(1, 6) + dir.substr(20, 4) + "0";
            Current += Decode(imm) - 4;
        }
    }
    InstructionQueue.push({{jump,  pc},
                           {++CLK, dir}});
}

//这里返回的是《clk，opt》
std::pair<int, ds::Operation> DecodeInstruction() {
    //<jump,<clk,binary_instruction>>
    //std::cout << "decode ";
    auto ins = InstructionQueue.front();
    InstructionQueue.pop();
    std::string dir = ins.second.second;
    std::string com = dir.substr(25, 7);
    if (com == "0110111")return LuiDecode(ins);
    else if (com == "0010111")return AuipcDecode(ins);
    else if (com == "1101111")return JalDecode(ins);
    else if (com == "1100111")return JalrDecode(ins);
    else if (com == "1100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")return BeqDecode(ins);
        else if (f3 == "001")return BneDecode(ins);
        else if (f3 == "100")return BltDecode(ins);
        else if (f3 == "101")return BgeDecode(ins);
        else if (f3 == "110")return BltuDecode(ins);
        else if (f3 == "111")return BgeuDecode(ins);
    } else if (com == "0000011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")return LbDecode(ins);
        else if (f3 == "001")return LhDecode(ins);
        else if (f3 == "010")return LwDecode(ins);
        else if (f3 == "100")return LbuDecode(ins);
        else if (f3 == "101")return LhuDecode(ins);
    } else if (com == "0100011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")return SbDecode(ins);
        else if (f3 == "001")return ShDecode(ins);
        else if (f3 == "010")return SwDecode(ins);
    } else if (com == "0010011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000")return AddiDecode(ins);
        else if (f3 == "010")return SltiDecode(ins);
        else if (f3 == "011")return SltiuDecode(ins);
        else if (f3 == "001")return SlliDecode(ins);
        else if (f3 == "100")return XoriDecode(ins);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")return SrliDecode(ins);
            else return SraiDecode(ins);
        } else if (f3 == "110")return OriDecode(ins);
        else if (f3 == "111")return AndiDecode(ins);
    } else if (com == "0110011") {
        std::string f3 = dir.substr(17, 3);
        if (f3 == "000") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")return AddDecode(ins);
            else return SubDecode(ins);
        } else if (f3 == "001")return SllDecode(ins);
        else if (f3 == "010")return SltDecode(ins);
        else if (f3 == "011")return SltuDecode(ins);
        else if (f3 == "100")return XorDecode(ins);
        else if (f3 == "101") {
            std::string f7 = dir.substr(0, 7);
            if (f7 == "0000000")return SrlDecode(ins);
            else return SraDecode(ins);
        } else if (f3 == "110")return OrDecode(ins);
        else if (f3 == "111")return AndDecode(ins);
    }
    ds::Operation default_opt;
    return {0, default_opt};
}

void FillRS(const std::pair<int, ds::Operation> &opt_pair) {
    //std::cout << "fillRS " << opt_pair.second.pc << std::endl;
    StationSeat seat;
    BufferSeat rob;
    switch (opt_pair.second.type) {
        case ds::Lui:
        case ds::Auipc:
        case ds::Jal:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            seat.imm = opt_pair.second.imm;
            seat.destination = opt_pair.second.rd;
            Register[opt_pair.second.rd].rename = CLK;
            seat.pc = opt_pair.second.pc;//jal、jalr的pc都记下来了可以直接用
            seat.type = opt_pair.second.type;
            ReservationStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
        case ds::Beq:
        case ds::Bne:
        case ds::Blt:
        case ds::Bge:
        case ds::Bltu:
        case ds::Bgeu:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            seat.imm = opt_pair.second.imm;
            //seat.destination = opt_pair.second.rd;
            //Register[opt_pair.second.rd].rename=CLK;
            seat.jump = opt_pair.second.jump;
            seat.pc = opt_pair.second.pc;
            seat.type = opt_pair.second.type;
            if (Register[opt_pair.second.rs1].rename)//如果正在重命名，说明前面有没算完的
                seat.rename1 = Register[opt_pair.second.rs1].rename;
            else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方没有算完，也就是用这个RS的编号重命名
                seat.value1 = Register[opt_pair.second.rs1].value;
            }
            if (Register[opt_pair.second.rs2].rename)//如果正在重命名，说明前面有没算完的
                seat.rename2 = Register[opt_pair.second.rs2].rename;
            else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方没有算完，也就是用这个RS的编号重命名
                seat.value2 = Register[opt_pair.second.rs2].value;
            }
            ReservationStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
        case ds::Xori:
        case ds::Ori:
        case ds::Andi:
        case ds::Slti:
        case ds::Sltiu:
        case ds::Addi:
        case ds::Jalr:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            seat.imm = opt_pair.second.imm;
            seat.pc = opt_pair.second.pc;
            seat.destination = opt_pair.second.rd;
            seat.type = opt_pair.second.type;
            if (Register[opt_pair.second.rs1].rename)//如果正在重命名，说明前面有没算完的
            {
                seat.rename1 = Register[opt_pair.second.rs1].rename;
            } else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方rd没有算完，也就是用这个RS的编号重命名
                seat.value1 = Register[opt_pair.second.rs1].value;
            }
            Register[opt_pair.second.rd].rename = CLK;//不能放到上面，会影响rs1是否重命名的判断，比如rd==rs1就会出问题
            ReservationStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
        case ds::Xor:
        case ds::Or:
        case ds::And:
        case ds::Slli:
        case ds::Srai:
        case ds::Srli:
        case ds::Sll:
        case ds::Slt:
        case ds::Sltu:
        case ds::Srl:
        case ds::Sra:
        case ds::Add:
        case ds::Sub:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            //seat.imm = opt_pair.second.imm;
            seat.destination = opt_pair.second.rd;
            seat.rs2 = opt_pair.second.rs2;
            seat.pc = opt_pair.second.pc;
            seat.type = opt_pair.second.type;
            if (Register[opt_pair.second.rs1].rename)//如果正在重命名，说明前面有没算完的
            {
                seat.rename1 = Register[opt_pair.second.rs1].rename;
            } else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方没有算完，也就是用这个RS的编号重命名
                seat.value1 = Register[opt_pair.second.rs1].value;
            }
            if (Register[opt_pair.second.rs2].rename)//如果正在重命名，说明前面有没算完的
            {
                seat.rename2 = Register[opt_pair.second.rs2].rename;
            } else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方没有算完，也就是用这个RS的编号重命名
                seat.value2 = Register[opt_pair.second.rs2].value;
            }
            Register[opt_pair.second.rd].rename = CLK;
            ReservationStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
        case ds::Lb:
        case ds::Lh:
        case ds::Lw:
        case ds::Lbu:
        case ds::Lhu:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            seat.imm = opt_pair.second.imm;
            seat.pc = opt_pair.second.pc;
            seat.destination = opt_pair.second.rd;
            if (Register[opt_pair.second.rs1].rename)//如果正在重命名，说明前面有没算完的
                seat.rename1 = Register[opt_pair.second.rs1].rename;
            else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方rd没有算完，也就是用这个RS的编号重命名
                seat.value1 = Register[opt_pair.second.rs1].value;
            }
            Register[opt_pair.second.rd].rename = CLK;
            if (opt_pair.second.type == ds::Lh || opt_pair.second.type == ds::Lhu)
                Register[opt_pair.second.rd + 1].rename = CLK;
            if (opt_pair.second.type == ds::Lw) {
                Register[opt_pair.second.rd + 1].rename = CLK;
                Register[opt_pair.second.rd + 2].rename = CLK;
                Register[opt_pair.second.rd + 3].rename = CLK;
            }
            seat.type = opt_pair.second.type;
            StorageStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
        case ds::Sb:
        case ds::Sh:
        case ds::Sw:
            seat.clk = opt_pair.first;
            rob.clk = opt_pair.first;
            seat.imm = opt_pair.second.imm;
            seat.pc = opt_pair.second.pc;
            seat.type = opt_pair.second.type;
            if (Register[opt_pair.second.rs1].rename)//如果正在重命名，说明前面有没算完的
                seat.rename1 = Register[opt_pair.second.rs1].rename;
            else {
                //说明没有没算完，就需要把值填进去，
                //并且以后的会认为这个地方没有算完，也就是用这个RS的编号重命名
                seat.value1 = Register[opt_pair.second.rs1].value;
            }
            if (Register[opt_pair.second.rs2].rename)//如果正在重命名，说明前面有没算完的
                seat.rename2 = Register[opt_pair.second.rs2].rename;
            else {
                //说明算完了，就需要把值填进去，
                //并且以后的会认为这个地方rd没有算完，也就是用这个RS的编号重命名
                seat.value2 = Register[opt_pair.second.rs2].value;
            }
            StorageStation.push_back(seat);
            ReorderBuffer.insert({rob.clk, rob});
            break;
    }
}

void Computing() {
    StationSeat toROB;
    bool flag = false;
    if (!ReservationStation.empty()) {
        for (auto ptr = ReservationStation.begin(); ptr != ReservationStation.end(); ++ptr) {
            if (ptr->rename1 == 0 && ptr->rename2 == 0) {
                toROB = *ptr;
                //std::cout << "computing " << toROB.pc << " ";
                switch (toROB.type) {
                    case ds::Lui:
                        Lui(toROB);
                        break;
                    case ds::Auipc:
                        Auipc(toROB);
                        break;
                    case ds::Jal:
                        Jal(toROB);
                        break;
                    case ds::Jalr:
                        Jalr(toROB);
                        break;
                    case ds::Beq:
                        Beq(toROB);
                        break;
                    case ds::Bne:
                        Bne(toROB);
                        break;
                    case ds::Blt:
                        Blt(toROB);
                        break;
                    case ds::Bge:
                        Bge(toROB);
                        break;
                    case ds::Bltu:
                        Bltu(toROB);
                        break;
                    case ds::Bgeu:
                        Bgeu(toROB);
                        break;
                    case ds::Xori:
                        Xori(toROB);
                        break;
                    case ds::Ori:
                        Ori(toROB);
                        break;
                    case ds::Andi:
                        Andi(toROB);
                        break;
                    case ds::Xor:
                        Xor(toROB);
                        break;
                    case ds::Or:
                        Or(toROB);
                        break;
                    case ds::And:
                        And(toROB);
                        break;
                    case ds::Slli:
                        Slli(toROB);
                        break;
                    case ds::Srai:
                        Srai(toROB);
                        break;
                    case ds::Srli:
                        Srli(toROB);
                        break;
                    case ds::Sll:
                        Sll(toROB);
                        break;
                    case ds::Slt:
                        Slt(toROB);
                        break;
                    case ds::Sltu:
                        Sltu(toROB);
                        break;
                    case ds::Srl:
                        Srl(toROB);
                        break;
                    case ds::Sra:
                        Sra(toROB);
                        break;
                    case ds::Slti:
                        Slti(toROB);
                        break;
                    case ds::Sltiu:
                        Sltiu(toROB);
                        break;
                    case ds::Add:
                        Add(toROB);
                        break;
                    case ds::Sub:
                        Sub(toROB);
                        break;
                    case ds::Addi:
                        Addi(toROB);
                        break;
                }
                ReservationStation.erase(ptr);
                flag = true;
                break;
            }
        }
    }
    //找到所有用rename重命名的seat，把他们的重命名改回来
    if (!flag && !StorageStation.empty()) {
        for (auto ptr = StorageStation.begin(); ptr != StorageStation.end(); ++ptr) {
            if (ptr->rename1 == 0 && ptr->rename2 == 0) {
                toROB = *ptr;
                //std::cout << "computing " << toROB.pc << " ";
                switch (toROB.type) {
                    case ds::Lb:
                        Lb(toROB);
                        break;
                    case ds::Lh:
                        Lh(toROB);
                        break;
                    case ds::Lw:
                        Lw(toROB);
                        break;
                    case ds::Lbu:
                        Lbu(toROB);
                        break;
                    case ds::Lhu:
                        Lhu(toROB);
                        break;
                    case ds::Sb:
                        Sb(toROB);
                        break;
                    case ds::Sh:
                        Sh(toROB);
                        break;
                    case ds::Sw:
                        Sw(toROB);
                        break;
                }
            }
            StorageStation.erase(ptr);
            flag = true;
            break;
        }
    }
}

int Issue(const BufferSeat &seat) {
    //std::cout << " issue " << seat.pc << std::endl;
    switch (seat.type) {
        case ds::Jal:
            Init();
            Halt = false;
            Current = seat.pc + seat.value[1];
            //std::cout << "jump to " << Current << std::endl;
            Register[seat.destination].value = seat.value[0];
            return Register[seat.destination].rename;
        case ds::Jalr:
            Init();
            Halt = false;
            Current = seat.value[1];
            //std::cout << "jump to " << Current << std::endl;
            Register[seat.destination].value = seat.value[0];
            return Register[seat.destination].rename;
        case ds::Lui:
        case ds::Auipc:
        case ds::Xor:
        case ds::Or:
        case ds::And:
        case ds::Slli:
        case ds::Srai:
        case ds::Srli:
        case ds::Sll:
        case ds::Slt:
        case ds::Sltu:
        case ds::Srl:
        case ds::Sra:
        case ds::Add:
        case ds::Sub:
        case ds::Xori:
        case ds::Ori:
        case ds::Andi:
        case ds::Slti:
        case ds::Sltiu:
        case ds::Addi:
            Register[seat.destination].value = seat.value[0];
            return Register[seat.destination].rename;
        case ds::Sb:
            Memory[seat.destination] = seat.value[0];
            return 0;
        case ds::Sh:
            Memory[seat.destination] = seat.value[0];
            Memory[seat.destination + 1] = seat.value[1];
            return 0;
        case ds::Sw:
            Memory[seat.destination] = seat.value[0];
            Memory[seat.destination + 1] = seat.value[1];
            Memory[seat.destination + 2] = seat.value[2];
            Memory[seat.destination + 3] = seat.value[3];
            return 0;
        case ds::Beq:
        case ds::Bne:
        case ds::Blt:
        case ds::Bge:
        case ds::Bltu:
        case ds::Bgeu:
            //本身不用跳但是我跳了
            if (seat.jump && seat.value[0] == 0) {
                Init();
                Halt = false;
                Current = seat.pc + 4;
                Wrong++;
                counter[seat.pc % Mod].Update(!seat.jump);
            } else if (!seat.jump && seat.value[0] == 1) {
                Init();
                Halt = false;
                Current = seat.pc + seat.value[1];
                Wrong++;
                counter[seat.pc % Mod].Update(!seat.jump);
            } else {
                Correct++;
                counter[seat.pc % Mod].Update(seat.jump);
            }
            return 0;
        case ds::Lb:
            Register[seat.destination].value = Decode(Decimal_Binary8(Memory[seat.read_mem_address]));
            return Register[seat.destination].rename;
        case ds::Lbu:
            Register[seat.destination].value = DecodeZeroExtend(Decimal_Binary8(Memory[seat.read_mem_address]));
            return Register[seat.destination].rename;
        case ds::Lh:
            Register[seat.destination].value = Decode(Decimal_Binary8(Memory[seat.read_mem_address + 1]) +
                                                      Decimal_Binary8(Memory[seat.read_mem_address]));
            return Register[seat.destination].rename;
        case ds::Lhu:
            Register[seat.destination].value = DecodeZeroExtend(Decimal_Binary8(Memory[seat.read_mem_address + 1]) +
                                                                Decimal_Binary8(Memory[seat.read_mem_address]));
            return Register[seat.destination].rename;
        case ds::Lw:
            Register[seat.destination].value = Decode(Decimal_Binary8(Memory[seat.read_mem_address + 3]) +
                                                      Decimal_Binary8(Memory[seat.read_mem_address + 2])
                                                      + Decimal_Binary8(Memory[seat.read_mem_address + 1]) +
                                                      Decimal_Binary8(Memory[seat.read_mem_address]));
            return Register[seat.destination].rename;
    }
    //std::cout << std::endl;
    return 0;
}

void UpdateROB() {
    //std::cout << "updateROB";
    auto ptr = ReorderBuffer.begin();
    if (ReorderBuffer.size() >= 2 && (++ptr)->second.ready) {
        BufferSeat issue = ptr->second;
        ReorderBuffer.erase(ptr);
        int rename = Issue(issue);
        if (rename) {
            Register[issue.destination].rename = 0;
            if (issue.type == ds::Lh || issue.type == ds::Lhu)Register[issue.destination + 1].rename = 0;
            else if (issue.type == ds::Lw)
                Register[issue.destination + 1].rename = Register[issue.destination + 2].rename = Register[
                        issue.destination + 3].rename = 0;
            //如果返回的值是0就说明了这条指令没有涉及rd
            for (auto ptr = ReservationStation.begin(); ptr != ReservationStation.end(); ++ptr) {
                if (ptr->rename1 == rename) {
                    ptr->rename1 = 0;
                    ptr->value1 = Register[issue.destination].value;
                }
                if (ptr->rename2 == rename) {
                    ptr->rename2 = 0;
                    ptr->value2 = Register[issue.destination].value;
                }
            }
            for (auto ptr = StorageStation.begin(); ptr != StorageStation.end(); ++ptr) {
                if (ptr->rename1 == rename) {
                    ptr->rename1 = 0;
                    ptr->value1 = Register[issue.destination].value;
                }
                if (ptr->rename2 == rename) {
                    ptr->rename2 = 0;
                    ptr->value2 = Register[issue.destination].value;
                }
            }
        }
    }
    ////std::cout << std::endl;
}

#endif //UNTITLED4_RUN_H
