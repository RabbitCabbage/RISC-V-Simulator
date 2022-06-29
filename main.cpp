#include <iostream>
#include <string>
#include <queue>
#include "command.h"
#include "define.h"

int main() {
    ReadCommand();
    while (1) {
        WB();
        MEM();
        ID();
        EX();
        IF();
        if (Execute.empty() && WriteMem.empty() && WriteReg.empty() && ReadReg.empty() && Halt)break;
    }
    std::cout << (Register[10] & 255u) << std::endl;
//    std::cout << (double) Correct / (Wrong + Correct) << std::endl;
    return 0;
}