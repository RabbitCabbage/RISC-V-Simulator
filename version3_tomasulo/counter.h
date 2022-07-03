//
// Created by lu'ren'jia'd's on 2022/6/29.
//

#ifndef UNTITLED4_COUNTER_H
#define UNTITLED4_COUNTER_H

class Counter {
    //0 Strongly Not Taken
    //1 Weakly Not Taken
    //2 Weakly Taken
    //3 Strongly Taken
private:
    int Status = 0;
public:
    bool Query() const {
        if (Status == 0 || Status == 1)return false;
        else return true;
    }

    void Update(bool jump) {
        if (jump) {
            if (Status < 3)Status++;
        } else if (Status > 0)Status--;
    }
};

#endif //UNTITLED4_COUNTER_H
