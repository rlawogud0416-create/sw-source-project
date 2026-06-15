#ifndef OUTFIT_H
#define OUTFIT_H

#include "Top.h"
#include "Bottom.h"
#include "Outer.h"

// 추천된 한 세트의 코디 (상의 + 하의 + 아우터)
class Outfit {
private:
    Top* top;
    Bottom* bottom;
    Outer* outer;

public:
    Outfit(Top* top, Bottom* bottom, Outer* outer);

    void display() const;
    bool isValid() const;

    // Getters
    Top* getTop() const { return top; }
    Bottom* getBottom() const { return bottom; }
    Outer* getOuter() const { return outer; }
};

#endif
