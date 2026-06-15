#ifndef BOTTOM_H
#define BOTTOM_H

#include "Clothing.h"

// 하의를 표현하는 클래스
class Bottom : public Clothing {
public:
    Bottom(int id, const std::string& name, int thicknessLevel);
    std::string getCategory() const override;
};

#endif
