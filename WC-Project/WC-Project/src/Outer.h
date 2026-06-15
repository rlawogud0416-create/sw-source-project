#ifndef OUTER_H
#define OUTER_H

#include "Clothing.h"

// 아우터를 표현하는 클래스
class Outer : public Clothing {
public:
    Outer(int id, const std::string& name, int thicknessLevel);
    std::string getCategory() const override;
};

#endif
