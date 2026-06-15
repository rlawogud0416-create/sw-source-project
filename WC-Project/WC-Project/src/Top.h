#ifndef TOP_H
#define TOP_H

#include "Clothing.h"

// 상의를 표현하는 클래스
class Top : public Clothing {
public:
    Top(int id, const std::string& name, int thicknessLevel);
    std::string getCategory() const override;
};

#endif
