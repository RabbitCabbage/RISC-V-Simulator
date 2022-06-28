#include <iostream>
#include <string>
#include <queue>
#include "command.h"
#include "define.h"

int main() {
    ReadCommand();
    while (1) {
        MEM();
        EX();
        ID();
        WB();
        IF();
        if (Execute.empty() && WriteMem.empty() && WriteReg.empty() && ReadReg.empty() && Halt)break;
    }
    std::cout << (Register[10] & 255u) << std::endl;
    return 0;
}