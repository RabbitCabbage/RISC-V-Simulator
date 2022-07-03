//
// Created by lu'ren'jia'd's on 2022/6/29.
//
#include <iostream>
#include "define.h"
#include "run.h"

int main() {
    Init();
    ReadCommand();
    FetchInstruction();
    while (1) {
        //std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        if (!Halt)FetchInstruction();
        if (!InstructionQueue.empty())FillRS(DecodeInstruction());
        Computing();
        UpdateROB();
        //std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        if (ReorderBuffer.size() == 1 && Halt)break;
        Register[0].value = 0;
//        for (int i = 0; i < 32; ++i) {
//            std::cout << Register[i].value << '\t';
//        }
//        std::cout << std::endl;
        //if (CLK == 100)return 0;
    }
    std::cout << (Register[10].value & 255u) << std::endl;
    return 0;
}